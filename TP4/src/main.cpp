#include "viewer.h"
#include "textured_sphere.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "skybox.h"
#include "node.h"
#include "shader.h"
#include <string>
#include <vector>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *texture_shader = new Shader(shader_dir + "texture.vert", shader_dir + "texture.frag");

    Texture *texture = new Texture("../../../textures/texture1.png");
    Shape* sphere1 = new TexturedSphere(texture_shader, texture);
    glm::mat4 sphere1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* sphere1_node = new Node(sphere1_mat);

    sphere1_node->add(sphere1);

    viewer.scene_root->add(sphere1_node);
    
    Shader *phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");

    Shape* sphere2 = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 sphere2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    Node* sphere2_node = new Node(sphere2_mat);

    sphere2_node->add(sphere2);

    viewer.scene_root->add(sphere2_node);

    std::string texture_dir = "../../../textures/";
    std::vector<std::string> faces =
    {
        texture_dir + "right.jpg",
        texture_dir + "left.jpg",
        texture_dir + "top.jpg",
        texture_dir + "bottom.jpg",
        texture_dir + "front.jpg",
        texture_dir + "back.jpg"
    };

    Texture* skyTexture = new Texture(faces);
    Shader* skyShader = new Shader(shader_dir + "skybox.vert", shader_dir + "skybox.frag");
    Shape* mySkybox = new Skybox(skyShader, skyTexture);

    Node* sky_node = new Node();
    sky_node->add(mySkybox);
    viewer.scene_root->add(sky_node);

    viewer.run();
}