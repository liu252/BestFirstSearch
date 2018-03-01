#include "BFS.cpp"

using namespace std;
int main( int argc, char* argv[] ) {
    string temp;
    cout <<"Please enter the filename: ";
    getline(cin, temp);
    for (int mode = 1; mode <= 4; mode++)
    {
    Grid g;
    g.setGrid(temp);
    BFS b(mode);
    if(mode == 1)
      cout << "Euclidean + Cost Method:" << endl;
    else if (mode == 3)
      cout << "Euclidean Cost:" << endl;
    else if (mode == 2)
      cout << "Manhatten + Cost Method:" << endl;
    else if (mode == 4)
      cout << "Manhatten Cost:" << endl;
    if(b.search(g.start, g.end, g)){
        list<Point> path;
        float c = b.path(path);
        for(int x=0; x<g.size; ++x){
            for(int y=0; y<g.size; ++y){
                if(g(x,y)==1)
                    cout << "+";
                else if(g.start.x==x && g.start.y==y){
                  cout<<"i";
                }
                else if(g.end.x==x && g.end.y==y){
                  cout<<"g";
                }
                else {
                    if(find(path.begin(),path.end(),Point(x,y))!=path.end())
                        cout << "o";
                    else cout << ".";
                }
            }
            cout<<"\n";
        }

        cout<<"\nPath cost " <<c<< ": ";
        for( list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            cout<< "(" << ( *i ).x << ", " << ( *i ).y << ") ";
        }
        cout << endl;
      }
    }
    cout << "\n\n";
    return 0;
}
