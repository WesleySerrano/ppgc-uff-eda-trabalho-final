#include "VoronoiDiagram.hpp"

void VoronoiDiagram::printEndpoint(Halfedge_handle halfEdge, bool isSourceVertex)
{
  std::cout << "\t";
  if ( isSourceVertex ) 
  {
    if ( halfEdge->has_source() )  std::cout << halfEdge->source()->point() << std::endl;
    else  std::cout << "point at infinity" << std::endl;
  } 
  else 
  {
    if ( halfEdge->has_target() )  std::cout << halfEdge->target()->point() << std::endl;
    else  std::cout << "point at infinity" << std::endl;
  }
}

void VoronoiDiagram::loadPointsFromFile(char* fileName)
{
  std::chrono::time_point<std::chrono::system_clock> timeStamp0, timeStamp1;
  std::ifstream input(fileName);
  assert( input );
  site2D site;

  long pointsCount = 0;
  timeStamp0 = std::chrono::high_resolution_clock::now();
  while ( input >> site )
  {
      this->voronoiDiagram->insert(site);
      pointsCount++;
      if(pointsCount%10000 == 0)
      { 
          std::chrono::duration<double, std::milli> stepDuration = std::chrono::high_resolution_clock::now() - timeStamp0;
          std::cout << pointsCount << " pontos inseridos. Tempo de execução total: " << stepDuration.count() << " milissegundos"<< std::endl;
      }
  }
  timeStamp1 = std::chrono::high_resolution_clock::now();
  input.close();  

  assert( this->voronoiDiagram->is_valid() );

  std::chrono::duration<double, std::milli> duration = timeStamp1 - timeStamp0;

  std::cout << pointsCount << " pontos inseridos no diagrama em " << duration.count() << " milissegundos\n";
}

void VoronoiDiagram::queryPoint(point2D point)
{
    std::cout << "Query point (" << point.x() << "," << point.y()
              << ") lies on a Voronoi " << std::flush;
    Locate_result pointLocation = this->voronoiDiagram->locate(point);

    if ( Vertex_handle* vertex = boost::get<Vertex_handle>(&pointLocation) ) 
    {
      std::cout << "vertex." << std::endl;
      std::cout << "The Voronoi vertex is:" << std::endl;
      std::cout << "\t" << (*vertex)->point() << std::endl;
    } 
    else if ( Halfedge_handle* edge = boost::get<Halfedge_handle>(&pointLocation) ) 
    {
      std::cout << "edge." << std::endl;
      std::cout << "The source and target vertices "
                << "of the Voronoi edge are:" << std::endl;
      this->printEndpoint(*edge, true);
      this->printEndpoint(*edge, false);
    } 
    else if ( Face_handle* face = boost::get<Face_handle>(&pointLocation) ) 
    {
      std::cout << "face." << std::endl;
      std::cout << "The vertices of the Voronoi face are"
                << " (in counterclockwise order):" << std::endl;
      Ccb_halfedge_circulator edgeCirculatorStart = (*face)->ccb();
      Ccb_halfedge_circulator edgeCirculator = edgeCirculatorStart;
      do 
      {
        this->printEndpoint(edgeCirculator, false);
      } 
      while ( ++edgeCirculator != edgeCirculatorStart );
    }
    std::cout << std::endl;
}

void VoronoiDiagram::queryPointsFromFile(char* fileName)
{
  std::chrono::time_point<std::chrono::system_clock> timeStamp0, timeStamp1;
  std::vector<point2D> queryPoints;
  std::ifstream input("data/queries1.dt.cin");
  assert( input );
  point2D p;
  while ( input >> p ) queryPoints.emplace_back(p);
  input.close();

  long pointsCount = 0;
  timeStamp0 = std::chrono::high_resolution_clock::now();
  for(point2D point : queryPoints) 
  {
      this->queryPoint(point);
      pointsCount++;
      if(pointsCount%10000 == 0) std::cout << pointsCount << " pontos buscados" << std::endl;
  }

  timeStamp1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = timeStamp1 - timeStamp0;

  std::cout << pointsCount << " pontos buscados no diagrama em " << duration.count() << " milissegundos\n";
}