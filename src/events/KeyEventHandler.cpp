#include "../../include/events/KeyEventHandler.h"
#include "../../include/core/Window.h"
using namespace std;

void KeyEventHandler::update(Window* other){
    GLFWwindow* window = other->windowData();
}

bool KeyEventHandler::pressed(Window* window, Keys keys){
    return glfwGetKey(window->windowData(), keys) == GLFW_PRESS;
}