#include <string.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#ifndef _BEST_FIRST_SEARCH_
#define _BEST_FIRST_SEARCH_

using namespace std;
class BestFirstSearch{
private:
  int** grid;
  int size;
  int goal[2];
  int initial[2];

  void setGrid();
  string getName();
public:
  BestFirstSearch();
  ~BestFirstSearch();
  void print();

  EuclideanDistance(int* point1, int* point2);
  ~EuclideanDistance();

  ManhattenDistance(int* point1, int* point2);
  ~ManhattenDistance();

};
#endif
