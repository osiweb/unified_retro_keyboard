// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Universal Keyboard Project
// ASDF keyboard firmware
//
// asdf_buffer.h
//
// Contains definitions and prototypes for the asdf keycode output buffer.
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
//

#if !defined(ASDF_BUFFER_H)
#define ASDF_BUFFER_H

#include "asdf_config.h"

#define ASDF_BUFFER_POOL_SIZE ASDF_KEYCODE_BUFFER_SIZE
#define ASDF_BUFFER_INVALID -1

// Setting the number of handles to 1 will work if only one buffer is requrired,
// and will save a few bytes of RAM. But the test code needs at least 2 buffer
// handles to test the module, so we leave it at 2.
#define ASDF_BUFFER_NUM_HANDLES 2

typedef int16_t asdf_buffer_handle_t;

// PROCEDURE: asdf_buffer_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize the buffer pool and handles
void asdf_buffer_init(void);

// PROCEDURE: asdf_buffer_new
// INPUTS: (uint16_t) size: size of the buffer to allocate.
// OUTPUTS: returns (asdf_buffer_handle_t) handle to identify the buffer allocated from the
//          pool.
// DESCRIPTION: Receives a request to allocate a fixed-size buffer from the
// pool. If there is enough room in the buffer pool, and if a buffer handle is
// available, then allocate space from the pool, initialize the next available
// buffer struct, and return the handle.
asdf_buffer_handle_t asdf_buffer_new(int16_t size);

// PROCEDURE: asdf_buffer_put
// INPUTS:(asdf_buffer_t) buffer_handle: pointer to the buffer struct.
//        (asdf_keycode_t) code: code to be added to the queue.
// OUTPUTS: None
// DESCRIPTION: Add the keycode to the head of the output buffer. If the buffer
// is full, quietly drop the keycode.
void asdf_buffer_put(asdf_buffer_handle_t handle, asdf_keycode_t code);

// PROCEDURE: asdf_buffer_get
// INPUTS: None
// OUTPUTS: returns next code in the buffer.
// DESCRIPTION: Gets the next queued code in the output buffer and return the
// value.
asdf_keycode_t asdf_buffer_get(asdf_buffer_handle_t handle);

#endif // !defined (ASDF_BUFFER_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

