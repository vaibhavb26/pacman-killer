#include "magnet.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;
#define PI  3.14159265358979323846

Magnet::Magnet(float y, color_t color)
{
	// this->type = rand()%2;
	// if(this->type == 1)
	this->position = glm::vec3(-2.8, y, 0);
	// else
		// this->position = glm::vec3(2.8, y, 0);
	const int n = 1000;
	float  v1,v2,dif;
	float radius = 1;
	dif = 360.0/n;
	v1 = 180.0/n;
	v1 += n / 2 * dif + dif;
	v2 = -180.0 / n;
	v2 += n / 2 * dif + dif;
	
	GLfloat vertex_buffer_data[9*n/2];
	GLfloat vertex_buffer_data1[9*n/2];
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
	v1 = 180.0/n;
	v1 += n/2*dif+dif;
	v2 = -180.0/n;
	v2 += n/2*dif+dif;
	
	for(int i=0;i<n/2-1;i++){
		for(int j=0;j<3;j++){
		vertex_buffer_data1[(i*9)+j] = 0.0f;
		}   
		vertex_buffer_data1[(i*9)+3] = (radius/2.0f)*cos((v2*PI)/180);
		vertex_buffer_data1[(i*9)+4] = (radius/2.0f)*sin((v2*PI)/180);
		vertex_buffer_data1[(i*9)+5] = 0.0f;
		vertex_buffer_data1[(i*9)+6] = (radius/2.0f)*cos((v1*PI)/180);
		vertex_buffer_data1[(i*9)+7] = (radius/2.0f)*sin((v1*PI)/180);
		vertex_buffer_data1[(i*9)+8] = 0.0f;
		v1 += dif;
		v2 += dif;
	}
	this->object = create3DObject(GL_TRIANGLES, 1500-3, vertex_buffer_data, color, GL_FILL);
	this->object1 = create3DObject(GL_TRIANGLES, 1500-3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	// if(this->type == 1) {
		glm::mat4 translate = glm::translate (this->position);    // glTranslatef
		glm::mat4 rotate    = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
	
		rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
		Matrices.model *= (translate * rotate);
		glm::mat4 MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->object);
		// draw3DObject(this->object1);
	// }
	// else {
	// 	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	// 	glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
	
	// 	rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
	// 	Matrices.model *= (translate * rotate);
	// 	glm::mat4 MVP = VP * Matrices.model;
	// 	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	// 	draw3DObject(this->object);
	 	draw3DObject(this->object1);
			
	// }
	// draw3DObject(this->object2);
}
