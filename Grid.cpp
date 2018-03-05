#include "Grid.h"

using namespace std;
Grid::Grid(string name)
{
  //Initializes Grid with Default Values
  size = 0;
  mode = 0;
  stepCost = 1;
  totalC = 0;
  totalF = 0;
  setGrid(name);
}
Grid::~Grid()
{
  //Deconstructor of Grid
  start=NULL;
  goal=NULL;
  for(int x=0; x<size; ++x)
  {
    for(int y=0; y<size; ++y)
    {
      delete grid[x][y];
    }
  }
}
Node* Grid::operator()(int x, int y)
{
  //Returns value at specific point in Grid
  return grid[x][y];
}
void Grid::setGrid(string name){
  //Reads file and sets grid
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

  //Parses the grid and creates map
  for(int x= 0; x<size; ++x){
    for(int y= 0; y<size; ++y){
      c = finput.get();
      if(c=='.'){
        grid[x][y]=new Node(x,y,0);
      }
      else if(c=='+'){
        grid[x][y]=new Node(x,y,1);
      }
      else if(c=='g'){
        goal=new Node(x,y,0);
        grid[x][y]=goal;
      }
      else if(c=='i'){
        start=new Node(x,y,0);
        grid[x][y]=start;
      }
    }
    finput.get();//eliminte the null at the end
    finput.get();//eliminate the new line char
  }
  finput.close();
}
void Grid::printGrid(){
  //prints completed grid onto console
  int t;
  for (int x=0; x<size; ++x){
    for (int y=0; y<size; ++y){
      t=grid[x][y]->type;
      if(goal==grid[x][y]){
        cout<<"g";
      }
      else if(start==grid[x][y]){
        cout<<"i";
      }
      else if(t==0){
        cout<<".";
      }
      else if(t==1){
        cout<<"+";
      }
      else if(t==2){
        cout<<"o";
      }
    }
    cout<<endl;
  }
  cout<<endl;
}
bool Grid::search(int m)
{
  //Searches for neighbors around current point
  mode=m;
  if(mode==0 || mode==1)
  {
    stepCost=1;
  }
  else
  {
    stepCost=0;
  }
  fringe.push_back(*start);
  totalF++;
  while(!fringe.empty())
  {
    list<Node>::iterator it = min_element(fringe.begin(),fringe.end());
    fringe.erase(it);
    totalC++;
    if (*it == *goal)
    {
      tracePath();
      return true;
    }
    addNeighbors(*it);
  }

  return false;
}
bool Grid::isValid(int x, int y)
{
  //Checks if point in grid is a valid neighbor
  return (x>=0 && x<size && y>=0 && y<size && grid[x][y]->type!=1);
}
void Grid::addNeighbors(Node n)
{
  Node* neighbor=NULL;
  if(isValid(n.x+1,n.y))
  {
    neighbor=grid[n.x+1][n.y];
    //Finds cost and distance of right neighbor
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x+1,n.y))
    {
      neighbor->parentX=n.x;
      neighbor->parentY=n.y;
      neighbor->cost=n.cost+stepCost;
      neighbor->dist=getDist(n.x+1,n.y);
      //Adds right neighbor to fringe
      totalF++;
      fringe.push_front(*neighbor);
    }
  }
  if(isValid(n.x-1,n.y))
  {
    neighbor=grid[n.x-1][n.y];
    //Finds cost and distance of left neighbor
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x-1,n.y))
    {
      neighbor->parentX=n.x;
      neighbor->parentY=n.y;
      neighbor->cost=n.cost+stepCost;
      neighbor->dist=getDist(n.x-1,n.y);
      //Adds left neighbor to fringe
      totalF++;
      fringe.push_front(*neighbor);
    }
  }
  if(isValid(n.x,n.y+1))
  {
    neighbor=grid[n.x][n.y+1];
    //Finds cost and distance of top neighbor
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x,n.y+1))
    {
      neighbor->parentX=n.x;
      neighbor->parentY=n.y;
      neighbor->cost=n.cost+stepCost;
      neighbor->dist=getDist(n.x,n.y+1);
      //Adds top neighbor to fringe
      totalF++;
      fringe.push_front(*neighbor);
    }
  }
  if(isValid(n.x,n.y-1))
  {
    neighbor=grid[n.x][n.y-1];
    //Finds cost and distance of bottom neighbor
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x,n.y-1))
    {
      neighbor->parentX=n.x;
      neighbor->parentY=n.y;
      neighbor->cost=n.cost+stepCost;
      neighbor->dist=getDist(n.x,n.y-1);
      //Adds bottom neighbor to fringe
      totalF++;
      fringe.push_front(*neighbor);
    }
  }
  neighbor=NULL;
}
double Grid::getDist(int a, int b)
{
  double dist;
  double xDif = abs(goal->x - a);
  double yDif = abs(goal->y - b);
  //Uses Euclidean or Manhattan methods
  if (mode==0 || mode==2)
  {
    //Euclidean method
    dist = sqrt(yDif*yDif+xDif*xDif);
  }
  else
  {
    //Manhattan method
    dist = yDif+ xDif;
  }
  return dist;
}
void Grid::tracePath()
{
  Node* n = goal;
  int step=1;
  while(n->parentX!=start->x || n->parentY!=start->y)
  {
    step++;
    n = grid[n->parentX][n->parentY];
    n->type=2;
  }
  if(mode==0)
  {
    cout<<"Euclidean + Step Cost"<<endl;
  }
  else if(mode==1)
  {
    cout<<"Manhattan + Step Cost"<<endl;
  }
  else if(mode==2)
  {
    cout<<"Euclidean Only"<<endl;
  }
  else
  {
    cout<<"Manhattan Only"<<endl;
  }
  cout<<"Total steps: "<<step<<endl;
  cout<<"Times added to the fringe: "<<totalF<<endl;
  cout<<"Times taken out of the fringe: "<<totalC<<endl<<endl;

  n=NULL;
}
