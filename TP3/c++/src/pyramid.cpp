#include "Pyramid.h"
#include "shape.h"

#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

Pyramid::Pyramid(Shader* shader_program) : Shape(shader_program) {

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.5f, -0.0f,      1.0f, 0.0f, 0.0f,//top
        0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 1.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,

        1, 2, 3,
        1, 3, 4
    };

    num_indices = 18;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);


    glEnableVertexAttribArray(1);
    GLintptr offset = 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offset);

}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Pyramid::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLE_STRIP, this->num_indices, GL_UNSIGNED_INT, 0);
}


void Pyramid::key_handler(int key) {
    return;
}

