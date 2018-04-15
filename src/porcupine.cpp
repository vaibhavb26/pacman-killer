#include "porcupine.h"
#include "main.h"
#define PI  3.14159265358979323846
#include <bits/stdc++.h>
using namespace std;

Porcupine::Porcupine(float x, float y, float enemy_speed) {
    this->position = glm::vec3(x, y, 0);
    // this->rotation = 0;
    // this->flag = 0;
    // this->radius = radius;
    this->enemy_speed = enemy_speed;
    // cout<<"hahaha "<<enemy_speed<<" "<<this->enemy_speed<<endl;
    // const int n=10000;
    // float  v1,v2,dif;
    // dif = 360.0/n;
    // v1 = 180.0/n;
    // v2 = -180.0/n;
    GLfloat vertex_buffer_data[] = {
        0, 0, 0,
        0.20f, 0, 0,
        0.10f, 0.50f, 0,
        
        0.20f, 0, 0,
        0.40f, 0, 0,
        0.30f, 0.50f, 0
    };
    // int col = rand() % 5;
    // this->col = col;
    // color_t temp;
    // if(col == 0)
    //     temp = COLOR_YELLOW;
    // else if(col == 1)
    //     temp = COLOR_GREEN;    
	// else if(col == 2)
    //     temp = COLOR_PURPLE;    
	// else if(col == 3)
    //     temp = COLOR_BLUE;    
	// else if(col == 4)
    //     temp = COLOR_BROWN;  
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<3;j++){
    //        vertex_buffer_data[(i*9)+j] = 0.0f;
    //     }   
    //     vertex_buffer_data[(i*9)+3] = (radius)*cos((v2*PI)/180);
    //     vertex_buffer_data[(i*9)+4] = (radius)*sin((v2*PI)/180);
    //     vertex_buffer_data[(i*9)+5] = 0.0f;
    //     vertex_buffer_data[(i*9)+6] = (radius)*cos((v1*PI)/180);
    //     vertex_buffer_data[(i*9)+7] = (radius)*sin((v1*PI)/180);
    //     vertex_buffer_data[(i*9)+8] = 0.0f;
    //     v1 += dif;
    //     v2 += dif;
    // }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_WHITE, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tick() {
    // cout<<this->position.x<<this->position.y<<endl;
    if(this->position.x + 0.4 < 2.0 && this->position.x >= 0) {
        // cout<<"yo "<<this->position.x<<endl;
        this->position.x += this->enemy_speed;
    }
    else if(this->position.x + 0.4 >= 2.0 || this->position.x <= 0){
        this->enemy_speed = -this->enemy_speed;
        this->position.x += this->enemy_speed;
    }
    // else {
    //     ;
    // }
    // if(this->position.x >= 4+this->radius)
    // {
    //     //destroy
    //     this->flag = 1;
    // }
    // else
    // {
    //     this->position.x += this->enemy_speed;
    // }
//  printf("%lf %lf\n",speed_y,this->position.y);
}

// bounding_box_t Ball::bounding_box() {
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { x, y, 0.4, 0.4 };
//     return bbox;
//}
