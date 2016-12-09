#version 150

in vec2 position;

uniform mat4 scale;
uniform mat4 model;

void main()
{
    gl_Position = scale * model * vec4(position.x, position.y , 0.0, 1.0);
}
