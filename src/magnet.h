#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
//    bool flag = false;
//    void set_position(float x, float y);
//    void tick();
//    double speed;
//    double speed_y;
//    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    // VAO *object2;
};

#endif 
