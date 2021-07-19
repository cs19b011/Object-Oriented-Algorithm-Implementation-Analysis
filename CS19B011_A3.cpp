#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Element{
    int data;
    Element* next;
};

typedef struct Element* eptr;

class Stack{
    private:
    eptr bottom; //acts as head of the linked list
    eptr top;   //acts as tail of the linked list
    
    public:
    void makeNull();    //clearing or making slack
    void Push(int x);
    int Pop();
    int Top();
    bool isEmpty();   
};

void Stack::makeNull(){
    bottom = new struct Element;
    bottom->next=NULL;          //forming head of linked list
    top=NULL;
}

bool Stack::isEmpty(){
    if(bottom->next == NULL) return true;
    else return false;
}

void Stack::Push(int x){
    eptr temp = new struct Element;
    temp->data = x;
    temp->next = NULL;  //storing given data in a temporary struct
    
    if(isEmpty() == true){
        bottom->next = temp;
        top = bottom->next;
    }
    
    else{
        top->next=temp;
        top=top->next;
    }
}

int Stack::Pop(){
    
    if(isEmpty()) return -1;
    
    int x = top->data;
    
    eptr temp = bottom;
    
    while(temp->next != top) temp = temp->next; //getting the pointer below top
    
    temp->next = NULL;
    top=temp;
    
    return x;
}

int Stack::Top(){
    
    if(isEmpty()) return -1;
    return top->data;
}


class Graph{
    private:
    bool** links;
    int vertices;
    bool* visited;
    
    public:
    void setZeroes(int n);
    void makeVisitedList();
    
    void operator+=(pair<int, int> addEdge);
    void operator-=(pair<int, int> delEdge);  
    
    void DFS(int v);
    
    bool detectCycleForSingleVertex(int v, int vprev);
    bool detectCycle();
    int components();
    bool reach(int u, int v);
};

void Graph::setZeroes(int n){           //forming adjacent matrix and setting elements in them with all false/zeroes
    vertices=n;
    links = new bool*[vertices];
        
    for(int i=0; i<vertices; i++){
        
        links[i] = new bool[vertices];
        for(int j=0; j<vertices; j++) links[i][j] = false;
    }
}

void Graph::operator+=(pair<int, int> addEdge){ //adding edge
    int u = addEdge.first;
    int v = addEdge.second;
        
    links[u][v] = true;
    links[v][u] = true;
}

void Graph::operator-=(pair<int, int> delEdge){ //deleting edge
    int u = delEdge.first;
    int v = delEdge.second;
        
    links[u][v] = false;
    links[v][u] = false;
}

void Graph::makeVisitedList(){              //making bool array and assigning false to each element
    visited = new bool[vertices];
    for(int i=0; i<vertices; i++) visited[i]=false;
}

bool Graph::detectCycleForSingleVertex(int v, int vprev){  //detecting cycle for single component
  
    visited[v] = true;
        
    for(int i=0; i<vertices; i++){
        
        if(links[v][i]){
            if(visited[i] && i != vprev)
                return true;
                
            else if(!visited[i]){
                if(detectCycleForSingleVertex(i, v) == true) return true; 
            }
        }
        
    }
    
    return false;

}

bool Graph::detectCycle(){ //detect cycle for whole graph
    
    makeVisitedList();
    
    for(int i=0; i<vertices; i++){
        if(!visited[i]){
            if(detectCycleForSingleVertex(i, -1)) return true;
        }
    }
    
    return false;
}

void Graph::DFS(int v){     //alloting visited for whole connected component for given vertex
    
    visited[v] = true;
    
    Stack S;
    S.makeNull();
    
    S.Push(v);
    int temp;
    
    while(!S.isEmpty()){
        
        temp=S.Top();
        visited[temp] = true;
        
        int check=0;
        for(int i=0; i<vertices; i++){
            if(links[temp][i] && !visited[i]){
                check++;
                S.Push(i);
                break;
            }
        }
        
        if(!check) temp=S.Pop();
    }
    
    
}

int Graph::components(){    //no of connected components
    
    makeVisitedList();
    int n=0;
    
    for(int i=0; i<vertices; i++){
        
        if(!visited[i]){
            DFS(i);     //all the vertices belong to the same connected component will be marked as visited
            n++;        //hence connected graph will be counted as 1 and 
                        //other vertices of the component wont enter into this loop
        }
    }
    
    return n;
}

bool Graph::reach(int u, int v){
    makeVisitedList();
    DFS(u);             //all the vertices belong to the same connected component will be marked as visited
    return visited[v];  //if v is visited both belongs to same connected component so there will be a path
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    
    Stack S;
    S.makeNull();
    
    int q;
    cin >> q;
    
    while(q){
        string query;
        cin >> query;
        q--;
        
        if(query == "push"){
            int x;
            cin >> x;
            S.Push(x);
        }
        
        if(query == "pop") cout << S.Pop() << endl;
        if(query == "top") cout << S.Top() << endl;
        if(query == "empty") cout << S.isEmpty() << endl;
    }
    
    int n,m;
    cin >> n >> m;
    
    Graph G;
    G.setZeroes(n);
    
    while(m){
        string operation;
        cin >> operation;
        m--;
        
        if(operation == "add"){
            pair<int, int> edge;
            cin >> edge.first >> edge.second;
            G+=edge;
        }
        
        if(operation == "del"){
            pair<int, int> edge;
            cin >> edge.first >> edge.second;
            G-=edge;
        }        
        
        if(operation == "cycle")        cout << G.detectCycle() << endl;
        if(operation == "components")   cout << G.components()  << endl;
        
        if(operation == "reach"){
            int u,v;
            cin >> u >> v;
            cout << G.reach(u, v) << endl;
        }
    }
    
    return 0;
}
