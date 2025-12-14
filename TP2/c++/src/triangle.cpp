#include "triangle.h"

#include <iostream>

Triangle::Triangle(Shader *shader_program) : shader_program_(shader_program->get_id()) {

    GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3 
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);    

    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::draw() {

    glUseProgram( this->shader_program_ );
    glBindVertexArray( VAO );
    /* draw points 0-3 from the currently bound VAO with current in-use shader */
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}

void Triangle::key_handler(int key) {
    return;
}

