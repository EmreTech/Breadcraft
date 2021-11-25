#include <utils/keyboard.hpp>

#include <algorithm>

Keyboard::Keyboard()
{
    std::fill(keys.begin(), keys.end(), 0);
}

Keyboard& Keyboard::getInstance()
{
    static Keyboard k;
    return k;
}

void Keyboard::updateKey(int id, int pressed)
{
    int actualPressed = pressed;
    if (actualPressed < 0)
        actualPressed = 0;
    if (actualPressed > 2)
        actualPressed = 2;

    keys[id] = actualPressed;
}

int Keyboard::getKey(int id)
{
    return keys[id];
}