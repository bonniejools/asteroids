#include <math.h>
#include "constants.h"
#include "asteroid.h"

#define NUM_ASTEROID_VERTICES 8

Asteroid::Asteroid() {}
Asteroid::Asteroid(GLuint shaderProgram, int size)
    : Entity(shaderProgram)
{
    // Generate the asteroid
    this->vertices = (GLfloat *) malloc(2 * NUM_ASTEROID_VERTICES * sizeof(float));
    this->Generate();

    this->verticesSize = sizeof(asteroidVertices);
    this->elements = asteroidElements;
    this->elementsSize = sizeof(asteroidElements);

    this->setScaling(1.0 / (1 << (MAX_ASTEROID_SIZE - size)));

    this->setRandomPosition();
    this->setRandomDirection();
    this->speed = ASTEROID_SPEED;

    return;
}

// Generate a random asteroid
void Asteroid::Generate()
{
    for (int i=0; i<NUM_ASTEROID_VERTICES; i++) {
        float distance = (rand() % 25) / 125.0; // range 0.0 - 0.1
        distance += 0.8; // 0.8 - 1.0
        float angle = i * 2 * M_PI / NUM_ASTEROID_VERTICES;

        vertices[2*i] = distance * sin(angle);
        vertices[2*i + 1] = distance * cos(angle);
    }

    return;
}

void Asteroid::setRandomPosition()
{
    float rand_x = (rand() % 1000) / 1000.0;
    float rand_y = (rand() % 1000) / 1000.0;

    rand_x = rand_x < 0.5 ? rand_x - 1.0 : rand_x;
    rand_y = rand_y < 0.5 ? rand_y - 1.0 : rand_y;

    this->setPosition(rand_x, rand_y);
}

void Asteroid::setRandomDirection()
{
    this->direction = (rand() % ((int) (M_PI * 1000))) / 1000.0;
}

void Asteroid::Update(float time_delta)
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

