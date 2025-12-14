#version 330 core

// input attribute variable, given per vertex
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

// global matrix variables
uniform mat4 view;
uniform mat4 projection;

// color given to the fragment shader
out vec3 fragColor;

void main() {
    fragColor = color;
    gl_Position = projection * view * vec4(position, 1);
}
