#ifndef KEY_PRESSED_EVENT_H
#define KEY_PRESSED_EVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyPressEvent : public Event
{
public:
    SDL_Keycode symbol;
    KeyPressEvent(SDL_Keycode symbol) : symbol(symbol) {}
};

#endif // KEY_PRESSED_EVENT_H
