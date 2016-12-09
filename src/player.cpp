#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>

#include "entity.h"


// x,y coords
GLfloat spaceshipVertices[] = {
    0.0f,  1.0f,
    1.0f, -1.0f,
    0.0f, -0.5f,
    -1.0f,-1.0f
};

GLuint spaceshipElements[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0
};

class Player : public Entity {
    public:

    Player(GLuint shaderProgram)
        : Entity(shaderProgram)
    {
        this->vertices = spaceshipVertices;
        this->verticesSize = sizeof(spaceshipVertices);
        this->elements = spaceshipElements;
        this->elementsSize = sizeof(spaceshipElements);

        this->setScaling(0.05);
    }
};

