#ifndef ASTER_ENTITY
#define ASTER_ENTITY

class Entity
{
    GLuint shaderProgram;
    glm::mat4 model; // The rotation
    glm::mat4 scale; // The scaling
    glm::mat4 trans; // The translation
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    public:
    Entity(GLuint shaderProgram);
    Entity();

    GLfloat *vertices;
    GLuint *elements;
    int verticesSize;
    int elementsSize;
    void setScaling(float scalar);
    void rotate(float radians);
    void setPosition(float x, float y);
    void Draw();

    private:
    void Upload();
};

#endif
