#include "BFS.h"

using namespace std;
BFS::BFS() {
    neighbors[0] = Point(-1,0); neighbors[1] = Point(0,1);
    neighbors[2] = Point(1,0); neighbors[3] = Point(0,-1);
}

float BFS::calcDist(Point& p){
    int x = end.x-p.x, y = end.y-p.y;
    float dis =sqrt(x*x+y*y);
    return dis;
}

bool BFS::isValid(Point& p) {
    return (p.x>-1 && p.y>-1 && p.x<g.size && p.y<g.size);
}

bool BFS::existPoint(Point& p, float cost) {
    list<Node>::iterator i;
    i = find(closed.begin(),closed.end(),p);
    if(i != closed.end()) {
        if((*i).cost+(*i).dist<cost)
          return true;
        else{
          closed.erase(i);
          return false;
        }
    }
    i = find(open.begin(),open.end(),p);
    if(i != open.end()){
        if((*i).cost+(*i).dist<cost)
          return true;
        else{
          open.erase(i);
          return false;
        }
    }
    return false;
}

bool BFS::fillOpen(Node& n) {
    float stepCost, nc, dist;
    Point neighbor;

    for(int x=0; x<4; ++x) {
        // one can make diagonals have different cost
        stepCost = x < 4 ? 1 : 1;
        neighbor = n.pos+neighbors[x];
        if(neighbor==end)
          return true;

        if(isValid(neighbor) && g(neighbor.x,neighbor.y) != 1 ) {
            nc = stepCost + n.cost;
            dist = calcDist(neighbor);
            if(!existPoint(neighbor, nc+dist)) {
                Node m;
                m.cost=nc;
                m.dist=dist;
                m.pos=neighbor;
                m.parent=n.pos;
                open.push_back(m);
            }
        }
    }
    return false;
}

bool BFS::search(Point& s, Point& e, Grid& gr) {
    Node n;
    end = e;
    start = s;
    g = gr;
    n.cost = 0;
    n.pos = s;
    n.parent = 0;
    n.dist = calcDist(s);
    open.push_back(n);
    while(!open.empty()) {
        Node n = open.front();
        open.pop_front();
        closed.push_back(n);
        if(fillOpen(n))
          return true;
    }
    return false;
}

float BFS::path(list<Point>& path) {
    path.push_front(end);
    float cost = 1 + closed.back().cost;
    path.push_front(closed.back().pos);
    Point parent = closed.back().parent;

    for(list<Node>::reverse_iterator i=closed.rbegin(); i!= closed.rend(); ++i) {
        if((*i).pos == parent && !((*i).pos == start)) {
            path.push_front((*i).pos);
            parent = (*i).parent;
        }
    }
    path.push_front(start);
    return cost;
}
