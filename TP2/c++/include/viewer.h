#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "drawable.h"

class Viewer {
public:
    Viewer(int width=640, int height=480);

    void run();
    void add(Drawable* drawable);
    void on_key(int key);

private:
    GLFWwindow* win;
    std::vector<Drawable*> drawables;
    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // VIEWER_H
