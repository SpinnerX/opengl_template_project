#include <iostream>
#include <cstring>
#include "core/Window.h"
#include "events/KeyEventHandler.h"
#include <memory>

// Application is the main of this entire project application

class Application{
    Application(Window* _window) : window(_window), isRunning(window->windowState()){}
public:
    ~Application() = default;

    // Helps initializes on creating a window. Among other things.
    static Application* CreateWindow(int w, int h, std::string name);

    void mainloop();

    friend std::ostream& operator<<(std::ostream& outs, Application& app){
        outs << *app.window << '\n';
        return outs;
    }

private:
    

private:
    Window* window;

    KeyEventHandler keyHandler;

    bool isRunning;
};