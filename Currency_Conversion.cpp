/*

Queries:
The next line will be a positive integer q, the number of queries.
Finally, we will have q lines with three integers, s, t, and X, where s is index of starting currency, t is index of target currency, and X is the amount of units of starting currency that must be converted into the target currency.

Constraints:
1 <= C <= 15
C <= N <= 100
1 <= q <= 10000
0 <= s,t < N

Output Format:
Output should be q lines, each containing the answer to the corresponding query.
Answer for a particular query can be one of the following:
    -1, if conversion is not possible through any means, following the treaty.
    a floating point value(upto 3 decimals), showing, maximum number of units of target currency.
    INF, if there is a path from s to t through an increasing weight cycle.

*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <iomanip>
using namespace std;

template <class T> class Graph{
    private:
    int V;
    T** AdjMatx;
    
    public:
    void makeNull(int V);
    void AddE(int a, int b, T w);
    T edge(int a, int b);
};//template graph class

template <class T> 
    void Graph<T>::makeNull(int V){    
        this->V = V;
        AdjMatx = new T*[V];
        
        for(int i=0; i<V; i++){
            AdjMatx[i] = new T[V];
            for(int j=0; j<V; j++) AdjMatx[i][j] = 0;
        }
    }

template <class T>
    void Graph<T>::AddE(int a, int b, T w){
        AdjMatx[a][b] = w;
    }

template <class T>
    T Graph<T>::edge(int a, int b){        
        
        return AdjMatx[a][b];
    }

class CurrencySystem{
    private:
    int C, N;
    int* nc;
    Graph<bool> T;
    Graph<float> G;
    Graph<float> Glog;//negative log values of graph G
    
    public:
    void makeNullT(int C){
        this->C = C;
        T.makeNull(C);
        for(int i=0; i<C; i++) T.AddE(i,i,1);
    }//initialization of colours graph and considering edge to i to i
    
    void AddEC(int a, int b){
        T.AddE(a,b,1);
        T.AddE(b,a,1);
    }//adding edge for colours graph bidirectionally
    
    void makeNullG(int N){
        this->N = N;
        G.makeNull(N);
        Glog.makeNull(N);
        nc = new int[N];
    }//initialization of G, Glog and nc
    
    void updateNC(int* A){for(int i=0; i<N; i++) nc[i]=A[i];}//nc elements
    
    void AddEG(int a, int b, float w){
        G.AddE(a,b,w);
        Glog.AddE(a,b,-log10(w));
    }//addEdge for G, Glog
    
    
    float currencyConversion(int s, int t, float X);
};

float CurrencySystem::currencyConversion(int s, int t, float X){
    
    float *dist = new float[N];
    for(int i=0; i<N; i++) dist[i] = INT_MAX;//short distances from s
    
    dist[s] = 0;
    
    float prevD = dist[t];
    for(int n=0; n<N; n++){
        prevD = dist[t];
        for(int u=0; u<N; u++){
            for(int v=0; v<N; v++){
                if(T.edge(nc[u], nc[v])){//exchange check
                    if(dist[u]!=INT_MAX && dist[u]+Glog.edge(u,v) < dist[v]){
                        dist[v] = dist[u]+Glog.edge(u,v);
                    }
                }
            }
        }
    }
  
    //now prevD is shortest distance after N-1 cycles
    
    if(dist[t]!=prevD) return -2;
    if(dist[t]==INT_MAX) return -1;
    else return X*pow(10,-dist[t]);
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int C, m;
    cin >> C >> m;
    
    CurrencySystem CS;
    CS.makeNullT(C);
    
    while(m){
        int a,b;
        cin >> a >> b;
        CS.AddEC(a,b);
        m--;
    }
    
    int N;
    cin >> N;
    CS.makeNullG(N);
    
    int* nc;
    nc = new int[N];
    
    for(int i=0; i<N; i++) cin >> nc[i];
    CS.updateNC(nc);
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            float w;
            cin >> w;
            CS.AddEG(i, j, w);
        }
    }
    
    int q;
    cin >> q;
    
    while(q){
        int s,t;
        float X;
        
        cin >> s >> t >> X;
        float curr = CS.currencyConversion(s, t, X);
        
        if(curr == -1) cout << "-1" << endl;
        else if(curr == -2) cout << "INF" << endl;
        else cout << fixed << setprecision(3) << curr << endl;
        
        q--;
    }
    
    return 0;
}
