#include <utils/delta_counter.hpp>

DeltaCounter& DeltaCounter::getInstance()
{
    static DeltaCounter dc;
    return dc;
}

void DeltaCounter::update()
{
    float currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;
}