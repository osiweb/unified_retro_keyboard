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

    asdf_cap_record_t r;
    assert(cap_pop(&r) == 1 && r.cycle == 100 && r.byte == 'a');
    assert(cap_pop(&r) == 1 && r.cycle == 200 && r.byte == 'b');
    assert(cap_pop(&r) == 0);

    /* overflow: oldest dropped */
    for (int i = 0; i < ASDF_CAP_RING_SIZE + 5; i++) cap_push(i, i & 0xFF);
    assert(cap_count() == ASDF_CAP_RING_SIZE);
    assert(cap_pop(&r) == 1 && r.cycle == 5);   /* first 5 were dropped */

    printf("capture: OK\n");
    return 0;
}
