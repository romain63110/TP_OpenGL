#ifndef CYLINDER_H
#define CYLINDER_H

#include "drawable.h"
#include "shader.h"
#include <GL/glew.h>

class Cylinder : public Drawable {
public:
    Cylinder(float height, float radius, int slices, Shader *shader_program);
    void draw();
    void key_handler(int key);
    virtual ~Cylinder();

private:
    GLuint shader_program_;
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    int index_count;
};

#endif

