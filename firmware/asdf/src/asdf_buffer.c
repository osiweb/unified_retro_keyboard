// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_buffer.c
//
// This is a circular buffer module that can be used by any part of the code
// that requires buffering. Buffering provides an interface between the
// generation of keycodes and the hardware-level keycode transmission, which may
// occur at different rates.
//
// Copyright 2019 David Fenyes
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.


#include <stdio.h>
#include <stdint.h>
#include "asdf.h"
#include "asdf_buffer.h"

// Implementation Notes:
//
// 1) Note that this implementation does not support dynamic allocation and
// freeing of buffers. Each buffer is allocated at startup and is stable forever
// afterwards.
//
// 2) Buffer handles are indices into an array of buffer-tracking structures.
// Using indices rather than pointers incurs a small performance penalty for the
// extra level of indirection, but affords the advantage of testing the buffer
// handle for validity.


// Define the low-level details for each buffer.
typedef struct {
  asdf_keycode_t *buf;
  int16_t size;
  uint8_t head;
  uint8_t tail;
  uint8_t count;
} asdf_buffer_t;

// This is the pool of codes available for buffering. This pool is divided among
// the allocated buffers.
static asdf_keycode_t buffer_pool[ASDF_BUFFER_POOL_SIZE];

// This array stores the buffering details for each allocated buffer. The number
// of available buffers is defined in the header file.
static asdf_buffer_t buffers[ASDF_BUFFER_NUM_HANDLES];

// Index of the beginning of unallocated part of the buffer pool.
static int16_t buffer_pool_next_available;

// Index of the next available buffer handle
static asdf_buffer_handle_t next_handle;


// PROCEDURE: asdf_buffer_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize the buffer pool and handles
//
// SIDE EFFECTS: See description
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_buffer_init(void)
{
  buffer_pool_next_available = 0;
  next_handle = 0;
}

// PROCEDURE: buffer_handle_valid
// INPUTS: (uint8_t) handle - handle to be checked
// OUTPUTS: returns TRUE if the handle is a valid allocated handle.
//
// DESCRIPTION: Returns TRUE if the handle is one that has been allocated.
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
uint8_t buffer_handle_valid(asdf_buffer_handle_t handle)
{
  return ((handle >= 0) && (handle < next_handle));
}

// PROCEDURE: asdf_buffer_new
// INPUTS: (uint16_t) size: size of the buffer to allocate.
//
// OUTPUTS: returns a uint8_t handle to identify the buffer allocated from the
//          pool.
//
// DESCRIPTION: Receives a request to allocate a fixed-size buffer from the
// pool. If there is enough room in the buffer pool, and if a buffer handle is
// available, then allocate space from the pool, initialize the next available
// buffer struct, and return the handle.
//
// SIDE EFFECTS: see above
//
// SCOPE: public
//
// COMPLEXITY: 3
//
asdf_buffer_handle_t asdf_buffer_new(int16_t size)
{
  asdf_buffer_handle_t handle = ASDF_BUFFER_INVALID;

  if (next_handle < ASDF_BUFFER_NUM_HANDLES) {
    if (size <= (ASDF_BUFFER_POOL_SIZE - buffer_pool_next_available)) {
      handle = next_handle++;

      buffers[handle].size = size;
      buffers[handle].buf = &buffer_pool[buffer_pool_next_available];
      buffers[handle].head = 0;
      buffers[handle].tail = 0;
      buffers[handle].count = 0;

      buffer_pool_next_available += size;
    }
  }
  return handle;
}


// PROCEDURE: asdf_buffer_put
//
// INPUTS:(asdf_buffer_t) buffer_handle: pointer to the buffer struct.
//        (asdf_keycode_t) code: code to be added to the queue.
//
// OUTPUTS: None
//
// DESCRIPTION: Add the keycode to the head of the output buffer. If the buffer
// is full, quietly drop the keycode.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES:
//
// COMPLEXITY: 3
//
// SCOPE: public
//
void asdf_buffer_put(asdf_buffer_handle_t handle, asdf_keycode_t code)
{
  if (buffer_handle_valid(handle)) {
    if (buffers[handle].count < buffers[handle].size) {
      buffers[handle].buf[buffers[handle].head] = code;
      buffers[handle].head = (buffers[handle].head + 1) % buffers[handle].size;
      buffers[handle].count++;
    }
  }
}

// PROCEDURE: asdf_buffer_get
//
// INPUTS: None
//
// OUTPUTS: returns next code in the buffer.
//
// DESCRIPTION: Gets the next queued code in the output buffer and return the
// value.
//
// SIDE EFFECTS: Removes a code from the queue.
//
// NOTES: If the buffer is empty, the code ASDF_INVALID_CODE is returned.
//
// COMPLEXITY: 2
//
// SCOPE: Public
//
asdf_keycode_t asdf_buffer_get(asdf_buffer_handle_t handle)
{
  asdf_keycode_t code = ASDF_INVALID_CODE;
  if (buffers[handle].count) {
    code = buffers[handle].buf[buffers[handle].tail];
    buffers[handle].tail = (buffers[handle].tail + 1) % buffers[handle].size;
    buffers[handle].count--;
  }
  return code;
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
