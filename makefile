#INCLUDE = -I /usr/local/include
LINK = -lm
COMPILER = g++ --std=c++17
MODULES = Voronoi.o

main: Voronoi
	$(COMPILER) main.cpp -O3 -o main $(MODULES) $(LINK) 

Voronoi: 
	$(COMPILER) -O3 -c Voronoi.cpp