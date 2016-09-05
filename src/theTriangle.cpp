#include "theTriangle.h"


theTriangle::theTriangle(float xx, float yy, float a){
    x = xx;
    y=yy;
    angle=a;
}

void theTriangle::draw(){
    glTranslatef(x, y, 0);
    glRotatef(angle, 0 , 0 ,1);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, 0, 0);
        glVertex3f(0.5, 0, 0);
        glVertex3f(0, 0.5, 0);
    glEnd();
}

void theTriangle::setX(float xx){
    x=xx;
}
void theTriangle::setY(float yy){
    y=yy;
}
void theTriangle::setAng(float ang){
    angle=ang;
}
float theTriangle::getX(){
    return x;
}
float theTriangle::getY(){
    return y;
}
float theTriangle::getAng(){
    return angle;
}

theTriangle::~theTriangle(){
    //dtor
}
