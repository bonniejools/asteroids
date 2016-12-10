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
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loadshaders.h"
#include "main.h"
#include "player.cpp"
#include "asteroid.cpp"

#define NUMBER_OF_ASTEROIDS 10

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
    GLuint shaderProgram= LoadShader(VERTEX_SHADER_LOCATION,
            FRAGMENT_SHADER_LOCATION);
    glUseProgram(shaderProgram);

    // Seed the random number and generate asteroids.
    Asteroid *asteroids = (Asteroid *) malloc(NUMBER_OF_ASTEROIDS * sizeof(Asteroid));
    for (int i=0; i<NUMBER_OF_ASTEROIDS; i++) {
        asteroids[i] = Asteroid(shaderProgram, 3);
    }
    Player player = Player(shaderProgram);

    // Create the camera
    glm::mat4 view = glm::lookAt(
                glm::vec3(1.2f, 1.2f, 1.2f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f)
            );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    auto last_frame_time = std::chrono::high_resolution_clock::now();

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Close window if 'esc' key is pressed

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            player.rotate(-0.1);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            player.rotate(0.1);

        // Update the game objects
        auto current_time = std::chrono::high_resolution_clock::now();
        float time_delta = std::chrono::duration<double, std::milli>(current_time - last_frame_time).count();
        last_frame_time = current_time;
        for (int i=0; i<NUMBER_OF_ASTEROIDS; i++)
            asteroids[i].Update(time_delta / 1000);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i=0; i<NUMBER_OF_ASTEROIDS; i++)
            asteroids[i].Draw();
        player.Draw();

    }

    glfwTerminate();
    return 0;
}

