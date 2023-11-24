#include <iostream>
#include "include/Application.h"
#include <cmath>
#include <random>


int main(){
    Application* app = Application::CreateWindow(600, 480, "Window #1");
    app->mainloop();
}
