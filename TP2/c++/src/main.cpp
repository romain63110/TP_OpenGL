#include "viewer.h"
#include "pyramid.h"
#include "shader.h"
#include "sphere.h"
#include "cylinder.h"
#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *color_shader = new Shader(shader_dir + "color.vert", shader_dir + "color.frag");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    viewer.add(new Pyramid(color_shader));
    viewer.add(new Sphere(1.0f, 10, 10, color_shader));
    viewer.add(new Cylinder(1.0f, 0.5f, 16, color_shader));

    viewer.run();
}
