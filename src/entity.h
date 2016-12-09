#ifndef ASTER_ENTITY
#define ASTER_ENTITY

class Entity
{
    GLuint shaderProgram;
    glm::mat4 model; // The rotation
    glm::mat4 scale; // The scaling
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    public:
    Entity(GLuint shaderProgram);

    GLfloat *vertices;
    GLuint *elements;
    int verticesSize;
    int elementsSize;
    void setScaling(float scalar);
    void rotate(float radians);
    void Draw();

    private:
    void Upload();
};

#endif
