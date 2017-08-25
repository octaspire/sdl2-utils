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
#ifndef OCTASPIRE_SDL2_TIMER_H
#define OCTASPIRE_SDL2_TIMER_H

#include <stdbool.h>
#include "SDL.h"
#include "octaspire/core/octaspire_memory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_sdl2_timer_t octaspire_sdl2_timer_t;

octaspire_sdl2_timer_t *octaspire_sdl2_timer_new(
    octaspire_memory_allocator_t * const allocator);

void octaspire_sdl2_timer_release(
    octaspire_sdl2_timer_t * const self);

void octaspire_sdl2_timer_update(
    octaspire_sdl2_timer_t * const self);

void octaspire_sdl2_timer_reset(
    octaspire_sdl2_timer_t * const self);

double octaspire_sdl2_timer_get_seconds(
    octaspire_sdl2_timer_t const * const self);

double octaspire_sdl2_timer_get_milliseconds(
    octaspire_sdl2_timer_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

