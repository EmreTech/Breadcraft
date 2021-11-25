#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/singleton.hpp>

struct DeltaCounter
{
    float delta;

    NON_COPYABLE(DeltaCounter)
    NON_MOVABLE(DeltaCounter)

    static DeltaCounter& getInstance();

    void update();

    private:
    DeltaCounter() {}

    float lastFrame;
};