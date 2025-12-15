#include "viewer.h"
#include "triangle.h"
//#include "pyramid.h"
#include "pyramid.h"
#include "cylinder.h"
#include "node.h"
#include "shader.h"
#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    glm::mat4 human_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -8.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
    Node* human = new Node(human_mat);

    // TODO create the human skeleton
    //body
    Shape* body = new Cylinder(color_shader,3,0.5f,16);
    glm::mat4 body_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* body_node = new Node(body_mat);
    body_node->add(body);
    human->add(body_node);

    //head
    Shape* head = new Pyramid(color_shader);
    glm::mat4 head_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* head_node = new Node(head_mat);
    head_node->add(head);
    body_node->add(head_node);

    //left_arm
    Shape* left_arm = new Cylinder(color_shader, 1, 0.5f, 16);
    glm::mat4 left_arm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //* glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* left_arm_node = new Node(left_arm_mat);
    left_arm_node->add(left_arm);
    body_node->add(left_arm_node);

    //left_forearm
    Shape* left_forearm = new Cylinder(color_shader, 1, 0.5f, 16);
    glm::mat4 left_forearm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    Node* left_forearm_node = new Node(left_forearm_mat);
    left_forearm_node->add(left_forearm);
    left_arm_node->add(left_forearm_node);

    //left_thigh
    Shape* left_thigh = new Cylinder(color_shader, 1, 0.5f, 16);
    glm::mat4 left_thigh_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -3.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* left_thigh_node = new Node(left_thigh_mat);
    left_thigh_node->add(left_thigh);
    body_node->add(left_thigh_node);

    //left_leg
    Shape* left_leg = new Cylinder(color_shader, 1, 0.5f, 16);
    glm::mat4 left_leg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* left_leg_node = new Node(left_leg_mat);
    left_leg_node->add(left_leg);
    left_thigh_node->add(left_leg_node);
    

    viewer.scene_root->add(human);

    viewer.run();
}