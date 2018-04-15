#include "platform.h"
#include "main.h"

Platform::Platform(color_t color)
{
//    this->position = glm::vec3(-1,-1,0);
//    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        -4, -4, 0,
        4, -4, 0,
        -4, -3, 0,

        -4, -3, 0,
        4, -3, 0,
        4, -4, 0
    };
    
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BROWN , GL_FILL);        
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
