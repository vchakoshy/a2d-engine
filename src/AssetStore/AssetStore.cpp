#include "AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore(){
    Logger::Log("asset store constructor called");
}

AssetStore::~AssetStore(){
    ClearAssets();
    Logger::Log("asset store destructor called");
}

void AssetStore::ClearAssets(){
    for (auto texture: textures){
        SDL_DestroyTexture(texture.second);
    }

    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer,  const std::string& assetId , const std::string& filepath){
    SDL_Surface* surface =  IMG_Load(filepath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_free(surface);

    textures.emplace(assetId, texture);
    Logger::Log("new texture added to asset store");
}

SDL_Texture* AssetStore::GetTexture(const std::string & assetId) {
    return textures[assetId];
}
