#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float y, float enemy_speed);
    glm::vec3 position;
    // float rotation;
    // float radius;
    // int flag;
    // int col;
    void draw(glm::mat4 VP);
//    bool flag = false;
    float enemy_speed;
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H