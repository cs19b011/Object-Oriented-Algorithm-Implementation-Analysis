#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

class set3{
    public:
    int a;
    int b;
    int c;  

};

bool operator<(const set3& p1, const set3& p2){
        
        if(p1.a < p2.a) return true;
        if(p1.a > p2.a) return false;
        if(p1.b < p2.b) return true;
        if(p1.b > p2.b) return false;  
        if(p1.c < p2.c) return true;
        else return false;
}

bool operator>(const set3& p1, const set3& p2){
        
        if(p1.a > p2.a) return true;
        if(p1.a < p2.a) return false; 
        if(p1.b > p2.b) return true;
        if(p1.b < p2.b) return false;  
        if(p1.c > p2.c) return true;
        else return false;
}


class Graph{
    
    protected:
    int V;
    vector <pair <int, int>> *AdjList;
    
    int update;
    
    public:
    
    Graph(int V){    
        this->V = V;
        AdjList = new vector <pair <int, int>>[V];
        update = 0;
    }//constructor for pre-assigning the no. of vertices
    
    void AddV();
    void AddE(int a, int b, int w);
    void DelE(int a, int b);
};


void Graph::AddV(){    
        
    vector <pair <int, int>> *oldAdjList;
    oldAdjList = new vector <pair <int, int>>[V];
    
    for(int i=0; i < V; i++) oldAdjList[i] = AdjList[i];//storing old elements in another array
    
    V++;
    AdjList = new vector <pair <int, int>>[V];//new array with new no. of vertices
    for(int i=0; i < V-1; i++) AdjList[i] = oldAdjList[i];
    
    update=0;
}


void Graph::AddE(int a, int b, int w){
    
    if(a < 0 || b < 0) cerr << "Invalid vertex/vertices" << endl;
    if(a > V-1 || b > V-1) cerr << "No existancy of vertex/vertices\nAdd vertex/vertices and try again" << endl;
         
    pair <int, int> pA (b, w);
    pair <int, int> pB (a, w);//making appropriate pairs
    
    auto i = AdjList[a].begin();
    int check = 0;
        
    while(i != AdjList[a].end()){
            
        if((i->second > pA.second) || (i->second == pA.second && i->first > pA.first)){
            AdjList[a].insert(i, pA);
            check++;
            break;
        }//inserting the pair either infront of a pair with just greater weight
        //or with same weight and just greater vertex value
            
        i++;
    }//inserting in a sorted way
        
    if(check == 0) AdjList[a].push_back(pA);
        
    i = AdjList[b].begin();
    check = 0;
        
    while(i != AdjList[b].end()){
        if((i->second > pB.second) || (i->second == pB.second && i->first > pB.first)){
            AdjList[b].insert(i, pB);
            check++;
            break;
        }
            
        i++;
    }
        
    if(check == 0) AdjList[b].push_back(pB);   
    
    update=0;
        
}


void Graph::DelE(int a, int b){

    if(a < 0 || b < 0) cerr << "Invalid vertex/vertices" << endl;
    if(a > V-1 || b > V-1) cerr << "No existancy of vertex/vertices" << endl;       
        
    int check = 0;
        
    for(auto i = AdjList[a].begin(); i != AdjList[a].end(); i++){
        if(i->first == b){
            AdjList[a].erase(i);
            check++;
            break;
            update=0;
        }//finding pair and erasing it
    }
    
    for(auto i = AdjList[b].begin(); i != AdjList[b].end(); i++){
        if(i->first == a){
            AdjList[b].erase(i);
            update=0;
            break;
        }
    }
        
    if(check == 0) cerr << "Edge doesn't exist" << endl;
}

class MST : public Graph{
    
    private:
    priority_queue<pair<int,int>>* tree;
    int verticesInTree;
    bool checkCycle(int u, int v);
    
    public:
    
    MST(int a) : Graph(a){
        tree = new priority_queue<pair<int, int>>[a];
        verticesInTree=a;
        update=0;
    }
    long long int Prims(int a);
    long long int Kruskal();
    void TreeUptodate();
    void DisplayTree();
    
};

long long int MST::Prims(int a){
    
    if(a < 0 || a > V-1) cerr << "Invalid vertex" << endl;
    
    long long int sum=0;
    
    verticesInTree = V;
    tree = new priority_queue<pair<int, int>>[V];
    
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) visited[i] = false;//making bool array with size V and all elements as false        
        
    pair<int, int> *edges = new pair<int, int>[V];
    
    for(int i = 0; i < V; i++){
        edges[i].first = -1;
        edges[i].second = INT_MAX;
    }//making array with two parameter.. 1)parent 2)edge
        
    edges[a].first  = a;
    edges[a].second = 0;
     

    priority_queue <pair<int,int>> queue;//priority queue with weight and edge
    
    pair <int,int> A (0,-(a+1));
    
    queue.push(A);
    visited[a]=true;
    
    while(!queue.empty()){
        auto x = queue.top();
        queue.pop();
        int u = -x.second-1;
        visited[u] = true;
        
        for(auto i = AdjList[u].begin(); i != AdjList[u].end(); i++){
            int v = i->first;
            int w = i->second;
            if(!visited[v] && (w < edges[v].second)){

                edges[v].first = u;
                edges[v].second = w;
                pair <int,int> p1(-w,-(v+1));
                queue.push(p1);
            }
        }//pushing non-visited vertex and edge to the queue in priority wise 
    }
    
    for(int i=0; i < V; i++){
        if(i!=a){
            int j=edges[i].first;
            sum+=edges[i].second;
            pair <int,int> p1(-edges[i].second, -(j+1));
            pair <int,int> p2(-edges[i].second, -(i+1));
            tree[i].push(p1);
            tree[j].push(p2);
        }
    }//making tree using parent-weight table
    
    update=1;

    return sum;
}

bool MST::checkCycle(int u, int v){
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) visited[i] = false;//making bool array with size V and all elements as false
        
    vector <int> queue;//queue for bfs
        
    visited[u] = true;
    queue.push_back(u);
        
    while(queue.size()){
        auto x = *queue.begin();
        queue.erase(queue.begin());
        
        auto a = tree[x];
        
        while(!a.empty()){
            auto b = a.top();
            a.pop();
            int ver=-b.second-1;
            
            if(!visited[ver]){
                visited[ver] = true;
                queue.push_back(ver);
                if(ver == v) return 1;//if found it will cause cycle by adding it so return 1
            }
        }
    }//finding v through BFS
    
    return 0;
}

long long int MST::Kruskal(){

    verticesInTree = V;
    tree = new priority_queue <pair<int, int>> [V];    
    
    long long int sum=0;
    
    priority_queue <set3> E;
    
    for(int i=0; i<V; i++){
        for(auto j=AdjList[i].begin(); j!=AdjList[i].end(); j++){
            if(j->first > i){
                class set3 set;
                set.a = -j->second;
                set.b = -(i+1);
                set.c = -(j->first+1);
                E.push(set);
            }
        }
    }//making a set of edges of whole graph priority-wise
    
    
    int i=0;
    while(i<V-1 && !E.empty()){
        auto A = E.top();
        E.pop();
        
        int u = -A.b -1;
        int v = -A.c-1;
        int w = A.a;
        
        if(!checkCycle(u,v)){
            pair<int,int> p1(w,-(u+1));
            pair<int,int> p2(w,-(v+1));
            tree[u].push(p2);
            tree[v].push(p1);
            sum-=w;
            i++;
        }//adding to tree if it doesn't make cycle
    }
    update=1;
    return sum;
}

void MST::TreeUptodate(){
    if(update == 1) cout << "YES" << endl;
    else cout << "NO" << endl;
}

void MST::DisplayTree(){
    priority_queue <set3> E;
    
    for(int i=0; i<verticesInTree; i++){
        auto a = tree[i];
        while(!a.empty()){
            auto b = a.top();
            a.pop();
            int j = -b.second-1;
            if(j > i){
                class set3 set;
                set.a = b.first;
                set.b = -(i+1);
                set.c = -j-1;
                E.push(set);
            }
        }
    }//making set of edges of tree
    
    while(!E.empty()){
        auto A = E.top();
        E.pop();
        cout << (-(A.b) - 1) << " " << -A.c-1 << " " << -A.a << endl;
    }
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int V;
    cin >> V;
    MST G(V);
    
    int Q;
    cin >> Q;
    
    while(Q){
        string query;
        cin >> query;
        Q--;
        
        if(query == "ADDV") G.AddV();
        
        if(query == "ADDE"){
            int a, b, w;
            cin >> a >> b >> w;
            G.AddE(a, b, w);          
        }
        
        if(query == "DELE"){
            int a, b;
            cin >> a >> b;
            G.DelE(a,b);
        }

        if(query == "Prims"){
            int v;
            cin >> v;
            cout << G.Prims(v) << endl;          
        }
        
        if(query == "Kruskal")  cout << G.Kruskal() << endl;
        
        if(query == "TreeUptodate") G.TreeUptodate();
        if(query == "DisplayTree")  G.DisplayTree();
    } 
    
    
    return 0;
}
