#include <assert.h>
#include <stdio.h>
#include "capture.h"

int main(void)
{
    cap_init();
    assert(cap_count() == 0);

    cap_push(100, 'a');
    cap_push(200, 'b');
    assert(cap_count() == 2);

    /* Keep cap_pop calls out of assert() expressions: under NDEBUG the call
     * would be elided and the buffer would not advance.  Always store the
     * return value into a local first. */
    asdf_cap_record_t r;
    int ok;

    ok = cap_pop(&r); assert(ok == 1); assert(r.cycle == 100 && r.byte == 'a');
    ok = cap_pop(&r); assert(ok == 1); assert(r.cycle == 200 && r.byte == 'b');
    ok = cap_pop(&r); assert(ok == 0);

    /* fill exactly to capacity: count must be the full size, no eviction yet */
    cap_clear();
    for (int i = 0; i < ASDF_CAP_RING_SIZE; i++) cap_push(i, i & 0xFF);
    assert(cap_count() == ASDF_CAP_RING_SIZE);

    /* overflow: oldest entries dropped */
    cap_clear();
    for (int i = 0; i < ASDF_CAP_RING_SIZE + 5; i++) cap_push(i, i & 0xFF);
    assert(cap_count() == ASDF_CAP_RING_SIZE);
    ok = cap_pop(&r); assert(ok == 1); assert(r.cycle == 5);  /* first 5 dropped */
    ok = cap_pop(&r); assert(ok == 1); assert(r.cycle == 6);  /* wrap-around intact */

    printf("capture: OK\n");
    return 0;
}
