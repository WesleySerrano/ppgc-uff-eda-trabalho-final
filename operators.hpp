#include "typedefs.hpp"

struct gt {
   bool operator()(point a, point b) {return a.x==b.x ? a.y>b.y : a.x>b.x;}
   bool operator()(Event *a, Event *b) {return a->getX()>b->getX();}
};