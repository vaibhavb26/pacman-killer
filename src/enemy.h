#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float radius,float enemy_speed);
    glm::vec3 position;
    float rotation;
    float radius;
    int flag;
    int col;
    float enemy_speed;
    void draw(glm::mat4 VP);
//    bool flag = false;
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H