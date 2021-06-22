#include "Voronoi.hpp"
void Voronoi::processPoint()
{   
   point p = points.top();
   points.pop();
   
   frontInsert(p);
}

void Voronoi::processEvent()
{   
   Event *event = events.top();
   events.pop();
   if (event->isValid()) {
      
      Segment *segment = new Segment(event->getPoint());
      this->output.emplace_back(segment);
      
      Arc *arc = event->getArc();
      if (arc->getPrev()) {
         arc->getPrev()->setNext(arc->getNext());
         arc->getPrev()->setSegment1(segment);
      }
      if (arc->getNext()) {
         arc->getNext()->setPrev(arc->getPrev());
         arc->getNext()->setSegment0(segment);
      }
      
      if (arc->getSegment0()) arc->getSegment0()->finish(event->getPoint());
      if (arc->getSegment1()) arc->getSegment1()->finish(event->getPoint());
      
      if (arc->getPrev()) checkCircleEvent(arc->getPrev(), event->getX());
      if (arc->getNext()) checkCircleEvent(arc->getNext(), event->getX());
   }
   delete event;
}

void Voronoi::frontInsert(point p)
{
   if (!root) {
      root = new Arc(p);
      return;
   }
   
   for (Arc *arc = root; arc; arc = arc->getNext()) {
      point q, r;
      if (intersect(p,arc,&q)) {
         
         if (arc->getNext() && !intersect(p,arc->getNext(), &r)) {
            arc->getNext()->setPrev(new Arc(arc->getPoint(),arc,arc->getNext()));
            arc->setNext(arc->getNext()->getPrev());
         }
         else arc->setNext(new Arc(arc->getPoint(),arc));
         arc->getNext()->setSegment1(arc->getSegment1());
         
         arc->getNext()->setPrev(new Arc(p,arc,arc->getNext()));
         arc->setNext(arc->getNext()->getPrev());
         arc = arc->getNext(); 
         
         Segment* newSegmentPrev = new Segment(q);
         Segment* newSegmentNext = new Segment(q);
         this->output.emplace_back(newSegmentPrev);
         this->output.emplace_back(newSegmentNext);
         arc->getPrev()->setSegment0(newSegmentPrev);
         arc->getPrev()->setSegment1(newSegmentPrev);
         arc->getNext()->setSegment0(newSegmentNext);
         arc->getNext()->setSegment1(newSegmentNext);
         
         checkCircleEvent(arc, p.x);
         checkCircleEvent(arc->getPrev(), p.x);
         checkCircleEvent(arc->getNext(), p.x);
         return;
      }
   }
   
   Arc *arc;
   for (arc = root; arc->getNext(); arc=arc->getNext()) ; 
   arc->setNext(new Arc(p,arc));  
   
   point start;
   start.x = X0;
   start.y = (arc->getNext()->getPoint().y + arc->getPoint().y) / 2;
   Segment* newSegment = new Segment(start);
   this->output.emplace_back(new Segment(start));
   arc->getNext()->setSegment0(newSegment);
   arc->getNext()->setSegment1(newSegment);
}

void Voronoi::checkCircleEvent(Arc *arc, double x0)
{   
   if (arc->getEvent() && arc->getEvent()->getX() != x0)
      arc->getEvent()->setValid(false);
   arc->setEvent(NULL);
   if (!arc->getPrev() || !arc->getNext())
      return;
   double x;
   point o;
   if (circle(arc->getPrev()->getPoint(), arc->getPoint(), arc->getNext()->getPoint(), &x,&o) && x > x0) {
      
      arc->setEvent(new Event(x, o, arc));
      events.push(arc->getEvent());
   }
}

bool Voronoi::circle(point a, point b, point c, double *x, point *o)
{   
   if ((b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y) > 0)
      return false;
   
   double A = b.x - a.x,  B = b.y - a.y,
          C = c.x - a.x,  D = c.y - a.y,
          E = A*(a.x+b.x) + B*(a.y+b.y),
          F = C*(a.x+c.x) + D*(a.y+c.y),
          G = 2*(A*(c.y-b.y) - B*(c.x-b.x));
   if (G == 0) return false;  
   
   o->x = (D*E-B*F)/G;
   o->y = (A*F-C*E)/G;
   
   *x = o->x + sqrt( pow(a.x - o->x, 2) + pow(a.y - o->y, 2) );
   return true;
}

bool Voronoi::intersect(point p, Arc *arc, point *result)
{
   if (arc->getPoint().x == p.x) return false;
   double a,b;
   if (arc->getPrev()) 
      a = intersection(arc->getPrev()->getPoint(), arc->getPoint(), p.x).y;
   if (arc->getNext()) 
      b = intersection(arc->getPoint(), arc->getNext()->getPoint(), p.x).y;
   if ((!arc->getPrev() || a <= p.y) && (!arc->getNext() || p.y <= b)) {
      result->y = p.y;
      result->x = (arc->getPoint().x*arc->getPoint().x + (arc->getPoint().y-result->y)*(arc->getPoint().y-result->y) - p.x*p.x)
                / (2*arc->getPoint().x - 2*p.x);
      return true;
   }
   return false;
}

point Voronoi::intersection(point p0, point p1, double lineSweep)
{
   point intersectionResult, p = p0;
   double z0 = 2*(p0.x - lineSweep);
   double z1 = 2*(p1.x - lineSweep);
   if (p0.x == p1.x)
      intersectionResult.y = (p0.y + p1.y) / 2;
   else if (p1.x == lineSweep)
      intersectionResult.y = p1.y;
   else if (p0.x == lineSweep) {
      intersectionResult.y = p0.y;
      p = p1;
   } else {
      
      double a = 1/z0 - 1/z1;
      double b = -2*(p0.y/z0 - p1.y/z1);
      double c = (p0.y*p0.y + p0.x*p0.x - lineSweep*lineSweep)/z0
               - (p1.y*p1.y + p1.x*p1.x - lineSweep*lineSweep)/z1;
      intersectionResult.y = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);
   }
   
   intersectionResult.x = (p.x*p.x + (p.y-intersectionResult.y)*(p.y-intersectionResult.y) - lineSweep*lineSweep)/(2*p.x-2*lineSweep);
   return intersectionResult;
}
void Voronoi::finishEdges()
{   
   double lineSweep = X1 + (X1-X0) + (Y1-Y0);
   
   for (Arc *i = root; i->getNext(); i = i->getNext())
      if (i->getSegment1())
         i->getSegment1()->finish(intersection(i->getPoint(), i->getNext()->getPoint(), lineSweep*2));
}

void Voronoi::printOutput()
{   
   std::cout << X0 << " "<< X1 << " " << Y0 << " " << Y1 << std::endl;
   
   std::vector<Segment*>::iterator i;
   for (i = output.begin(); i != output.end(); i++) {
      point p0 = (*i)->getStart();
      point p1 = (*i)->getEnd();
      std::cout << p0.x << " " << p0.y << " " << p1.x << " " << p1.y << std::endl;
   }
}

void Voronoi::fortune(char* inputFileName)
{
   point p;
   std::ifstream input(inputFileName);
  std::chrono::time_point<std::chrono::system_clock> timeStamp0, timeStamp1;
   unsigned long inputCount = 0;
   while (input >> p.x >> p.y) {
      points.push(p);
      if(++inputCount%10000 == 0) std::cout << inputCount << " pontos lidos\n";
      
      if (p.x < X0) X0 = p.x;
      if (p.y < Y0) Y0 = p.y;
      if (p.x > X1) X1 = p.x;
      if (p.y > Y1) Y1 = p.y;
   }
   input.close();
   std::cout << inputCount << " pontos lidos\n";
   
   double dx = (X1-X0+1)/5.0; double dy = (Y1-Y0+1)/5.0;
   X0 -= dx; 
   X1 += dx; 
   Y0 -= dy; 
   Y1 += dy;
   
  timeStamp0 = std::chrono::high_resolution_clock::now();
   while (!points.empty())
   {
      if (!events.empty() && events.top()->getX() <= points.top().x) processEvent();
      else processPoint();
   }
   
   while (!events.empty()) processEvent();

   finishEdges(); 
   timeStamp1 = std::chrono::high_resolution_clock::now();
  
   std::chrono::duration<double, std::milli > duration = timeStamp1 - timeStamp0;

//Otimizado 24813,4 ms
//Não otimizado 70413,6
   printOutput(); 
   std::cout << "Diagrama com " << inputCount << " pontos de entrada criado em " << duration.count() << " milissegundos\n";
}