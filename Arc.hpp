#include "typedefs.hpp"
#include "Segment.hpp"

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