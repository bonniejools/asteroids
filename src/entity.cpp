#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entity.h"

Entity::Entity() {}
Entity::Entity(GLuint shaderProgram)
{
    this->shaderProgram = shaderProgram;

    // Initialize buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void Entity::Draw() {
    this->Upload();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, elementsSize, GL_UNSIGNED_INT, 0);

    return;
}

void Entity::Upload()
{
    // Bind the vertex buffer and upload vertices.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glBufferData(
            GL_ARRAY_BUFFER,
            verticesSize,
            vertices,
            GL_STATIC_DRAW);

    // Define vertices as positions
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
            2*sizeof(float), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize,
            elements, GL_STATIC_DRAW);

    // Upload scaling matrix
    GLint uniScale = glGetUniformLocation(shaderProgram, "scale");
    glUniformMatrix4fv(uniScale, 1, GL_FALSE, glm::value_ptr(scale));

    // Upload model(rotation) matrix
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    // Upload model(rotation) matrix
    GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
}

void Entity::setScaling(float scalar)
{
    scale = glm::scale(scale, glm::vec3(scalar, scalar, scalar));
}

void Entity::rotate(float radians)
{
    model = glm::rotate(model, radians, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::setPosition(float x, float y)
{
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
}

