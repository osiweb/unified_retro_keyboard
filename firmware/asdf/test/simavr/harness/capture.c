#include <stdlib.h>

#include "capture.h"

static asdf_cap_record_t ring[ASDF_CAP_RING_SIZE];
static size_t head = 0;   /* next write */
static size_t tail = 0;   /* next read */
static size_t count = 0;

void cap_clear(void) { head = tail = count = 0; }
void cap_init(void)  { cap_clear(); }

void cap_push(uint64_t cycle, uint8_t byte)
{
    ring[head].cycle = cycle;
    ring[head].byte  = byte;
    head = (head + 1) % ASDF_CAP_RING_SIZE;
    if (count < ASDF_CAP_RING_SIZE) count++;
    else tail = (tail + 1) % ASDF_CAP_RING_SIZE;   /* drop oldest on overflow */
}

int cap_pop(asdf_cap_record_t *out)
{
    if (!out) abort();
    if (count == 0) return 0;
    *out = ring[tail];
    tail = (tail + 1) % ASDF_CAP_RING_SIZE;
    count--;
    return 1;
}

size_t cap_count(void) { return count; }
