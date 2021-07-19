 #include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define S_MIN -100000001

int maximum(int a, int b, int c){
    int max = a;
    if(max < b) max=b;
    if(max < c) max=c;
    
    return max;
}

class BloomBrain{
    
    private:
    int *S;
    int rooms;
    bool *checkOccupied;
    
    int *forQT, *forQT2;
    long long int subQT(int low, int middle, int high);
    long long int qualityTalks(int low, int high);
    
    int subPlay(int low, int mid, int high);
    
    public:
    BloomBrain(int N);  
    void update(int *array);
    void join(int n);
    void leave(int i);
    void occupied();
    int play(int low, int high);

};


BloomBrain::BloomBrain(int N){
    rooms = N;
    S = new int[rooms];
    forQT = new int[rooms];
    forQT2 = new int[rooms];
    checkOccupied = new bool[rooms];
    
    for(int i=0; i<rooms; i++) checkOccupied[i] = true;
}

long long int BloomBrain::subQT(int low, int middle, int high){
    int i = low;
    int j = middle+1;
    int k = low;
    
    long long int QT = 0;
    
    while((i <= middle) && (j <= high)){
        if(forQT[i] <= forQT[j]){
            forQT2[k] = forQT[i];
            i++;
        }
        
        else{
            forQT2[k] = forQT[j];
            j++;
            QT+= middle + 1 - i;//adding all exchanges that may happen during sorting
        }
        
        k++;
    }
    
    while(i <= middle){
        forQT2[k] = forQT[i];
        i++;
        k++;
    }
    
    while(j <= high){
        forQT2[k] = forQT[j];
        j++;
        k++;
    }
    
    for(int l=low; l<=high; l++) forQT[l] = forQT2[l];
    
    return QT;
}

long long int BloomBrain::qualityTalks(int low, int high){
    
    long long int QT=0;
    
    if(low < high){
        int middle = low + (high - low)/2;
        QT += qualityTalks(low, middle);
        QT += qualityTalks(middle+1, high);
        QT += subQT(low, middle, high);//adding all exchanges that may happen during sorting
    }
    
    return QT;
}

void BloomBrain::update(int *array){
        
    for(int i=0; i<rooms; i++) S[i] = array[i];
    
    int k=0;
    
    for(int i=0; i<rooms; i++){
        if(checkOccupied[i]){
            forQT[k] = S[i];
            k++;
        }
    }//Loading all Seraphic Numbers if occupied
    
    cout << qualityTalks(0, k-1) << endl;
}

void BloomBrain::join(int s){
    
    for(int i=rooms-1; i>=0; i--){
        if(!checkOccupied[i]){
            S[i] = s;
            checkOccupied[i] = true;
            break;
        }//if a slot is empty while checking backward assigning occupied and the seraphic number
    }
}

void BloomBrain::leave(int idx){
    if(idx<rooms && idx>=0){
        S[idx] = 0;
        checkOccupied[idx] = false;
    }//if index is inside the range assigning unoccupied and setting seraphic number as zero as default
}

void BloomBrain::occupied(){
    
    int occ=0;
    
    for(int i=0; i<rooms; i++){
        if(checkOccupied[i]) occ++;
    }
    
    cout << occ << endl;
}


int BloomBrain::subPlay(int low, int mid, int high){
    int sum = 0;
    int sum1 = S_MIN;
    for (int i = mid; i >= low; i--) {
        if(checkOccupied[i]) sum = sum + S[i];
        if (sum > sum1) sum1 = sum;
    }//largest sum of subarray we can get fixing mid as high end
 
    sum = 0;
    int sum2 = S_MIN;
    for (int i = mid + 1; i <= high; i++) {
        if(checkOccupied[i]) sum = sum + S[i];
        if (sum > sum2) sum2 = sum;
    }//largest sum of subarray we can get fixing mid+1 as low end
 
    return maximum(sum1 + sum2, sum1, sum2);
}

int BloomBrain::play(int low, int high){
    
    if(low==high){
        if(checkOccupied[low]) return S[low];
        else return S_MIN;
    }
    
    int mid = low + (high - low)/2;
    return maximum(play(low,mid), play(mid+1,high), subPlay(low,mid,high));
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int N,Q;
    cin >> N >> Q;
    BloomBrain A(N);
    
    for(int i=0; i<Q; i++){
        string query;
        cin >> query;
        
        if(query == "update"){
            int* array;
            array = new int[N];
                
            for(int i=0; i<N; i++) cin >> array[i];         
            
            A.update(array);
        }
        
        if(query == "join"){
            int s;
            cin >> s;
            A.join(s);
        }
        
        if(query == "leave"){
            int idx;
            cin >> idx;
            A.leave(idx);
        }
        
        if(query == "play")     cout << A.play(0,N-1) << endl;
        if(query == "occupied") A.occupied();
    }
    
    
    return 0;
}
