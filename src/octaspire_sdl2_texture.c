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
#include "octaspire/sdl2-utils/octaspire_sdl2_texture.h"
#include <assert.h>
#include <octaspire/core/octaspire_helpers.h>
#include <octaspire/core/octaspire_container_utf8_string.h>
#include <octaspire/core/octaspire_memory.h>

struct octaspire_sdl2_texture_t
{
    octaspire_memory_allocator_t      *allocator;
    octaspire_container_utf8_string_t *path;
    SDL_Texture                       *texture;
    size_t                             width;
    size_t                             height;
};

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_path(
    char const * const path,
    bool const blend,
    SDL_Renderer *renderer,
    octaspire_stdio_t *stdio,
    octaspire_memory_allocator_t *allocator)
{
    size_t bufferLength = 0;
    char *buffer = octaspire_helpers_path_to_buffer(path, &bufferLength, allocator, stdio);

    if (!buffer)
    {
        return 0;
    }

    octaspire_sdl2_texture_t *result =
        octaspire_sdl2_texture_new_from_buffer(buffer, bufferLength, path, blend, renderer, allocator);

    free(buffer);
    buffer = 0;

    return result;
}

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_buffer(
    void const * const buffer,
    size_t const bufferLengthInOctets,
    char const * const name,
    bool const blend,
    SDL_Renderer *renderer,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_sdl2_texture_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_texture_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->path      = octaspire_container_utf8_string_new(name, allocator);

    if (!self->path)
    {
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

#ifdef OCTASPIRE_SDL2_UTILS_USE_SDL_IMAGE_LIBRARY
    SDL_Surface *imageSurface = IMG_Load_RW(SDL_RWFromConstMem(buffer, bufferLengthInOctets), 1);
#else
    SDL_Surface *imageSurface = SDL_LoadBMP_RW(SDL_RWFromConstMem(buffer, bufferLengthInOctets), 1);
#endif

    if (!imageSurface)
    {
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

    self->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    if (!self->texture)
    {
        printf("Texture \"%s\" cannot be created: %s\n", name, SDL_GetError());
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

    self->width  = imageSurface->w;
    self->height = imageSurface->h;

    SDL_FreeSurface(imageSurface);
    imageSurface = 0;

    if (blend)
    {
        if (SDL_SetTextureBlendMode(self->texture, SDL_BLENDMODE_BLEND) < 0)
        {
            abort();
        }
    }

    return self;
}

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_color_keyed_from_path(
    char const * const path,
    uint8_t const red,
    uint8_t const green,
    uint8_t const blue,
    SDL_Renderer *renderer,
    octaspire_stdio_t *stdio,
    octaspire_memory_allocator_t *allocator)
{
    size_t bufferLength = 0;
    char *buffer = octaspire_helpers_path_to_buffer(path, &bufferLength, allocator, stdio);

    if (!buffer)
    {
        return 0;
    }

    octaspire_sdl2_texture_t *result = octaspire_sdl2_texture_new_color_keyed_from_buffer(
        buffer,
        bufferLength,
        path,
        red,
        green,
        blue,
        renderer,
        allocator);

    free(buffer);
    buffer = 0;

    return result;
}

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_color_keyed_from_buffer(
    void const * const buffer,
    size_t const bufferLengthInOctets,
    char const * const name,
    uint8_t const red,
    uint8_t const green,
    uint8_t const blue,
    SDL_Renderer *renderer,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_sdl2_texture_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_texture_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->path      = octaspire_container_utf8_string_new(name, allocator);

    if (!self->path)
    {
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

#ifdef OCTASPIRE_SDL2_UTILS_USE_SDL_IMAGE_LIBRARY
    SDL_Surface *imageSurface = IMG_Load_RW(SDL_RWFromConstMem(buffer, bufferLengthInOctets), 1);
#else
    SDL_Surface *imageSurface = SDL_LoadBMP_RW(SDL_RWFromConstMem(buffer, bufferLengthInOctets), 1);
#endif

    if (!imageSurface)
    {
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

    SDL_SetColorKey(imageSurface, 1, SDL_MapRGB(imageSurface->format, red, green, blue));

    self->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    if (!self->texture)
    {
        printf("Texture \"%s\" cannot be created: %s\n", name, SDL_GetError());
        octaspire_sdl2_texture_release(self);
        self = 0;
        return self;
    }

    self->width  = imageSurface->w;
    self->height = imageSurface->h;

    SDL_FreeSurface(imageSurface);
    imageSurface = 0;

    return self;
}

void octaspire_sdl2_texture_release(octaspire_sdl2_texture_t *self)
{
    if (!self)
    {
        return;
    }

    SDL_DestroyTexture(self->texture);
    octaspire_container_utf8_string_release(self->path);
    octaspire_memory_allocator_free(self->allocator, self);
}

void octaspire_sdl2_texture_render_at_position_clip(
    octaspire_sdl2_texture_t const * const self,
    SDL_Renderer *renderer,
    int const origoX,
    int const origoY,
    int const x,
    int const y,
    SDL_Rect const * const src)
{
    SDL_Rect dst = {origoX + x, origoY + y, self->width, self->height};

    if (src)
    {
        dst.w = src->w;
        dst.h = src->h;
    }

    SDL_RenderCopy(renderer, self->texture, src, &dst);
}

size_t octaspire_sdl2_texture_get_width(
    octaspire_sdl2_texture_t const * const self)
{
    return self->width;
}

size_t octaspire_sdl2_texture_get_height(
    octaspire_sdl2_texture_t const * const self)
{
    return self->height;
}

void octaspire_sdl2_texture_print(
    octaspire_sdl2_texture_t const * const self)
{
    assert(self);

    printf(
        "texture \"%s\" %zu x %zu\n",
        octaspire_container_utf8_string_get_c_string(self->path),
        self->width,
        self->height);
}

