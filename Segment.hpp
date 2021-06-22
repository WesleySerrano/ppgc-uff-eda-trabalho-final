#include "typedefs.hpp"

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