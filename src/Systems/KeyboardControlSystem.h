#ifndef KEYBOARD_CONTROL_SYSTEM_H
#define KEYBOARD_CONTROL_SYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlSystem : public System
{

public:
    KeyboardControlSystem()
    {
    }

    void SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
    {
        eventBus->SubscribeToEvent<KeyPressEvent>(this, &KeyboardControlSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressEvent &event)
    {
        std::string keyCode = std::to_string(event.symbol);
        std::string keySymbol(1, event.symbol);
        Logger::Log("key pressed event emitted: [" + keyCode + "] " + keySymbol);
    }

    void Update(){
        
    }
};

#endif // KEYBOARD_CONTROL_SYSTEM_H
