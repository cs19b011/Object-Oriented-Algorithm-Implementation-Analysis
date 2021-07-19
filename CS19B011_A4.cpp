#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T> class Vector{
    
    private:
    
    size_t cap;
    size_t currentSize;
    T* vec;
    
    public:
    
    Vector(size_t c);
    Vector(size_t c, T x);
    Vector();
    
    /*~Vector(){
        delete[] vec;
    }*/
    
    size_t capacity();
    size_t size();
    
    void push(T x);
    void pop();
    T front();
    T back();
    T operator [](size_t i);
    
    void swap(T* x, T* y);
    void sort(size_t low, size_t high);
    
    protected:
    
    size_t partition(size_t low, size_t high);
    
};

template <class T>
    Vector<T>::Vector(size_t c){
        currentSize = 0;
        cap = c;
        vec = new T[c];
    }//creating array with currentSize 0 and capacity c

template <class T>
    Vector<T>::Vector(size_t c, T x){
        currentSize = c;
        cap=c;
        vec = new T[c];
        for(size_t i=0; i!=currentSize; i++) vec[i]=x;
    }//creating array with capacity c and assigning every element with x

template <class T>
    Vector<T>::Vector(){
        currentSize = 0;
        cap = 1;
        vec = new T[1];
    }//creating array with currentSize 0 and capacity 1


template <class T>
    size_t Vector<T>::capacity(){
        return cap;
    }//returning capacity

template <class T>
    size_t Vector<T>::size(){
        return currentSize;
    }//returning currentSize

template <class T>
    void Vector<T>::push(T x){
        if(currentSize<cap){
            currentSize++;
            vec[currentSize-1]=x;
        }//if there is vacant slot assigning the first slot to x
        
        else{
            T* oldVec = new T[cap];
            size_t oldSize = currentSize;
            for(size_t i=0; i!=oldSize; i++) oldVec[i] = vec[i];

            cap*=2;
            vec = new T[cap];
            currentSize = 0;
            for(size_t i=0; i!=oldSize; i++) push(oldVec[i]);
            delete[] oldVec;
            
            push(x);
        }//if there is no vacancy doubling the capacity and recreating new array. Finally re-pushing every element
    }

template <class T>
    void Vector<T>::pop(){
        if(currentSize){
            currentSize--;
            T* oldVec = new T[cap];
            size_t oldSize = currentSize;
            for(size_t i=0; i!=currentSize; i++) oldVec[i] = vec[i];
            
            vec = new T[cap];
            currentSize = 0;
            for(size_t i=0; i!=oldSize; i++) push(oldVec[i]);
            delete[] oldVec;
        }
    }//decreasing currentSize by 1 and recreating and repushing every element to vec

template <class T>
    T Vector<T>::front(){
        if(!currentSize) return -1;
        else return vec[0];
    }

template <class T>
    T Vector<T>::back(){
        if(!currentSize) return -1;
        else return vec[currentSize-1];        
    }

template <class T>
    T Vector<T>::operator [](size_t i){
        if(currentSize<=i) return -1;
        else return vec[i];
    }

template <class T>
    void Vector<T>::swap(T *x, T *y){
        T z = *x;
        *x = *y;
        *y = z;
    }

template <class T>
    void Vector<T>::sort(size_t low, size_t high){
        if(low<high){
            size_t p = partition(low, high);
            if(p !=0) sort(low, p-1);
            sort(p+1, high);
        }
    }//quicksort


template <class T>
    size_t Vector<T>::partition(size_t low, size_t high){
        T pivot = vec[low];
        size_t i = low;
        
        for(size_t j=low+1; j<=high; j++){
            if(vec[j] < pivot){
                i++;
                swap(&vec[i], &vec[j]);
            }
        }//arranging every element such that from low+1 to i elements are < pivot and i+1 to high >=pivot
        
        swap(&vec[i], &vec[low]);//vec[i] here will be < pivot and vec[i+1] >= pivot.. so swaping both 
        return i;
        
    }//partition fn with pivot as beginning element


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    string firstLine;
    getline(cin, firstLine);
    
    std::string::reverse_iterator ite;
    ite = firstLine.rbegin();
    
    Vector<int> arr;
    
    size_t a=0, b=0;
    size_t x=1;
    int checka=0;
    int checkb=0;   //verifying existance of a,b
    
    while(((size_t)(*ite)>=48) && ((size_t)(*ite)<=57)){
        a += (((size_t)(*ite) - 48)*x);
        x*=10;
        ite++;
        checka++;
    }//extracting the no. at the last of firstLine if exist
    
    x=1;
    ite++;
    
    while(((size_t)(*ite)>=48) && ((size_t)(*ite)<=57)){
        b += ((size_t)(*ite) - 48)*x;
        x*=10;
        ite++;
        checkb++;
    }//extracting the no. at the 2nd last of firstLine if exist
    
    if(checka != 0){
        if(checkb != 0) arr = Vector<int>(b, a);
        else arr = Vector<int>(a);
    }
    
    
    int q;
    cin >> q;

    
    while(q){
        string query;
        cin >> query;
        q--;
        
        if(query == "push"){
            int x;
            cin >> x;
            arr.push(x);
        }
        
        if(query == "pop")      arr.pop();
        if(query == "front")    cout << arr.front()     << endl;
        if(query == "back")     cout << arr.back()      << endl;
        if(query == "capacity") cout << arr.capacity()  << endl;
        if(query == "size")     cout << arr.size()      << endl;   
        
        if(query == "sort"){
            size_t low = 0;
            size_t high = arr.size() - 1;
            arr.sort(low, high);
            for(size_t i=0; i<arr.size(); i++) cout << arr[i] << " ";
            cout << endl;
        }
        
        if(query == "element"){
            size_t i;
            cin >> i;
            cout << arr[i] << endl;
        }
    }
    
    
    return 0;
}
