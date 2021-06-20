#include "VoronoiDiagram.hpp"

int main(int argc, char* argv[])
{
  VoronoiDiagram *voronoiDiagram = new VoronoiDiagram();
  voronoiDiagram->loadPointsFromFile((char*)"data/data1.dt.cin");
  voronoiDiagram->queryPointsFromFile((char*)"data/queries1.dt.cin");

  return 0;
}