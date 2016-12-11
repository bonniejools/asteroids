#include "constants.h"

class Bullet : public Entity
{
    GLfloat bulletVertices[4] = {
        0.0f, -1.0f,
        0.0f, 1.0f
    };
    GLuint bulletElements[2] = {0, 1};

    public:

    Bullet(){}
    Bullet(GLuint shaderProgram, float direction)
        : Entity(shaderProgram)
    {
        this->vertices = bulletVertices;
        this->verticesSize = sizeof(bulletVertices);
        this->elements = bulletElements;
        this->elementsSize = sizeof(bulletElements);

        this->setScaling(0.03);
        this->speed = BULLET_SPEED;

        this->direction = -direction;
        this->setRotation(direction);
    }
};

