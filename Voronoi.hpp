#include "operators.hpp"

#ifndef VORONOI_H
#define VORONOI_H

class Voronoi
{
    public:
        Voronoi()
        {
            this->root = 0;
            X0 = 0;
            X1 = 0;
            Y0 = 0;
            Y1 = 0;
        }

        void processPoint();
        void processEvent();
        void frontInsert(point);

        bool circle(point, point, point, double*, point*);
        void checkCircleEvent(Arc*, double);

        bool intersect(point, Arc*, point* result = 0);
        point intersection(point, point, double);

        void finishEdges();
        void printOutput();

        void fortune(char*);

    private:
        std::priority_queue<point,  std::vector<point>,  gt> points;
        std::priority_queue<Event*, std::vector<Event*>, gt> events;

        std::vector<Segment*> output;
        Arc* root;
        double X0, X1, Y0, Y1;
};

#endif
