#include "main.h"

#ifndef PLANK_H
#define PLANK_H


class Plank {
public:
    Plank() {}
    Plank(float x, float y, float radius,float enemy_speed);
    glm::vec3 position;
    float rotation;
    float radius;
    int flag;
    float angle;
    int col;
    float enemy_speed;
    void draw(glm::mat4 VP);
//    bool flag = false;
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif // BALL_H