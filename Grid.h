#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#ifndef _GRID_H_
#define _GRID_H_
using namespace std;

class Grid{
private:
  int grid[80][80];

  std::string getName();
public:
    Grid();
    void setGrid(string name);
    int operator()(int x, int y);
    int size;
    Point start;
    Point end;
};
#endif
