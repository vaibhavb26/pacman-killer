#include "plank.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;
#define PI  3.14159265358979323846

Plank::Plank(float x, float y, float radius,float enemy_speed) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 0;
    this->radius = radius;
    this->enemy_speed = enemy_speed;
    const int n = 1000;
    float  v1,v2,dif;
    float angle = rand()%151 -75;
    this->angle = angle;
    int col = rand() % 5;
    this->col = col;
    color_t temp;
    if(col == 0)
        temp = COLOR_YELLOW;
    else if(col == 1)
        temp = COLOR_GREEN;    
	else if(col == 2)
        temp = COLOR_PURPLE;    
	else if(col == 3)
        temp = COLOR_BLUE;    
	else if(col == 4)
        temp = COLOR_BROWN;    
    // float first_angle_x = angle - 45;
    // float first_angle_y = angle + 45;
    // float first_x = x + (radius)*(1.414235)*cos((first_angle_x*PI)/180);
    // float first_y = y + (radius)*(1.414235)*sin((first_angle_x*PI)/180);
    // float second_x = x + (radius)*(1.414235)*cos((first_angle_y*PI)/180);
    // float second_y = y + (radius)*(1.414235)*sin((first_angle_y*PI)/180);
    // float second_angle_x = angle - 45;
    // float second_angle_y = angle + 45;
    // float third_x = x + (radius)*(1.414235)*cos((second_angle_x*PI)/180);
    // float third_y = y + (radius)*(1.414235)*sin((second_angle_x*PI)/180);
    // float fourth_x = x + (radius)*(1.414235)*cos((second_angle_y*PI)/180);
    // float fourth_y = y + (radius)*(1.414235)*sin((second_angle_y*PI)/180);
    
    dif = 360.0/n;
    v1 = 180.0/n;
    v2 = -180.0/n;
    static GLfloat vertex_buffer_data[9*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
           vertex_buffer_data[(i*9)+j] = 0.0f;
        }   
        vertex_buffer_data[(i*9)+3] = (radius)*cos((v2*PI)/180);
        vertex_buffer_data[(i*9)+4] = (radius)*sin((v2*PI)/180);
        vertex_buffer_data[(i*9)+5] = 0.0f;
        vertex_buffer_data[(i*9)+6] = (radius)*cos((v1*PI)/180);
        vertex_buffer_data[(i*9)+7] = (radius)*sin((v1*PI)/180);
        vertex_buffer_data[(i*9)+8] = 0.0f;
        v1 += dif;
        v2 += dif;
    }
    static GLfloat buffer_data[18];
    
    buffer_data[0] = 1.5*radius;
    buffer_data[1] = radius;
    buffer_data[2] = 0.0f;
    buffer_data[3] = -1.5*radius;
    buffer_data[4] = radius;
    buffer_data[5] = 0.0f;
    buffer_data[6] = 1.5*radius;
    buffer_data[7] = radius + radius/1.5f;
    buffer_data[8] = 0.0f;
    buffer_data[9] = 1.5*radius;
    buffer_data[10] = radius + radius/1.5f;
    buffer_data[11] = 0.0f;
    buffer_data[12] = -1.5*radius;
    buffer_data[13] = radius + radius/1.5f;
    buffer_data[14] = 0.0f;
    buffer_data[15] = -1.5*radius;
    buffer_data[16] = radius;
    buffer_data[17] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, temp, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, buffer_data, COLOR_WHITE, GL_FILL);
}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->angle * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Plank::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plank::tick() {
    if(this->position.x >= 4+this->radius)
        this->flag = 1;
    else
        this->position.x += this->enemy_speed;
}