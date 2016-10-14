#include "theFrame.h"
#include <GL/glut.h>
#include <iostream>
#include "theTriangle.h"
#include <math.h>
#include <electricField.h>
#include "string"

using namespace std;

snowMan theFrame:: s;

camera theFrame:: cam(0,0,0,5.5,-124.9,70.6);

float xB=0.1,yB=0.1;

bool paused = false;

int mouseX, mouseY, ctrKey;
float incT = 0.016, totT =0.0;

electricField Ez(2, M_PI/2, 1, M_PI*0/180);
electricField Ex(2, M_PI/2, 1, M_PI*90/180);

theFrame::theFrame(int* argc, char* argv[], char* title){

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(1000, 700);
    glutCreateWindow(title);

    glutDisplayFunc(theFrame::render);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseClickFunc);
    glutMotionFunc(mouseMotionFunc);
    glutIdleFunc(idleFunc);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}

void theFrame::render(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    gluLookAt(cam.getCamX(), cam.getCamY(),cam.getCamZ(),
            cam.getObjX(), cam.getObjY(),  cam.getObjZ(),
			0.0f, 0.0f,  1.0f);


	glBegin(GL_LINES);
        glColor3f(1.0f, 0 ,0 ); //x axis

        glVertex3f(2.1f, 0, 0);
        glVertex3f(10.0, 0.0,0);


        glColor3f(0.0f, 1.0f ,0 );  // y axis

        glVertex3f(0.0, 0.0,0);
        glVertex3f(0.0, 10.0,0);

        glColor3f(0.0f, 0 ,1.0f );  // z axis

        glVertex3f(0.0, 0.0,2.1f);
        glVertex3f(0.0, 0.0,10.0f);

	glEnd();

	/*for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glColor3f(0.01*i, 0.2*i, 0.2);
			glTranslatef(i*5.0+xB,yB+j * 5.0,0);
			s.draw();
			glPopMatrix();
		}*/
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
        for(float y = 0; y<50; y+=.01){
            float z =(float)Ez.getValueAt(totT, y);
            float x = (float)Ex.getValueAt(totT, y);
            glVertex3f(x, y, z);
        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f ,0 );
        glVertex3f(0,0,0);
        glVertex3f(0,0,Ez.getValueAt(totT, 0));
        glColor3f(0.0f, 1.0f ,1.0f );
        glVertex3f(0,0,0);
        glVertex3f(Ex.getValueAt(totT, 0),0,0);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(1,0, 0);
    for (char* txt="Ex = 2cos(pi*t/2 - 1*y + pi/2)"; *txt != '\0'; txt++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *txt);
    }

    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos3f(0,0, 1);
    for (char* txt="Ez = 2cos(pi*t/2 - 1*y )"; *txt != '\0'; txt++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *txt);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(1,1, 1);
    for (char* txt="Axis: x->Red; y->Green; z->Blue"; *txt != '\0'; txt++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *txt);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(1,1, 0.001f);
    for (char* txt="LHCP wave with Ex leading by pi/2"; *txt != '\0'; txt++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *txt);
    }
	glutSwapBuffers();
}

void theFrame::keyboardFunc(unsigned char c, int i, int j){
    //cout << i<<"\n" <<j <<endl;
    if( c == 27)
        exit(0);
    if( c == 'w' || c == 'W'){
        cam.moveCamR(cam.getR()-.5);
    }
    if( c == 's' || c == 'S'){
        cam.moveCamR(cam.getR()+.5);
    }
    if( c == ' '){
        paused  = !paused;
    }
}
void theFrame::mouseClickFunc(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        mouseX =x;mouseY = y;
        //cout <<"CLICK Mx: "<<mouseX<<" My:"<<mouseY<<endl;
    }
}
void theFrame::mouseMotionFunc(int x, int y){
    float factor = 0.1;
    int delX = x - mouseX, delY = y - mouseY;   //delY changes theta and delX changes phi
    mouseX = x;mouseY = y;
    //cout <<"DRAGED Mx: "<<mouseX<<" My:"<<mouseY<<endl;
    int mod = glutGetModifiers();
    if(mod== GLUT_ACTIVE_CTRL){
        cam.moveObjPhi(cam.getPhi()-(float)factor*delX);
        cam.moveObjTheta(cam.getTheta()-(float)factor*delY);
    }else{
        cam.moveCamPhi(cam.getPhi()-(float)factor*delX);
        cam.moveCamTheta(cam.getTheta()-(float)factor*delY);
    }

}


void theFrame::changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void theFrame::idleFunc(){
    update();
    glutPostRedisplay();
}
void theFrame::update(){        //update everything for animation
    //xB+=0.001;yB+=0.0001;
    if(!paused){
        Sleep(incT*1000);
        totT += incT;
    }
}

theFrame::~theFrame(){
    //dtor
}
