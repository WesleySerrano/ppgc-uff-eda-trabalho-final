#include "typedefs.hpp"
#include "Arc.hpp"
#ifndef EVENT_H
#define EVENT_H

class Event {
    public:
        Event(double _x, point _p, Arc *_a)
            : x(_x), p(_p), a(_a), valid(true) {}

    double getX(){return this->x;}
    point getPoint(){return this->p;}
    bool isValid(){return this->valid;}
    void setValid(bool _v){this->valid = _v;}
    Arc* getArc(){return this->a;}

    private:
        double x;
        point p;
        Arc *a;
        bool valid;
};

#endif