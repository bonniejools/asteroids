#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#ifndef ASTER_ENTITY
#define ASTER_ENTITY

class Entity
{
    public:
    GLfloat *vertices;
    GLuint *elements;
    int verticesSize;
    int elementsSize;
    float direction = 0.0;
    float speed     = 0.0;
    glm::vec3 position;

    Entity(GLuint shaderProgram);
    Entity();
    void setScaling(float scalar);
    void rotate(float radians);
    void setRotation(float radians);
    void setPosition(float x, float y);
    void Draw();
    void Update(float time_delta);


    private:
    void Upload();
    GLuint shaderProgram;
    glm::mat4 model; // The rotation
    glm::mat4 scale; // The scaling
    glm::mat4 trans; // The translation
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};

#endif

