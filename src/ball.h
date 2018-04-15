#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double accln;
    void draw(glm::mat4 VP);
    bool flag = false;
    void set_position(float x, float y);
    void tick();
    double speed;
    double speed_y;
//    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
