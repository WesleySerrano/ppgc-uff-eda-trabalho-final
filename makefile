INCLUDE = -I /usr/local/include
LINK = -lgmp -lmpfr
COMPILER = g++ --std=c++17
MODULES = VoronoiDiagram.o

main: VoronoiDiagram
	$(COMPILER) main.cpp -O3 -o main $(MODULES) $(LINK) $(INCLUDE)

VoronoiDiagram: 
	$(COMPILER) -O3 -c VoronoiDiagram.cpp