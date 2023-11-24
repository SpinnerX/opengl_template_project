#include <iostream>
#include <GLFW/glfw3.h>
#include <cstring>
#include <cmath>
#include <cstdlib>

class Window;

class KeyEventHandler{
    // Make it easier to call glfw key codes.
    enum Keys{
        ESCAPE=GLFW_KEY_ESCAPE, // escape key
        UP=GLFW_KEY_UP, // arrow up
        DOWN=GLFW_KEY_DOWN, // arrow down
        RIGHT=GLFW_KEY_RIGHT, // arrow right
        LEFT=GLFW_KEY_LEFT, // arrow left
        W=GLFW_KEY_W,  // W key
        A=GLFW_KEY_A, // A key
        S=GLFW_KEY_S, // S key
        D=GLFW_KEY_D, // D key
        PRESSED=GLFW_PRESS // key pressed
    };
public:

    KeyEventHandler* instance() { return new KeyEventHandler(); }

    void update(Window* window);

private:
    // boolean indicator that this specific key has been pressed!
    bool pressed(Window* window, Keys keys);
};