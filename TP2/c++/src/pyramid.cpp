#include "Pyramid.h"

#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

Pyramid::Pyramid(Shader* shader_program) : shader_program_(shader_program->get_id()) {

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

void Pyramid::draw() {

    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);

    float Translate = 3.0f;
    glm::vec3 const& Rotate = {2*glfwGetTime(),0,0};

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    View = glm::rotate(View, Rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.41f, 1.0f));
    View *= Model;

    GLint viewMatrixLocation = glGetUniformLocation(shader_program_, "view");
    //std::cout << viewMatrixLocation << std::endl;
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &View[0][0]);
    GLint projectionMatrixLocation = glGetUniformLocation(shader_program_, "projection");
    //std::cout << projectionMatrixLocation << std::endl;
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &Projection[0][0]);

    /* draw points 0-3 from the currently bound VAO with current in-use shader */
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void Pyramid::key_handler(int key) {
    return;
}

