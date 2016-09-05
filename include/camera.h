#ifndef CAMERA_H
#define CAMERA_H


class camera
{
    public:
        camera(float r, float phi, float theta);
        camera(float oxx,float oyy,float ozz, float r, float phi, float theta);
        void moveCamR(float r);
        void moveCamPhi(float p);
        void moveCamTheta(float t);
        void moveObjR(float r);
        void moveObjPhi(float p);
        void moveObjTheta(float t);
        float getCamX();
        float getCamY();
        float getCamZ();
        float getObjX();
        float getObjY();
        float getObjZ();
        float getR();
        float getPhi();
        float getTheta();

        virtual ~camera();

    protected:

    private:

        float r, phi,theta, x, y , z;
        float cx, cy, cz, ox, oy, oz;
        void moveCamForward(float delta);
        void calcComponents();
        void calcCameraPos();
        void calcObjectPos();
        void display();
};

#endif // CAMERA_H
