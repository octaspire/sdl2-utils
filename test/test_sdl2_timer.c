/******************************************************************************
Octaspire sdl2-utils - Utilities for SDL2
Copyright 2017 www.octaspire.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
******************************************************************************/
#include "../src/octaspire_sdl2_timer.c"
#include <assert.h>
#include <time.h>
#include "external/greatest.h"

static octaspire_memory_allocator_t *octaspireSDL2TimerTestAllocator = 0;


#if (__STDC_VERSION__ >= 201112L)

static double octaspire_test_sdl2_timer_private_timespec_to_double(
    struct timespec const ts)
{
    return (double)(ts.tv_sec) + ((double)(ts.tv_nsec) / 1000000000.0);
}

TEST octaspire_sdl2_timer_test(void)
{
    octaspire_sdl2_timer_t * t =
        octaspire_sdl2_timer_new(octaspireSDL2TimerTestAllocator);

    double const epsilonSecs = 0.0001;

    for (size_t i = 0; i < 256; ++i)
    {
        octaspire_sdl2_timer_reset(t);
        struct timespec start;
        ASSERT_EQ(TIME_UTC, timespec_get(&start, TIME_UTC));

        for (size_t j = i; j < (i * (10 * i)); ++j)
        {
            ASSERT(j >= i);
        }

        struct timespec now;
        ASSERT_EQ(TIME_UTC, timespec_get(&now, TIME_UTC));

        double  const secs  =
            octaspire_test_sdl2_timer_private_timespec_to_double(now) -
            octaspire_test_sdl2_timer_private_timespec_to_double(start);

        octaspire_sdl2_timer_update(t);
        double  const msecs = secs * 1000.0;

        ASSERT_IN_RANGE(secs,  octaspire_sdl2_timer_get_seconds(t),      epsilonSecs);
        ASSERT_IN_RANGE(msecs, octaspire_sdl2_timer_get_milliseconds(t), epsilonSecs * 1000);
    }

    octaspire_sdl2_timer_release(t);
    t = 0;

    PASS();
}

#endif

GREATEST_SUITE(octaspire_sdl2_timer_suite)
{
    octaspireSDL2TimerTestAllocator = octaspire_memory_allocator_new(0);

    assert(octaspireSDL2TimerTestAllocator);

#if (__STDC_VERSION__ >= 201112L)
    RUN_TEST(octaspire_sdl2_timer_test);
#endif

    octaspire_memory_allocator_release(octaspireSDL2TimerTestAllocator);
    octaspireSDL2TimerTestAllocator = 0;
}

