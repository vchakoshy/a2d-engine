#ifndef DAMAGE_SYSTEM_H
#define DAMAGE_SYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System
{
public:
    DamageSystem()
    {
        RequireComponent<BoxColliderComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
    }

    void onCollision(CollisionEvent &event)
    {
        Entity a = event.a;
        Entity b = event.b;
        Logger::Log("the damage system received collision");

        if (a.BelongsToGroup("projectiles") && b.HasTag("player"))
        {
            OnProjectileHitsPlayer(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.HasTag("player"))
        {
            OnProjectileHitsPlayer(b, a);
        }

        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies"))
        {
            OnProjectileHitsEnemy(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies"))
        {
            OnProjectileHitsEnemy(b, a);
        }
    }

    void OnProjectileHitsEnemy(Entity projectile, Entity enemy)
    {
         auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (!projectileComponent.isFriendly)
        {
            return;
        }

        auto &health = enemy.GetComponent<HealthComponent>();
        health.healthPercentage -= projectileComponent.hitPercentDamage;

        if (health.healthPercentage <= 0)
        {
            enemy.Kill();
        }

        projectile.Kill();
    }

    void OnProjectileHitsPlayer(Entity projectile, Entity player)
    {
        auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (projectileComponent.isFriendly)
        {
            return;
        }

        auto &health = player.GetComponent<HealthComponent>();
        health.healthPercentage -= projectileComponent.hitPercentDamage;

        if (health.healthPercentage <= 0)
        {
            player.Kill();
        }

        projectile.Kill();
    }

    void Update() {

    };
};

#endif