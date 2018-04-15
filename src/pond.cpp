#include "pond.h"
#include "main.h"
#define PI  3.14159265358979323846

Pond::Pond(color_t color)
{
    this->position = glm::vec3(-1, -2, 0);
    // this->rotation = 0;
    // this-> flag = 0;
    // this->radius = radius;
    // this->enemy_speed = enemy_speed;
    const int n=1000;
    float  v1,v2,dif;
    float radius = 1;
    dif = 360.0/n;
    v1 = 180.0/n;
    v1 += n/2*dif+dif;
    v2 = -180.0/n;
    v2 += n/2*dif+dif;
    
    static GLfloat vertex_buffer_data[9*n/2];
    for(int i=0;i<n/2-1;i++){
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
    this->object = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
