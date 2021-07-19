#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int FindMax(int a[50], int n){
    int max = a[0];
    
    for(int i=1; i<n; i++){
        if(a[i]>max) max=a[i];
    }
    
    return max;
}           //function to find max value in an array

int FindMin(int a[50], int n){
    int min = a[0];
    
    for(int i=1; i<n; i++){
        if(a[i]<min) min=a[i];
    }

    return min;
}           //function to find min value in an array

int FindAvg(int a[50], int n){
    int sum = 0;
    
    for(int i=0; i<n; i++){
        sum+=a[i];
    }
    
    return sum/n;
}           //function to find floor of avg. in an array

class Matrix{
    private:
    int data[50][50];           //contains elements in matrix
    int rowLength;              //no. of elements in a row
    
    public:
    void fillZeroes(int n);                         //forming a default matrix with all elements zero with given size
    void buildMatrix(int n, int M[50][50]);         //forming matrix by given 2D matrix 
    void changeElement(int a, int b, int number);   //function to change a single element with specified indices
    int returnElement(int a, int b);                //returning with specified indices
    int returnRowLength();                          //returning rowLength
    void SPSUM();                                   //Special Sum
    void MOD();                                     //Mod Multiplication
    void MRS(Matrix N, int k);                      //Matrix Right Shift 
    void MADD(Matrix N, int x);                     //Special Matrix Addition
};

void Matrix::fillZeroes(int n){
    rowLength = n;
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<rowLength; j++) data[i][j] = 0;
    }
}

void Matrix::buildMatrix(int n, int M[50][50]){
    
    rowLength = n;
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<rowLength; j++) data[i][j]=M[i][j];
    }
}

void Matrix::changeElement(int a, int b, int number){
    data[a][b] = number;
}

int Matrix::returnElement(int a, int b){
    return data[a][b];
}

int Matrix::returnRowLength(){
    return rowLength;
}



void PrintMatrix(Matrix M){         //this function doesnt include in class
    
    //size                      => M.returnRowLength()
    //element with indices i,j  => M.returnElement(i,j)
    
    for(int i=0; i<M.returnRowLength(); i++){
        for(int j=0; j<M.returnRowLength(); j++) cout<<M.returnElement(i,j)<<" ";
        cout<<endl;
    }
}        //prints matrix in desired form



Matrix Transpose(Matrix M){         //this function doesnt include in class
    
    
    Matrix N;
    N.fillZeroes(M.returnRowLength());  //creating matrix of same size with all zeroes

    for(int i=0; i<M.returnRowLength(); i++){
        for(int j=0; j<M.returnRowLength(); j++){
            
            //changing (i,j) element of N => from 0 to (j,i) element of M
            
            N.changeElement(i, j, M.returnElement(j, i));
        }
    }
    
    return N;
}               //forming new Matrix which is transpose of given Matrix



Matrix Add(Matrix M, Matrix N){     //this function doesnt include in class
    
    
    Matrix L;
    L.fillZeroes(M.returnRowLength());  //creating matrix of same size with all zeroes
    
    for(int i=0; i<M.returnRowLength(); i++){
        for(int j=0; j<M.returnRowLength(); j++){
            
            //changing (i,j) element of L => from 0 to sum of (i,j) elements of M, N
            
            L.changeElement(i, j, M.returnElement(i, j) + N.returnElement(i, j));
        }
    }
    
    return L;
}              //forming new Matrix formed by addition of given 2 matrices



void Matrix::SPSUM(){
    
    for(int i=0; i<rowLength; i++){
        
        //We don't need to swap elements or create a new matrix and swap
        //Just adding element (j,i) instead of (i,j) at its turn is enough if (i+j) is odd
        
        long long int Sum=0;
        
        for(int j=0; j<rowLength; j++){
            
            if((i+j)%2 == 0) Sum+=data[i][j]; // if sum of indices is even, adds the same element
            
            else Sum+=data[j][i];             //else adds element with indices (j,i)
        }
        
        cout<<Sum;
        
        if(i == rowLength-1) cout<<endl;    //after printing sum of last row we should print "\n" instead of ","
        else cout<<",";
    }
}

void Matrix::MOD(){
    long long int product = 1;
    
    for(int i=0; i<rowLength; i++){
        int r = i%3;    //remainder when i is divided by 3
        
        if(r == 0) product = product*FindMax(data[i], rowLength);
        if(r == 1) product = product*FindMin(data[i], rowLength);
        if(r == 2) product = product*FindAvg(data[i], rowLength);
        
    }
    
    cout<<product<<endl;
}

void Matrix::MRS(Matrix N, int k){
    
    Matrix MR;
    MR.fillZeroes(rowLength);       //new matrix with zeroes and size of rowLength
    
    int n = rowLength;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            
            //considering i1, j1 as new indices after shifting
            // in common cases j1 = j+k.. if it exceeds n then n+j1 = j+k..
            //So j1 = (j+k)%n [dividend = quotient*divisor  + remainder form] 
            
            //in common cases i1 = i + (j+k)/n  => i increases by 1 when j+k exceeds n
            //if it exceeds n, then n+i1 = i + (j+k)/n
            //So i1 = (i+((j+k)/n))%n
            
            int i1 = (i+((j+k)/n))%n;
            int j1 = (j+k)%n;
            MR.changeElement(i1, j1, data[i][j] + N.returnElement(i, j));
        }
    }
    PrintMatrix(MR);
}

void Matrix::MADD(Matrix N, int x){
    
    Matrix V;
    V.buildMatrix(rowLength, data); //we can't access matrix as matrix form in its function.. So creating similar one
    
    if(x==1) PrintMatrix(Add(Transpose(V),N));  //A'+B
    if(x==2) PrintMatrix(Add(V,Transpose(N)));  //A+B'
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    Matrix A, B;
    int q, n;
    cin>>q>>n;
    int M[50][50], N[50][50];     
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cin>>M[i][j];
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cin>>N[i][j];
    }
    
    //Storing matrices in 2D arrays
    
    A.buildMatrix(n, M);
    B.buildMatrix(n, N);
    //converting to class Matrix form
    
    
    while(q){
        string query;
        cin>>query;
        
        if(query == "SPSUM"){
            A.SPSUM();
        }
        
        if(query == "MOD"){
            A.MOD();
        }
        
        if(query == "MRS"){
            int k;
            cin>>k;
            A.MRS(B, k);
        }
        
        if(query == "MADD"){
            int x;
            cin>>x;
            A.MADD(B, x);
        }
        
        q--;
    }
    
    return 0;
}