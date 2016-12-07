#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#define MAX_ASTEROID_SIZE 6
using namespace std;

class Asteroid
{
    GLfloat asteroidVertices[16];

    GLuint asteroidElements[16] = {
        0, 1,
        1, 2,
        2, 3,
        3, 4,
        4, 5,
        5, 6,
        6, 7,
        7, 0
    };

    float rotation = 0;
    GLuint vao;
    GLuint vbo;
    GLint posAttrib;
    GLuint program;
    GLuint ebo;
    int size;

    float speed; // distance/s
    float direction; // radians

    // Generate a random asteroid
    void Generate()
    {
        for (int i=0; i<8; i++) {
            float distance = (rand() % 25) / 125.0; // 0.0 - 0.1
            distance += 0.8; // 0.8 - 1.0
            distance /= 1 << (MAX_ASTEROID_SIZE - size);
            float angle = i * 2 * M_PI / 8;

            asteroidVertices[2*i] = distance * sin(angle);
            asteroidVertices[2*i + 1] = distance * cos(angle);
        }

        speed = 0.1;
        this->SetRandomDirection();
        this->MoveToStartingPosition();

        return;
    }

    void SetRandomDirection() {
        direction = rand() % (int) (2 * M_PI * 1000);
        direction /= 1000;
    }

    void MoveToStartingPosition() {
        float start_x = (rand() % 100) / 100.0;
        start_x = start_x < 0.5 ? -1.0 + start_x : start_x;
        float start_y = (rand() % 100) / 100.0;
        start_y = start_y < 0.5 ? -1.0 + start_y : start_y;

        SetPosition(start_x, start_y);
    }

    public:

    float x = 0.0;
    float y = 0.0;

    Asteroid() {return;}
    Asteroid(GLuint program, int size)
    {
        this->program = program;
        this->size    = size;

        // Initialise buffers
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        // Generate the asteroid
        this->Generate();

        // Upload to GPU
        this->Upload();

        // Create Ebo
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(asteroidElements),
                asteroidElements, GL_STATIC_DRAW);

        return;
    }

    void Draw() {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, sizeof(asteroidElements), GL_UNSIGNED_INT, 0);

        return;
    }

    void Upload() {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glBufferData(GL_ARRAY_BUFFER, sizeof(asteroidVertices), asteroidVertices, GL_STATIC_DRAW);
        posAttrib = glGetAttribLocation(program, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                2*sizeof(float), 0);
    }

    // Set the position
    void SetPosition(float x, float y)
    {
        float diff_x = x - this->x;
        float diff_y = y - this->y;

        for (int i=0; i<8; i++) {
            asteroidVertices[2*i] += diff_x;
            asteroidVertices[2*i + 1] += diff_y;
        }

        this->x = x;
        this->y = y;
        this->Upload();

        return;
    }

    void Update(float delta) {
        float d_x = delta * speed * sin(direction);
        float d_y = delta * speed * cos(direction);
        SetPosition(x+d_x, y+d_y);
        this->x += d_x;
        this->y += d_y;
    }
};

