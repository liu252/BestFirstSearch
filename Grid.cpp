#include "Grid.h"

using namespace std;
Grid::Grid(){
  size = 0;
}
int Grid::operator()(int x, int y){
  return grid[x][y];
}

void Grid::setGrid(){
  string name = getName();

  cout<<"Reading "+name+"..."<<endl;
  ifstream finput(name.c_str());
  if (finput.fail()){//if the reading fails, will output an error message and quit
    cerr<<"Error: Invalid Filename"<<endl;
    exit(1);
  }
  char c;
  stringstream s;
  while((c=finput.get())!='\n')
    s<<c;
  s>>size;

  cout<<"Parsing the grid..."<<endl;
  for(int x= 0; x<size; ++x){
    for(int y= 0; y<size; ++y){
      c = finput.get();
      if(c=='.'){
        grid[x][y]=0;
      }
      else if(c=='+'){
        grid[x][y]=1;
      }
      else if(c=='g'){
        grid[x][y]=0;
        end = Point(x,y);
      }
      else if(c=='i'){
        grid[x][y]=0;
        start = Point(x,y);
      }
    }
    finput.get();//eliminte the null at the end
    finput.get();//eliminate the new line char
  }
  finput.close();
}

string Grid::getName(){
  string temp;
  cout <<"Please enter the filename: ";
  getline(cin, temp);
  return temp;
}
