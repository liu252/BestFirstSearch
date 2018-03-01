#include "Node.cpp"
#include "Grid.cpp"
#include <list>
#include <algorithm>
#include <cmath>

#ifndef _BFS_H_
#define _BFS_H_

class BFS {
public:
    BFS(int m);

    float calcDist(Point& p );
    bool isValid(Point& p );
    bool existPoint(Point& p, float cost);
    bool fillOpen(Node& n);

    bool search(Point& s, Point& e, Grid& gr);

    float path(list<Point>& path);

    Grid g;
    Point end, start;
    Point neighbors[4];
    list<Node> open;
    list<Node> closed;
    int mode;
};

#endif
