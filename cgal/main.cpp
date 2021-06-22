#include "VoronoiDiagram.hpp"

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    std::cout << "Por favor informe os caminhos para os arquivos de entrada e de buscas\n";
    std::cout << "Tenha um bom dia\n";
    std::cout << "Não esqueça de beber água\n";
    std::cout << "Leia um bom livro\n";
    exit(0);
  }

  VoronoiDiagram *voronoiDiagram = new VoronoiDiagram();
  voronoiDiagram->loadPointsFromFile(argv[1]);
  voronoiDiagram->queryPointsFromFile(argv[2]);

  return 0;
}