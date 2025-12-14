#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "drawable.h"
#include "shader.h"
#include <GL/glew.h>

class Triangle : public Drawable {
public:
    Triangle(Shader *shader_program);
    void draw();
    void key_handler(int key);
    virtual ~Triangle();

private:
    GLuint shader_program_;
    GLuint VAO;
    GLuint VBO;
};

#endif
