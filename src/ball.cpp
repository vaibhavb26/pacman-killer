#include "ball.h"
#include "main.h"
#include <bits/stdc++.h>
#define PI  3.14159265358979323846
using namespace std;
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->accln = 0;
    speed = 0;
    speed_y = 0;
    const int n=10000;
    float  v1,v2,dif;
    dif = 360.0/n;
    v1 = 180.0/n;
    v2 = -180.0/n;
    static GLfloat vertex_buffer_data[9*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
           vertex_buffer_data[(i*9)+j] = 0.0f;
        }   
        vertex_buffer_data[(i*9)+3] = (0.2)*cos((v2*PI)/180);
        vertex_buffer_data[(i*9)+4] = (0.2)*sin((v2*PI)/180);
        vertex_buffer_data[(i*9)+5] = 0.0f;
        vertex_buffer_data[(i*9)+6] = (0.2)*cos((v1*PI)/180);
        vertex_buffer_data[(i*9)+7] = (0.2)*sin((v1*PI)/180);
        vertex_buffer_data[(i*9)+8] = 0.0f;
        v1 += dif;
        v2 += dif;
    }
    // static const GLfloat vertex_buffer_data[] = {
    //     -0.2, -0.2, 0, // vertex 1
    //     0.2,  -0.2, 0, // vertex 2
    //     0.2,  0.2, 0, // vertex 3

    //     0.2,  0.2, 0, // vertex 3
    //     -0.2, 0.2, 0, // vertex 4
    //     -0.2, -0.2, 0 // vertex 1
    // };

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if(this->position.y < -1.98 && !(this->position.x > -1.95 && this->position.x < -0.02)) {
//        printf("haha\n");
        speed_y = 0;
        this->position.y = -1.8;

    }
    else if(this->position.x > -1.98 && this->position.x < -0.02) {
        float min_y = -2 - sqrt(1 - (this->position.x+1)*(this->position.x+1));
        // float min_y = sqrt(0.64 - (-1 - this->position.x)*(-1 - this->position.x));
        if(this->position.y < min_y + 0.2)
        {
            this->position.y = min_y + 0.2;
            speed_y = 0;
        }
        // if(this->position.y < min_y)
        // {
        //     this->position.y = min_y;
        //     speed_y = 0;
        // } 
    }
    if(this->position.x >= 3.8) {
        speed = -0.05;
//        cout<<speed<<endl;
    }
    else if(this->position.x <= -3.8) {
        speed = 0.05;
 //       cout<<speed<<endl;
    }    
    else 
        speed = 0;
    this->position.y += speed_y;
//    printf("%lf %lf\n",speed_y,this->position.y);
}

// bounding_box_t Ball::bounding_box() {
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { x, y, 0.4, 0.4 };
//     return bbox;
// }
