#version 150

in vec2 position;

uniform mat4 scale;
uniform mat4 model; // Model should be rotation * scale * translation
uniform mat4 trans;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * trans * scale * model * vec4(position.x, position.y , 0.0, 1.0);
}
