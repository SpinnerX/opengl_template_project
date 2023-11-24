#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
using namespace std;

const char* vertexSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 a_Position;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);	
        }
)";

const char* fragmentSrc = R"(
    #version 330 core
    layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
)";


int quickExampleOfDrawingATriangle(){

    if(!glfwInit()){
        printf("Does not initialize correctly!\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 480, "Window", nullptr, nullptr);

    if(!window){
        printf("Window doesnt work!\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    
    unsigned int _vertexArr, _vertexBuffer, _vertexIndex;

    glGenVertexArrays(1, &_vertexArr);
    glBindVertexArray(_vertexArr);

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

    float vertices[3 * 3] = {
        -0.1f, -0.1f, 0.0f,
            0.1f, -0.1f, 0.0f,
            0.0f,  0.1f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &_vertexIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexIndex);

    unsigned int indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // SHADERS STUFFFF!

    // Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(_vertexArr);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
