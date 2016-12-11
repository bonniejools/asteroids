#include "entity.h"

#ifndef ASTER_ASTEROID
#define ASTER_ASTEROID

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

    void Generate();
    void setRandomPosition();
    void setRandomDirection();

    public:
    Asteroid(GLuint shaderProgram, int size);
    Asteroid();
    void Update(float time_delta);
};

#endif

