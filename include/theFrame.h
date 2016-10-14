#ifndef THEFRAME_H
#define THEFRAME_H
#include "snowMan.h"
#include "camera.h"

class theFrame
{
public:
    theFrame(int* argc, char* argv[], char* title);
    virtual ~theFrame();

protected:

private:
    static void render(void);
    static void changeSize(int w, int h);
    static void keyboardFunc(unsigned char c,int i, int j);
    static void mouseClickFunc(int button, int state, int x, int y);
    static void mouseMotionFunc(int x, int y);
    static void idleFunc();
    static void update();
    static snowMan s;
    static camera cam;
};

#endif // THEFRAME_H
