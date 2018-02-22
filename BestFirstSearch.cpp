#include "BestFirstSearch.h"
using namespace std;
BestFirstSearch::BestFirstSearch(){
  size = 80;
  grid = NULL;
  goal[0]=0;
  goal[1]=0;
  initial[0]=0;
  initial[1]=0;
  setGrid();
}
BestFirstSearch::~BestFirstSearch(){
  cout<<"Deallocating the memory of the grid..."<<endl;
  for(int x=0; x<size; ++x)
    delete grid[x];
  delete grid;
}
void BestFirstSearch::setGrid(){

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

  cout<<"Allocating memory for the grid..."<<endl;
  grid = new int*[size];
  for(int x=0; x<size; ++x)
    grid[x]=new int[size];

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
        goal[0]=x;
        goal[1]=y;
      }
      else if(c=='i'){
        grid[x][y]=0;
        initial[0]=x;
        initial[1]=y;
      }
    }
    finput.get();//eliminte the null at the end
    finput.get();//eliminate the new line char
  }
  finput.close();
}
string BestFirstSearch::getName(){
  string temp;
  cout <<"Please enter the filename: ";
  getline(cin, temp);
  return temp;
}
void BestFirstSearch::print(){
  int temp;
  cout<<"Printing the grid..."<<endl;
  cout<<"N = "<<size<<endl;
  cout<<"goal = ("<<goal[0]<<", "<<goal[1]<<")"<<endl;
  cout<<"initial = ("<<initial[0]<<", "<<initial[1]<<")"<<endl;
  for(int x=0; x<size; ++x){
    for(int y=0; y<size; ++y){
      temp=grid[x][y];
      if(x==goal[0] && y==goal[1])
        cout<<'g';
      else if(x==initial[0] && y==initial[1])
        cout<<'i';
      else if(temp==0)
        cout<<'.';
      else if(temp==1)
        cout<<'+';
      else if(temp==2)
        cout<<'o';
      }
    cout<<endl;
  }

}
