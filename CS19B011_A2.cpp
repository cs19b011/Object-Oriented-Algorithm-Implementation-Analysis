#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Matrix{
    protected:
    long long int** data;           //contains elements in matrix
    long long int noOfRows;
    long long int noOfColumns;
    
    public:
    void buildMatrix(long long int n, long long int m, long long int** M);         //forming matrix by given 2D matrix
    long long int binarySearch(long long int x, long long int k);
    void matrixSearch(long long int x);
};

void Matrix::buildMatrix(long long int n, long long int m, long long int** M){
    
    noOfRows = n;
    noOfColumns = m;
    
    data = new long long int*[noOfRows];
    
    for(long long int i=0; i<n; i++){
        
        data[i] = new long long int[noOfColumns];
        for(long long int j=0; j<m; j++) data[i][j]=M[i][j];
    }
}

long long int Matrix::binarySearch(long long int x, long long int k){
    
    long long int low, high;
    low = 0;
    high = noOfColumns - 1;
    
    if(data[k][0] > x) return -1;
    if(data[k][noOfColumns - 1] < x) return noOfColumns - 1;
    
    while(high >= low){
        long long int middle = (high + low)/2;
        
        if(x == data[k][middle]){
            while(x == data[k][middle]) middle++;
            middle--;
            return middle;
        }
        
        if(x < data[k][middle]) high = middle-1;
        if(x > data[k][middle]) low = middle+1;
    }
    
    return high;
    
}

void Matrix::matrixSearch(long long int x){

    long long int i = -1;
    long long int j = -1;
    
    for(long long int k=0; k<noOfRows; k++){
        
        long long int s;
        s=binarySearch(x,k);
        
        if((s != -1) && (x == data[k][s])){
            i=k;
            j=s;
            
            while(x == data[i][j]) j--;
            
            j++;
            
            break;
        }
        
    }
        
       
    cout<<i<<" "<<j<<"\n";
    
}

class MatrixMedian : public Matrix{
    
    public :
    long long int upperBound(long long int x, long long int k);
    long long int findMedian();
};

long long int MatrixMedian::upperBound(long long int x, long long int k){

    
    if(x > data[k][noOfColumns-1]) return -1;
    
    return binarySearch(x, k)+1;
}

long long int MatrixMedian::findMedian(){
    
    long long int min, max;
    
    long long int m=noOfColumns;
    long long int n=noOfRows;
    
    min = data[0][0];
    max = data[0][m-1];
    
    for(long long int i=0; i<n; i++){
        
        if(min > data[i][0]) min = data[i][0];
        
        if(max < data[i][m - 1]) max = data[i][m - 1];
    } 
    
    long long int count = (n*m + 1)/2; 
    
    while (min < max) 
    { 
        long long int mid = (max + min) / 2; 
        long long int greaterCount = 0;
        
        
        for (long long int i = 0; i < n; i++){
            
            if(mid < data[i][0]) greaterCount += 0;
            else if(mid > data[i][m-1]) greaterCount += m;
            else{
                long long int s = upperBound(mid, i);
                greaterCount += s;
            }
            

        }
        
        
        if (greaterCount < count) min = mid+1;
        else max = mid; 
    }
    
    return min;    
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Prlong long int output to STDOUT */ 
    
    Matrix A;
    long long int rows, columns;

    cin>>rows;
    cin>>columns;
    
    long long int** M;    
    
    M = new long long int*[rows];
    
    for(long long int i=0; i<rows; i++){
        M[i] = new long long int[columns];
        for(long long int j=0; j<columns; j++) cin>>M[i][j];
    }
    
    A.buildMatrix(rows, columns, M);
    
    long long int q;
    cin>>q;
    
    while(q!=0){
        string query;
        cin>>query;
        
        if (query == "BS"){
            long long int x, k;
            cin>>x>> k;
            cout<<A.binarySearch(x, k)<<"\n";
        }
        
        if (query == "MS"){
            long long int x;
            cin>>x;
            A.matrixSearch(x);
        }
        
        if (query == "Median"){
            MatrixMedian B;
            B.buildMatrix(rows, columns, M);
            cout<<B.findMedian()<<"\n";
        }
        
        q--;
    }
    
    
    return 0;
}