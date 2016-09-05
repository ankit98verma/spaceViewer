#ifndef THETRIANGLE_H
#define THETRIANGLE_H
#include <GL/glut.h>

class theTriangle
{
public:
    theTriangle(float xx, float yy, float a);
    virtual ~theTriangle();
    void draw();
    void setX(float x);
    void setY(float y);
    void setAng(float ang);
    float getX();
    float getY();
    float getAng();

protected:

private:
    float x, y, angle;

};

#endif // THETRIANGLE_H
