#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL.h>

struct SpriteComponent
{
    std::string assetId;
    int width;
    int height;
    int zindex;
    bool isFixed;
    SDL_Rect srcRect;
    SDL_RendererFlip flip;

    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int zindex = 0, bool isFixed = false, int srcRectX = 0, int srcRectY = 0 )
    {
        this->assetId = assetId;
        this->height = height;
        this->width = width;
        this->zindex = zindex;
        this->flip = SDL_FLIP_NONE;
        this->srcRect = {srcRectX, srcRectY, width, height};
        this->isFixed = isFixed;
    }
};

#endif