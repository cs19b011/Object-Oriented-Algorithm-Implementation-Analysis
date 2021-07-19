#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int min3(int a, int b, int c){
    int min = a;
    if(min > b) min = b;
    if(min > c) min = c;
    return min;
}//minimum among 3

class EDD{

    private:
    string s1;
    string s2;
    int n=0, m=0;
    int** matrix;
    int edited=0;
    
    public:
    void assign(string a, string b){
        s1=a;
        s2=b;
        n=s1.length();
        m=s2.length();
        edited=0;
    }//assigning strings
    
    void compdist();
    int dist();
    void table();
};

void EDD::compdist(){
    
    if(n==0 || m==0){
        int x=0;
        throw x;
    }//exception handling
    
    matrix = new int*[n+1];
    for(int i=0; i<n+1; i++) matrix[i] = new int[m+1];//matrix initialization

    for(int i=0; i<=n; i++) matrix[i][0]=i;
    for(int j=1; j<=m; j++) matrix[0][j]=j;//initial defaults in matrix
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            int insert = matrix[i][j-1] + 1;    //for insertion
            int del = matrix[i-1][j] + 1;       //for deleting
            int sub = matrix[i-1][j-1] + 1;     //for substitution
            if(s1[i-1]==s2[j-1]) sub--;         //if same
            matrix[i][j] = min3(insert, del, sub);  //best among 3
        }
    }
    edited=1;
    
}

int EDD::dist(){

    if(n==0 || m==0){
        int x=0;
        throw x;
    }//exception handling
    
    if(edited==0) compdist();
    return matrix[n][m];
}

void EDD::table(){

    if(n==0 || m==0){
        int x=0;
        throw x;
    }//exception handling
    
    if(edited==0) compdist();
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    
    int q;
    cin >> q;
    
    EDD e;
    
    //cout << "hello" << endl;
    
    while(q){
        string s;
        cin >> s;
        q--;
        //cout << q << endl;
        
        if(s == "assign"){
            string a,b;
            cin >> a >> b;
            //cout << "hello" << endl;
            e.assign(a,b);
        }
        
        if(s == "compdist"){
            try{
                e.compdist();
            }
            catch(int x){
                if(x==0) cerr << "Strings unintialized" << endl;
            }//exception handling
        }
        if(s == "dist"){
            int d=0;
            try{
                d=e.dist();
            }
            catch(int x){
                if(x==0) cerr << "Strings unintialized" << endl;
            }//exception handling
            
            cout << d << endl;
        }
        if(s == "table"){
            try{
                e.table();
            }
            catch(int x){
                if(x==0) cerr << "Strings unintialized" << endl;
            }//exception handling
        }
    }
    
    return 0;
}