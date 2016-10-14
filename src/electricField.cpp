#include "electricField.h"
#include <math.h>
#include <iostream>

using namespace std;
electricField::electricField(float Eo, float omega, float beta,float phase){
    this->Eo = Eo;
    this->omega = omega;
    this->beta = beta;
    this->phase=phase;
    //ctor
}

double electricField::getValueAt(float t, float x){
    return Eo * cos(omega*t - beta*x + phase);
}

electricField::~electricField()
{
    //dtor
}

electricField::electricField(const electricField& other)
{
    //copy ctor
}
