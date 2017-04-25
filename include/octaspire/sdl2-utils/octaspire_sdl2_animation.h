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
#ifndef OCTASPIRE_SDL2_ANIMATION_H
#define OCTASPIRE_SDL2_ANIMATION_H

#include <stdbool.h>
#include "octaspire/sdl2-utils/octaspire_sdl2_texture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_sdl2_animation_t octaspire_sdl2_animation_t;

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new(
    char const * const name,
    bool const loop,
    octaspire_memory_allocator_t * const allocator);

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new_copy(
    octaspire_sdl2_animation_t const * const other,
    octaspire_memory_allocator_t * const allocator);

void octaspire_sdl2_animation_release(octaspire_sdl2_animation_t *self);

bool octaspire_sdl2_animation_push_back_frame(
    octaspire_sdl2_animation_t * const self,
    SDL_Rect const * const rect,
    double const durationInSeconds);

void octaspire_sdl2_animation_update(
    octaspire_sdl2_animation_t * const self,
    double const dt);

void octaspire_sdl2_animation_render(
    octaspire_sdl2_animation_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY);

void octaspire_sdl2_animation_print(
    octaspire_sdl2_animation_t const * const self);

char const * octaspire_sdl2_animation_get_name(
    octaspire_sdl2_animation_t const * const self);

void octaspire_sdl2_animation_set_position(
    octaspire_sdl2_animation_t * const self,
    int const x,
    int const y,
    int const z);

int octaspire_sdl2_animation_get_x(
    octaspire_sdl2_animation_t const * const self);

int octaspire_sdl2_animation_get_y(
    octaspire_sdl2_animation_t const * const self);

int octaspire_sdl2_animation_get_z(
    octaspire_sdl2_animation_t const * const self);

void octaspire_sdl2_animation_set_visible(
    octaspire_sdl2_animation_t * const self,
    bool const visible);

bool octaspire_sdl2_animation_is_visible(
    octaspire_sdl2_animation_t const * const self);


#ifdef __cplusplus
}
#endif

#endif

