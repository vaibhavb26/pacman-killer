#include "main.h"

#ifndef POND_H
#define POND_H


class Pond {
public:
    Pond() {}
    Pond(color_t color);
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
};

#endif 
