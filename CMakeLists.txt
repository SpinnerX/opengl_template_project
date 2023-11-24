cmake_minimum_required(VERSION 3.15)

SET(PROJECT_NAME project)

project(${PROJECT_NAME} VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Searching for OpenGL frameworks
# OpenGL
find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include(cmake/glad.cmake)

include_directories(${GLUT_INCLUDE_DIRS} ${glad_include})

# Handling our file structures here.
# This allows us to include our libraries throughout this entire project.
# This lets us get access to our includes and headers
file(GLOB
    "main.cpp"
    "include/*.h"
    "include/core/*.h"
)



# Globalizes our *.cpp files
file(
   GLOB
   SRC
   "src/*.cpp"
   "src/core/*.cpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SRC} ${glad_src})


# Help for linking the opengl libraries
# Linking the link that helped get opengl working: 
# https://carette.xyz/posts/opengl_and_cpp_on_m1_mac/
# target_link_directories(${PROJECT_NAME} PUBLIC $(OPENGL_INCLUDE_DIR)) # Not gonna delete this commented, just so I know this wont work for future ref.

# Linking the libraries for Cocoa, OpenGL, IOKit, and glfw
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW) # This helps us get rid of the "___glewGenBuffers" reference error