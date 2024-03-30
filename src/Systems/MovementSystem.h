#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../Components/TransformCompnent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System
{
public:
    MovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime)
    {
        for (auto entity : GetSystemEntities())
        {
            auto &transform = entity.GetComponent<TransformComponent>();
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidBody.velocity.x * deltaTime;
            transform.position.y += rigidBody.velocity.y * deltaTime;

            bool isEntityOutsideMap = (transform.position.x < 0 ||
                                       transform.position.x > Game::mapWidth ||
                                       transform.position.y < 0 ||
                                       transform.position.y > Game::mapHeight);

            if (isEntityOutsideMap && !entity.HasTag("player"))
            {
                entity.Kill();
            }
        }
    }
};

#endif