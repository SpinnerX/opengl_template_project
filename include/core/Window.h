#include <iostream>
#include <cstring>
#if __APPLE__ // This is to disable deprecation warnings from opengl
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#endif

class Window{
    friend class Application;

    // For right now WindowSpecifications hold window name, width, and height.
    // Eventually may want to handle how pixels to be rendered, etc. (for future ref)
    struct WindowSpecifications{
        WindowSpecifications(int w=0, int h=0, std::string name=""){
            width = w, height=h;
            this->name = name;
        }
        int width, height;
        std::string name;
    };

    Window(GLFWwindow* _window, WindowSpecifications&& _specs) : window(_window), specs(_specs), windowOpen(true){}
public:

    ~Window() = default;

    // Hels us create different instances of the window
    // lets us constantly create an instance of window, since opengl has to using glfwCreateWindow() to initialize in building a window.
    static Window* init(int w, int h, std::string name) {
        if(!glfwInit()){
            std::cerr << "[ERROR] Initialized GLFW not successful!\n";
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // This may be replaced with logging in the future once logger framework is implemented.
        std::cerr << "[INFO] Initializing window: " << name << " successful!\n";

        // WindowProperties winProp = WindowProperties(w, h, name);

        GLFWwindow* window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
        return new Window(window, WindowSpecifications(w, h, name));
    }

    GLFWwindow* windowData(){ return this->window; } // grabs our windows internal GLFWwindow ptr.

    void run(); // Windows mainloop.

    // Just some getters to access specific window properties.
    std::string name() const { return specs.name; }

    // width() and height() grabs the dimensions of the window.
    int width() const { return specs.width; }

    int height() const { return specs.height; }

    bool windowState() const { return windowOpen; }

    std::string to_string(){ return std::to_string(width()) + " x " + std::to_string(height()) + ": " + name(); }


    // Just being able to print directly to_string without making a function call, for simplicity.
    friend std::ostream& operator<<(std::ostream& outs, Window& window){
        outs << window.to_string() << '\n';
        return outs;
    }

private:
    bool windowClose() const { return !glfwWindowShouldClose(window); } // Check if the window is closing

    void clear() { glClear(GL_COLOR_BUFFER_BIT); } // clearing the windows buffer.

    void update(); // updating window events.

protected:
    GLFWwindow* window; // Window pointer to creating a window in this class.
    WindowSpecifications specs; // handles grabbing window properties.

    bool windowOpen;
};