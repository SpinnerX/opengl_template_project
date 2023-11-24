#include "../include/Application.h"
using namespace std;

Application* Application::CreateWindow(int w, int h, string name){
    return new Application(Window::init(w, h, name));
}

void Application::mainloop(){
    while(isRunning){
            std::cerr << "mainloop running...\n";
            
            window->run();

            isRunning = window->windowState(); // This helps us check the state of the window if it is open.
        }
}

