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
#include "octaspire/sdl2-utils/octaspire_sdl2_timer.h"

struct octaspire_sdl2_timer_t
{
    octaspire_memory_allocator_t *allocator;
    double                        seconds;
    Uint64                        countNow;
    Uint64                        countPrevious;
};


octaspire_sdl2_timer_t *octaspire_sdl2_timer_new(
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_sdl2_timer_t *self = octaspire_memory_allocator_malloc(
        allocator,
        sizeof(octaspire_sdl2_timer_t));

    if (!self)
    {
        return self;
    }

    self->allocator      = allocator;

    octaspire_sdl2_timer_reset(self);

    return self;
}

void octaspire_sdl2_timer_release(
    octaspire_sdl2_timer_t * const self)
{
    if (!self)
    {
        return;
    }

    octaspire_memory_allocator_free(self->allocator, self);
}

void octaspire_sdl2_timer_update(
    octaspire_sdl2_timer_t * const self)
{
    self->countPrevious = self->countNow;
    self->countNow      = SDL_GetPerformanceCounter();

    Uint64 const countDiff = self->countNow - self->countPrevious;

    self->seconds = (double)countDiff / (double)SDL_GetPerformanceFrequency();
}

void octaspire_sdl2_timer_reset(
    octaspire_sdl2_timer_t * const self)
{
    self->seconds       = 0;
    self->countNow      = SDL_GetPerformanceCounter();
    self->countPrevious = self->countNow;
}

double octaspire_sdl2_timer_get_seconds(
    octaspire_sdl2_timer_t const * const self)
{
    return self->seconds;
}

double octaspire_sdl2_timer_get_milliseconds(
    octaspire_sdl2_timer_t const * const self)
{
    return self->seconds * 1000.0;
}

