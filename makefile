INCLUDE = -I /usr/local/include
LINK = -lgmp -lmpfr
COMPILER = g++ --std=c++17
MODULES = VoronoiDiagram.o

main: VoronoiDiagram
	$(COMPILER) main.cpp -o main $(MODULES) $(LINK) $(INCLUDE)

VoronoiDiagram: 
	$(COMPILER) -c VoronoiDiagram.cpp