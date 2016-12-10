#version 150

in vec2 position;

uniform mat4 scale;
uniform mat4 model;
uniform mat4 trans;

void main()
{
    gl_Position = trans * scale * model * vec4(position.x, position.y , 0.0, 1.0);
}
