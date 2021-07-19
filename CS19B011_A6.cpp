#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;


template <class T> class Graph{
    private:
    int V;
    vector <pair <int, T>> *AdjList;
    
    public:
    Graph(int v);
    void AddV();
    void AddE(int a, int b, T w);
    void DelE(int a, int b);
    void BFS(int a);
    void SSP(int a);
};

template <class T> 
    Graph<T>::Graph(int V){    
        this->V = V;
        AdjList = new vector <pair <int, T>>[V];
    }//constructor for pre-assigning the no. of vertices

template <class T>
    void Graph<T>::AddV(){    
        
        vector <pair <int, T>> *oldAdjList;
        oldAdjList = new vector <pair <int, T>>[V];
    
        for(int i=0; i < V; i++) oldAdjList[i] = AdjList[i];//storing old elements in another array
    
        V++;
        AdjList = new vector <pair <int, T>>[V];//new array with new no. of vertices
        for(int i=0; i < V-1; i++) AdjList[i] = oldAdjList[i];
    }

template <class T>
    void Graph<T>::AddE(int a, int b, T w){
    
        if(a < 0 || b < 0) cerr << "Invalid vertex/vertices" << endl;
        if(a > V-1 || b > V-1) cerr << "No existancy of vertex/vertices\nAdd vertex/vertices and try again" << endl;
         
        pair <int, T> pA (b, w);
        pair <int, T> pB (a, w);//making appropriate pairs
    
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
        
    }

template <class T>
    void Graph<T>::DelE(int a, int b){

        if(a < 0 || b < 0) cerr << "Invalid vertex/vertices" << endl;
        if(a > V-1 || b > V-1) cerr << "No existancy of vertex/vertices" << endl;       
        
        int check = 0;
        
        for(auto i = AdjList[a].begin(); i != AdjList[a].end(); i++){
            if(i->first == b){
                AdjList[a].erase(i);
                check++;
                break;
            }//finding pair and erasing it
        }
    
        for(auto i = AdjList[b].begin(); i != AdjList[b].end(); i++){
            if(i->first == a){
                AdjList[b].erase(i);
                break;
            }
        }
        
        if(check == 0) cerr << "Edge doesn't exist" << endl;
    }


template <class T>
    void Graph<T>::BFS(int a){
        
        bool *visited = new bool[V];
        for(int i = 0; i < V; i++) visited[i] = false;//making bool array with size V and all elements as false
        
        vector <int> queue;//queue for bfs
        
        visited[a] = true;
        queue.push_back(a);
        
        while(queue.size()){
            auto x = *queue.begin();
            cout << x << " ";
            queue.erase(queue.begin());
            
            for(auto i = AdjList[x].begin(); i != AdjList[x].end(); i++){
                if(!visited[i->first]){
                    visited[i->first]=true;
                    queue.push_back(i->first);
                }//if not visited pushing in queue
            }//pushing vertices linked with x and we have already assigned with desired order
        }
        
        cout << endl;
    }
    
template <class T>
    void Graph<T>::SSP(int a){
       
        bool *visited = new bool[V];
        for(int i = 0; i < V; i++) visited[i] = false;//making bool array with size V and all elements as false        
        
        pair<int, T> *paths = new pair<int, T>[V];
        
        for(int i = 0; i < V; i++){
            paths[i].first = -1;
            paths[i].second = (T)INT_MAX;
        }//making array with two parameter.. 1)nearest parent in recently updated path 2) length of path
        
        paths[a].first  = a;
        paths[a].second = 0;
     
        priority_queue <pair<T,int>> queue;
        
        pair <T,int> A (0,a);
        
        queue.push(A);
        visited[a]=true;
        
        while(queue.size()){
            pair <T,int> x = queue.top();
            queue.pop();
            visited[x.second] = true;
            
            for(auto i = AdjList[x.second].begin(); i != AdjList[x.second].end(); i++){
                if(!visited[i->first]&&((i->second + paths[x.second].second) < paths[i->first].second)){

                    paths[i->first].first = x.second;
                    paths[i->first].second = i->second + paths[x.second].second;
                    pair <T,int> y(-paths[i->first].second,i->first);
                    queue.push(y);
                    
                }
            }
        }
        
        
        for(int i = 0; i < V; i++) cout << paths[i].second << " ";
        cout << endl;
        
    }



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int V;
    cin >> V;
    Graph <int> G(V);
    
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
        
    }
    
    for(int i=0; i<2; i++){
        string query;
        cin >> query;
        
        if(query == "BFS"){
            int a;
            cin >> a;
            
            G.BFS(a);
        }
        
        if(query == "SSP"){
            int a;
            cin >> a;
            
            G.SSP(a);
        }        
    }
    
    
    return 0;
}
