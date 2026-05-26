#ifndef ASDF_SIM_CAPTURE_H
#define ASDF_SIM_CAPTURE_H

#include <stdint.h>
#include <stddef.h>

#define ASDF_CAP_RING_SIZE 64

typedef struct {
    uint64_t cycle;
    uint8_t  byte;
} asdf_cap_record_t;

void cap_init(void);
void cap_push(uint64_t cycle, uint8_t byte);
int  cap_pop(asdf_cap_record_t *out);   /* 1 if a record was returned, 0 if empty */
size_t cap_count(void);
void cap_clear(void);

#endif
