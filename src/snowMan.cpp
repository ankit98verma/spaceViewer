#include "snowMan.h"
#include <GL/glut.h>

snowMan::snowMan()
{
    //ctor
}

void snowMan::draw() {
	glutSolidSphere(0.5f,20,20);
}

snowMan::~snowMan()
{
    //dtor
}
