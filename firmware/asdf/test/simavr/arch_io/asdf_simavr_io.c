#include <string.h>

#include "asdf_simavr_io_familyA.h"
#include "asdf_simavr_io_familyB.h"

const asdf_io_map_t *asdf_io_pick(const char *target)
{
    if (!strcmp(target, "atmega328p") ||
        !strcmp(target, "atmega168p") ||
        !strcmp(target, "atmega88p")) return &asdf_io_familyA;
    if (!strcmp(target, "atmega640") ||
        !strcmp(target, "atmega1280") ||
        !strcmp(target, "atmega2560")) return &asdf_io_familyB;
    return 0;
}
