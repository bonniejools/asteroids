#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <SOIL/SOIL.h>
#include <math.h>
#include <chrono>
#include <ctime>

#include "loadshaders.h"
#include "main.h"
#include "player.cpp"
#include "asteroid.cpp"

int main()
{
    using namespace std;

    // Creates the GLFW context.
    // GLFW creates a window with an OpenGL context.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_TITLE, nullptr,
            nullptr);
    glfwMakeContextCurrent(window);

    // GLEW links to gpu functions
    glewExperimental = GL_TRUE;
    glewInit();

    // Loads vertex & fragment shaders
    GLuint program = LoadShader(VERTEX_SHADER_LOCATION,
            FRAGMENT_SHADER_LOCATION);
    glUseProgram(program);

    // Make vbo the current object with glBindBuffer() and then 'upload' data to it.
    // GL_STATIC_DRAW means that the vertex data will be uploaded once and then
    // drawn lots and lots of times.

    Asteroid asteroid = Asteroid(program, 3);
    Player player = Player(program);

    auto last_frame_time = std::chrono::high_resolution_clock::now();

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Close window if 'esc' key is pressed

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            player.Rotate(0.1);

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            player.Rotate(-0.1);

        // Update the game objects
        auto current_time = std::chrono::high_resolution_clock::now();
        float time_delta = std::chrono::duration<double, std::milli>(current_time - last_frame_time).count();
        last_frame_time = current_time;
        asteroid.Update(time_delta / 1000.0);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        asteroid.Draw();
        player.Draw();

    }

    glfwTerminate();
    return 0;
}

