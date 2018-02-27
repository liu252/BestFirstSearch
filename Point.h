#ifndef _POINT_H_
#define _POINT_H_

class Point {
public:
    Point(int a=0, int b=0);
    bool operator ==(const Point& o);
    Point operator +(const Point& o);
    int x, y;
};

#endif
