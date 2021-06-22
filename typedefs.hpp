class Arc;
class Event;
class Segment;

#include "imports.hpp"

typedef std::pair<double, double> point;
#define x first
#define y second

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


#ifndef ARC_H
#define ARC_H
class Arc 
{
    public:
        Arc(point _p, Arc *a=0, Arc *b=0)
        : p(_p), prev(a), next(b), e(0), s0(0), s1(0) {}

        point getPoint(){return this->p;}
        Arc* getPrev(){return this->prev;}
        Arc* getNext(){return this->next;}
        
        Event* getEvent(){return this->e;}

        Segment* getSegment0(){return this->s0;}
        Segment* getSegment1(){return this->s1;}

        void setNext(Arc* _a){this->next = _a;}
        void setPrev(Arc* _a){this->prev = _a;}

        void setEvent(Event* _e){this->e = _e;}

        void setSegment0(Segment* _s){this->s0 = _s;}
        void setSegment1(Segment* _s){this->s1 = _s;}
    private:

        point p;
        Arc *prev, *next;
        Event *e;

        Segment *s0, *s1;
};
#endif

#ifndef SEGMENT_H
#define SEGMENT_H

class Segment{
    public:
        Segment(point p)
            : start(p), end(0,0), done(false)
        { }
        
        void finish(point p) { if (done) return; end = p; done = true; }

        point getStart(){return this->start;}
        point getEnd(){return this->end;}

   private:

    point start, end;
    bool done;
};
#endif