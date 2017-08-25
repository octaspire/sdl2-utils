#include "external/greatest.h"

extern SUITE(octaspire_sdl2_timer_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(octaspire_sdl2_timer_suite);
    GREATEST_MAIN_END();
}

