#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#define MAX_ASTEROID_SIZE 6
using namespace std;

class Asteroid : public Entity
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

    // Generate a random asteroid
    void Generate()
    {
        for (int i=0; i<8; i++) {
            float distance = (rand() % 25) / 125.0; // 0.0 - 0.1
            distance += 0.8; // 0.8 - 1.0
            float angle = i * 2 * M_PI / 8;

            asteroidVertices[2*i] = distance * sin(angle);
            asteroidVertices[2*i + 1] = distance * cos(angle);
        }

        return;
    }

    void setRandomPosition()
    {
        float rand_x = (rand() % 1000) / 1000.0;
        float rand_y = (rand() % 1000) / 1000.0;

        rand_x = rand_x < 0.5 ? rand_x - 1.0 : rand_x;
        rand_y = rand_y < 0.5 ? rand_y - 1.0 : rand_y;

        this->setPosition(rand_x, rand_y);
    }

    void setRandomDirection()
    {
        this->direction = (rand() % ((int) (M_PI * 1000))) / 1000.0;
    }

    public:
    Asteroid(GLuint program, int size)
        : Entity(program)
    {
        // Generate the asteroid
        this->Generate();
        this->vertices = asteroidVertices;
        this->verticesSize = sizeof(asteroidVertices);
        this->elements = asteroidElements;
        this->elementsSize = sizeof(asteroidElements);

        this->setScaling(1.0 / (1 << (MAX_ASTEROID_SIZE - size)));

        this->setRandomPosition();
        this->setRandomDirection();
        this->speed = 0.1;

        return;
    }

    void Update(float time_delta)
    {
        Entity::Update(time_delta);

        if (abs(position.x) > 1.15)
        {
            position.x = -position.x;
        }

        if (abs(position.y) > 1.15)
        {
            position.y = -position.y;
        }
        return;
    }
};

