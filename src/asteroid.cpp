#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>

GLfloat asteroidVertices[] = {
    //  x       y
     0.2f,   0.125f,
     0.075f, -0.125f,
     0.2f,  -0.0625f,
     0.325f, -0.125f,
};

GLuint asteroidElements[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0
};


class Asteroid
{
    float rotation = 0;
    GLuint vao;
    GLuint vbo;
    GLint posAttrib;
    GLuint program;
    GLuint ebo;

    public:
    Asteroid(GLuint program)
    {
        // Initialise buffers
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        // Upload to GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glBufferData(GL_ARRAY_BUFFER, sizeof(asteroidVertices), asteroidVertices, GL_STATIC_DRAW);
        posAttrib = glGetAttribLocation(program, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                2*sizeof(float), 0);

        // Create Ebo
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(asteroidElements),
                asteroidElements, GL_STATIC_DRAW);

        this->program = program;

        return;
    }

    void Draw() {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
        posAttrib = glGetAttribLocation(program, "position");
        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

        return;
    }
};

