#include "sphere.h"

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

Sphere::Sphere(float radius, int sectors, int stacks, Shader* shader_program) : shader_program_(shader_program->get_id()) {

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    //VERTICES
    float x, y, z, xy;
    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i) {
        // cercle
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        y = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            z = xy * sinf(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back((x / radius + 1) * 0.5f);
            vertices.push_back((y / radius + 1) * 0.5f);
            vertices.push_back((z / radius + 1) * 0.5f);
        }
    }

    //for (auto i : vertices)
        //std::cout << i << ' ';


    //TRIANGLES
    int k1, k2;
    for (int i = 0; i < stacks; ++i) {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            // Cree un carré
            // T1
            if (i != 0) { 
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // T2
            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
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

Sphere::~Sphere() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Sphere::draw() {

    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);

    glm::vec3 const& Translate = {4.0f,0.0f,-10.0f};
    glm::vec3 const& Rotate = { 2 * glfwGetTime(),0,0 };

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), Translate);
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
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

void Sphere::key_handler(int key) {
    return;
}

