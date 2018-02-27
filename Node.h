#include "Point.cpp"

#ifndef _NODE_H_
#define _NODE_H_

class Node {
public:
    bool operator==(const Node& o);
    bool operator==(const Point& o);
    bool operator<(const Node& o);
    Point pos, parent;
    float dist, cost;
};

#endif
