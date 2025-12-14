#include "cylinder.h"

#include <vector>
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#ifndef PI
#define PI 3.141592653589793
#endif

Cylinder::Cylinder(float height, float radius, int slices, Shader *shader_program) : shader_program_(shader_program->get_id()) {

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    // generate vertices
    for (int i = 0; i < slices; i++) {
        float theta = 2.0f * glm::pi<float>() * static_cast<float>(i) / static_cast<float>(slices);
        float x = radius * glm::cos(theta);
        float y = radius * glm::sin(theta);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.5f * height);
        //rgb
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(-0.5f * height);
        //rgb
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
    }

    // add top and bottom vertices
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.5f * height);
    //rgb
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-0.5f * height);
    //rgb
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);

    // generate indices
    for (int i = 0; i < slices; i++) {
        indices.push_back(2 * i);
        indices.push_back(2 * i + 1);
        indices.push_back((2 * i + 2) % (2 * slices));
        indices.push_back(2 * i + 1);
        indices.push_back((2 * i + 3) % (2 * slices));
        indices.push_back((2 * i + 2) % (2 * slices));
        indices.push_back(2 * i);
        indices.push_back((2 * i + 2) % (2 * slices));
        indices.push_back(-2);
        indices.push_back(2 * i + 1);
        indices.push_back(-1);
    }

    //for (auto i : indices)
        //std::cout << i << ' ';

    index_count = indices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(1);
    GLintptr offset = 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offset);

}

Cylinder::~Cylinder() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Cylinder::draw() {

    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);

    glm::vec3 const& Translate = { -4.0f,0.0f,-10.0f };
    glm::vec3 const& Rotate = { 2 * glfwGetTime(),0.5f * glfwGetTime(),0 };

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), Translate);
    View = glm::rotate(View, Rotate.y, glm::vec3(1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    View = glm::rotate(View, Rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Model = glm::scale(glm::mat4(4.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    View *= Model;

    GLint viewMatrixLocation = glGetUniformLocation(shader_program_, "view");
    //std::cout << viewMatrixLocation << std::endl;
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &View[0][0]);
    GLint projectionMatrixLocation = glGetUniformLocation(shader_program_, "projection");
    //std::cout << projectionMatrixLocation << std::endl;
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &Projection[0][0]);

    /* draw points 0-3 from the currently bound VAO with current in-use shader */
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, 0);
}

void Cylinder::key_handler(int key) {
    return;
}

