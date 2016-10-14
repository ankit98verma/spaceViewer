#include "theFrame.h"
#include <GL/glut.h>
#include <iostream>
#include "theTriangle.h"
#include <math.h>
#include <electricField.h>

using namespace std;

snowMan theFrame:: s;

camera theFrame:: cam(0,0,0,5,45,90);

float xB=0.1,yB=0.1;

int mouseX, mouseY, ctrKey;

electricField Ex(100, M_PI, 0.01, M_PI*60/180);

theFrame::theFrame(int* argc, char* argv[], char* title){

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 50);
    glutInitWindowSize(700, 600);
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
        glColor3f(1.0f, 0 ,0 );

        glVertex3f(0.0, 0,0);
        glVertex3f(10.0, 0.0,0);

        glColor3f(0.0f, 1.0f ,0 );

        glVertex3f(0.0, 0.0,0);
        glVertex3f(0.0, 10.0,0);

        glColor3f(0.0f, 0 ,1.0f );

        glVertex3f(0.0, 0.0,0.0f);
        glVertex3f(0.0, 0.0,10.0f);
	glEnd();

	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glColor3f(0.01*i, 0.2*i, 0.2);
			glTranslatef(i*5.0+xB,yB+j * 5.0,0);
			s.draw();
			glPopMatrix();
		}

	glutSwapBuffers();
}

void theFrame::keyboardFunc(unsigned char c, int i, int j){
    cout << i<<"\n" <<j <<endl;
    if( c == 27)
        exit(0);
    if( c == 'w'){
        cam.moveCamR(cam.getR()-.1);
    }
    if( c == 's'){
        cam.moveCamR(cam.getR()+.1);
    }
}
void theFrame::mouseClickFunc(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        mouseX =x;mouseY = y;
        cout <<"CLICK Mx: "<<mouseX<<" My:"<<mouseY<<endl;
    }
}
void theFrame::mouseMotionFunc(int x, int y){
    float factor = 0.1;
    int delX = x - mouseX, delY = y - mouseY;   //delY changes theta and delX changes phi
    mouseX = x;mouseY = y;
    cout <<"DRAGED Mx: "<<mouseX<<" My:"<<mouseY<<endl;
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
    xB+=0.001;yB+=0.0001;
}

theFrame::~theFrame(){
    //dtor
}
