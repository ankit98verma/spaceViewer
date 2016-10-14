using  namespace std;
#include "camera.h"
#include <iostream>
#include <math.h>
#define PI 3.142


camera::camera(float rr, float p, float t){
    r=rr;ox=0;
    phi=p;oy=0;
    theta=t;oz=0;
    calcComponents();calcCameraPos();
}
camera::camera(float oxx,float oyy,float ozz, float rr, float p, float t){
    r=rr;ox=oxx;
    phi=p;oy=oyy;
    theta=t;oz=ozz;
    calcComponents();calcCameraPos();
}

void camera::moveCamR(float rr){
    moveCamForward(rr-r);//display();
}
void camera::moveCamPhi(float p){
    phi=p;calcCameraPos();
}
void camera::moveCamTheta(float t){
    theta=t;calcCameraPos();
}
void camera::moveObjR(float rr){
    r=rr;calcObjectPos();
}
void camera::moveObjPhi(float p){
    phi=p;calcObjectPos();
}
void camera::moveObjTheta(float t){
    theta=t;calcObjectPos();
}

void camera::moveCamForward(float delta){
    ox += delta*cos(phi*0.0174532925f)*sin(theta*0.0174532925f);
    oy += delta*sin(phi*0.0174532925f)*sin(theta*0.0174532925f);
    oz += delta*cos(theta*0.0174532925f);

    cx += delta*cos(phi*0.0174532925f)*sin(theta*0.0174532925f);
    cy += delta*sin(phi*0.0174532925f)*sin(theta*0.0174532925f);;
    cz += delta*cos(theta*0.0174532925f);
}

void  camera::calcComponents(){
    x = r*cos(phi*0.0174532925f)*sin(theta*0.0174532925f);
    y = r*sin(phi*0.0174532925f)*sin(theta*0.0174532925f);
    z = r*cos(theta*0.0174532925f);
    //display();
}
void camera::calcCameraPos(){
    calcComponents();
    cx = ox+x;
    cy = oy+y;
    cz = oz+z;
}
void camera::calcObjectPos(){
    calcComponents();
    ox = cx-x;
    oy = cy-y;
    oz = cz-z;
}

float camera::getCamX(){
    return cx;
}
float camera::getCamY(){
    return cy;
}
float camera::getCamZ(){
    return cz;
}
float camera::getObjX(){
    return ox;
}
float camera::getObjY(){
    return oy;
}
float camera::getObjZ(){
    return oz;
}

float camera::getR(){
    return r;
}
float camera::getPhi(){
    return phi;
}
float camera::getTheta(){
    return theta;
}

void camera::display(){
    cout << "Cx: " << cx <<"\tCy: "<< cy <<"\tCz:" << cz<<"\n";
    cout << "Ox: " << ox <<"\tOy: "<< oy <<"\tOz:" << oz<<"\n";
    cout << "R: " << r <<"\tPhi: "<< phi <<"\tTheta:" << theta<<"\n";
}

camera::~camera(){

}
