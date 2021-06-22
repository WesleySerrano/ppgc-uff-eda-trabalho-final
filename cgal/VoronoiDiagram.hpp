#include "includes.hpp"
#include "typedefs.hpp"

#ifndef VORONOI_H
#define VORONOI_H
class VoronoiDiagram
{
    public:
        VoronoiDiagram()
        {
            this->voronoiDiagram = new CGAL_VoronoiDiagram();
        }

        void loadPointsFromFile(char*);
        void queryPoint(point2D);
        void queryPointsFromFile(char*);
        void printEndpoint(Halfedge_handle, bool);
    private:
        CGAL_VoronoiDiagram* voronoiDiagram;        
};
#endif