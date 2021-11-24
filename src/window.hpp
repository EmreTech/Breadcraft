#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void setupCallbacks();

namespace Window
{

bool init();
GLFWwindow *getWindow();

} // namespace Window