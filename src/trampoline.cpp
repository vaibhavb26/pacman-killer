#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(color_t color)
{
//    this->position = glm::vec3(-1,-1,0);
//    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        2.0, -2, 0,
        2.1, -2, 0,
        2.0, -1, 0,

        2.0, -1, 0,
        2.1, -1, 0,
        2.1, -2, 0
    };
    
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_RED , GL_FILL);        

    static const GLfloat vertex_buffer_data1[] = {
        3.5, -2, 0,
        3.6, -2, 0,
        3.5, -1, 0,

        3.5, -1, 0,
        3.6, -1, 0,
        3.6, -2, 0
    };
    
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_RED , GL_FILL);        

    static const GLfloat vertex_buffer_data2[] = {
        2.1, -1, 0,
        3.5, -1, 0,
        2.8, -1.5, 0
    };
    
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_RED , GL_FILL);        

}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}
