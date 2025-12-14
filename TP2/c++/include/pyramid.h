#ifndef PYRAMID_H
#define PYRAMID_H

#include "drawable.h"
#include "shader.h"
#include <GL/glew.h>

class Pyramid : public Drawable {
public:
    Pyramid(Shader* shader_program);
    void draw();
    void key_handler(int key);
    virtual ~Pyramid();

private:
    GLuint shader_program_;
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
};

#endif

