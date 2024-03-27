#ifndef CAMERA_MOVEMENT_SYSTEM_H
#define CAMERA_MOVEMENT_SYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformCompnent.h"
#include <SDL2/SDL.h>

class CameraMovementSystem: public System {
public:
    CameraMovementSystem(){
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(SDL_Rect &camera){
        for (auto entity: GetSystemEntities()){
            auto transform = entity.GetComponent<TransformComponent>();
            camera.x = transform.position.x;
            camera.y = transform.position.y;
        }

    }

};

#endif 