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
#ifndef OCTASPIRE_SDL2_TEXTURE_H
#define OCTASPIRE_SDL2_TEXTURE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_sdl2_texture_t octaspire_sdl2_texture_t;

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_path(
    char const * const path,
    bool const blend,
    SDL_Renderer *renderer,
    octaspire_stdio_t *stdio,
    octaspire_memory_allocator_t *allocator);

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    char const * const name,
    bool const blend,
    SDL_Renderer *renderer,
    octaspire_memory_allocator_t *allocator);

void octaspire_sdl2_texture_release(octaspire_sdl2_texture_t *self);

void octaspire_sdl2_texture_render_at_position_clip(
    octaspire_sdl2_texture_t const * const self,
    SDL_Renderer *renderer,
    int const origoX,
    int const origoY,
    int const x,
    int const y,
    SDL_Rect const * const src);

size_t octaspire_sdl2_texture_get_width(
    octaspire_sdl2_texture_t const * const self);

size_t octaspire_sdl2_texture_get_height(
    octaspire_sdl2_texture_t const * const self);

void octaspire_sdl2_texture_print(
    octaspire_sdl2_texture_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

