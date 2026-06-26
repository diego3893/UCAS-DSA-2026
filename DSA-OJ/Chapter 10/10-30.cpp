#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
using namespace std;

void sort3(vector<int>&, int, int);
int partition(vector<int>&, int, int);
void qsort(vector<int>&);


int main(){
    vector<int> arr;
    int num;
    while(cin >> num){
        arr.push_back(num);
    }
    qsort(arr);
    for(int i=0; i<arr.size(); ++i){
        printf("%d ", arr[i]);
    }
    
    return 0;
}

void sort3(vector<int>& arr, int low, int high){
    int len = high-low+1;
    if(len <= 1){
        return;
    }
    if(len == 2){
        if(arr[low] > arr[high]){
            swap(arr[low], arr[high]);
        }
        return;
    }
    if(len == 3){
        if(arr[low] > arr[low+1]){
            swap(arr[low], arr[low+1]);
        }
        if(arr[low+1] > arr[high]){
            swap(arr[low+1], arr[high]);
        }
        if(arr[low] > arr[low+1]){
            swap(arr[low], arr[low+1]);
        }
        return;
    }
}

int partition(vector<int>& arr, int low, int high){
    int pivot = arr[low];
    while(low < high){
        while(low < high && arr[high] >= pivot){
            high--;
        }
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot){
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void qsort(vector<int>& arr){
    if(arr.empty()){
        return;
    }
    
    stack<pair<int, int>> s; 
    s.push({0, arr.size()-1});

    while(!s.empty()){
        int low = s.top().first;
        int high = s.top().second;
        s.pop();

        if(high-low+1 <= 3){
            sort3(arr, low, high);
            continue;
        }

        int pivot_idx = partition(arr, low, high);

        int left_len = pivot_idx-low;
        int right_len = high-pivot_idx;

        if(left_len > right_len){
            if (pivot_idx-1 > low){
                s.push({low, pivot_idx-1});
            }
            if(high > pivot_idx+1){
                s.push({pivot_idx+1, high});
            }
        }else{
            if(high > pivot_idx+1){
                s.push({pivot_idx+1, high});
            }
            if(pivot_idx - 1 > low){
                s.push({low, pivot_idx-1});
            }
        }
    }
}