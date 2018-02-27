#include "Node.h"

bool Node::operator==(const Node& o){
  return pos == o.pos;
}
bool Node::operator==(const Point& o){
  return pos == o;
}
bool Node::operator<(const Node& o){
  return dist + cost < o.dist + o.cost;
}
