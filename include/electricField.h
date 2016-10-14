#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H


class electricField
{
    public:
        electricField(float eo, float o, float b, float phase);
        double getValueAt(float t, float x);
        virtual ~electricField();
        electricField(const electricField& other);

    protected:

    private:
        float Eo,omega, beta, phase;
};

#endif // ELECTRICFIELD_H
