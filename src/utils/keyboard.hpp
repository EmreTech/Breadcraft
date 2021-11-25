#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/singleton.hpp>
#include <array>

/**
 * Wrapper for keyboard functions in GLFW.
 * 0 = GLFW_RELEASE
 * 1 = GLFW_PRESS
 * 2 = GLFW_REPEAT
 */

struct Keyboard
{
    NON_COPYABLE(Keyboard)
    NON_MOVABLE(Keyboard)

    static Keyboard& getInstance();

    void updateKey(int id, int pressed);
    int getKey(int id);

    private:
    Keyboard();

    std::array<int, GLFW_KEY_LAST> keys;
};