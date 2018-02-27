#include "Point.h"

Point::Point(int a, int b){
   x=a;
   y=b;
 }

bool Point::operator ==(const Point& o){
  return o.x==x && o.y==y;
}

Point Point::operator +(const Point& o){
  return Point(o.x+x, o.y+y);
}
