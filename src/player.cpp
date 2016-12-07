#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <math.h>

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

class Player
{
    float rotation = 0;
    GLuint vao;
    GLuint vbo;
    GLint posAttrib;
    GLuint program;
    GLuint ebo;

    float scaling_x = 0.05;
    float scaling_y = 0.05;

    public:
    Player(GLuint program)
    {
        // Initialise buffers
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
        this->program = program;

        // Run scaling
        for (int i=0; i<4; i++) {
            spaceshipVertices[2*i]       *= scaling_x;
            spaceshipVertices[(2*i) + 1] *= scaling_y;
        }

        // Upload to GPU
        this->Upload();

        return;
    }

    void Upload() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(spaceshipVertices),
                spaceshipVertices,
                GL_STATIC_DRAW);
	posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		2*sizeof(float), 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spaceshipElements),
                spaceshipElements, GL_STATIC_DRAW);
    }

    void Rotate(float rot) {
        for (int i=0; i<4; i++) {
            float curr_x = spaceshipVertices[2*i];
            float curr_y = spaceshipVertices[2*i + 1];
            spaceshipVertices[2*i] = cos(rot)*curr_x - sin(rot)*curr_y;
            spaceshipVertices[2*i + 1] = sin(rot)*curr_x + cos(rot)*curr_y;
        }

        this->Upload();
    }

    void Draw() {
        // Bind relevant buffers and redraw
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

        return;
    }
};

