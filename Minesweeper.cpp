#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int min(int a, int b){
    if(a<b) return a;
    return b;
}

class Grid{
    private:
    int N;  //size of grid
    int M;  //no. of mines
    int** mines;    //neighbour mines
    bool** reveal;
    
    public:
    
    int revealed;   //no. of cells revealed
    
    Grid(int N, int M);
    void placeMine(int mine);
    
    void revealCell(int a, int b);
    bool checkMine(int a, int b);
};

Grid::Grid(int N, int M){
    
    revealed=0;
    
    this->N = N;
    this->M = M;    
    mines = new int*[N];
    reveal = new bool*[N];    
    
    for(int i=0; i<N; i++){
        mines[i] = new int[N];
        reveal[i] = new bool[N];
        for(int j=0; j<N; j++){
            mines[i][j] = 0;
            reveal[i][j] = 0;
        }
    }
}


void Grid::placeMine(int mine){ //consider a mine is represented by -1
    
    int a=mine/N;   //row
    int b=mine%N;   //column
    
    if(mines[a][b]==-1) return;
    mines[a][b]=-1;
    
    int lowerI = max(0,   a-1);
    int upperI = min(N-1, a+1);
    int lowerJ = max(0,   b-1);
    int upperJ = min(N-1, b+1);//boundaries for iterator of neighbours    
    
    
    for(int i=lowerI; i<=upperI; i++){
        for(int j=lowerJ; j<=upperJ; j++){
            if(mines[i][j] != -1){
                mines[i][j]++;
            }
        }
    }   //increasing a value among non-mine neighbours indicating an extra mine appeared 
}

void Grid::revealCell(int a, int b){
    if(mines[a][b] == -1) return;   //if mine return
    if(reveal[a][b]) return; //if already revealed return
    
    
    reveal[a][b] = 1;
    revealed++;
        
    if(mines[a][b] == 0){ //if there are no mines in neighbours we need to reveal neighbours
        
        queue <pair<int, int>> Q;   //queue for neighbour cells which have 0 neighbour mines
            
        pair<int, int> P(a,b);
        Q.push(P);
            
        while(!Q.empty()){
                
            auto A = Q.front();
            int x = A.first;
            int y = A.second;
            
            Q.pop();
                
            int lowerI = max(0,x-1);
            int upperI = min(N-1, x+1);
            int lowerJ = max(0,y-1);
            int upperJ = min(N-1, y+1);//boundaries for iterator of neighbours
                
            for(int i=lowerI; i<=upperI; i++){
                for(int j=lowerJ; j<=upperJ; j++){
                    
                    if(mines[i][j] != -1 && reveal[i][j] == 0){
                            
                        reveal[i][j] = 1;
                        revealed++;
                            
                        if(mines[i][j] == 0){
                            pair<int, int> P2(i,j);
                            Q.push(P2);
                        }//if there are 0 neighbour mines, we need to repeat process for that cell
                    }
                }
            }
        }
    }
    
}

bool Grid::checkMine(int a, int b){
    if(mines[a][b] == -1) return 1;
    else return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    
    int N,M;
    cin >> N >> M;
    
    Grid A(N,M);
    
    for(int i=0; i<M; i++){
        int m=0;
        cin >> m;
        A.placeMine(m);
    }

    
    while(1){
        
        int a,b;
        string s1, s2;
        
        cin >> s1;
        if(s1.empty()) break;
        cin >> s2;
        if(s2.empty()) break;
        
        a = stoi(s1);
        b = stoi(s2);
        
        if(A.checkMine(a, b)){
            cout << "Lost" << endl;
            break;
        }
        
        A.revealCell(a, b);
        int R = A.revealed;
        
        if(R < N*N-M) cout << R << endl;
        else{
            cout << "Won" << endl;
            break;            
        }
        
    }//infinite loop - breaks when won/lost/input ends
        
    
    return 0;
}
