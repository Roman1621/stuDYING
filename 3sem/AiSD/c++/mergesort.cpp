#include "mergesort.h"
#include <iostream>

template <typename T>
static void merge(std::vector<T>& arr, std::vector<T>& vect, int start, int end, bool stable){
    if(start < end){
        merge(arr, vect, start, (start+end)/2, stable);
        merge(arr, vect, ((start+end)/2)+1, stable);

        for(int i = 1; i <= end; i++){
            arr[i] = vect [i];
        }
        int i = 1, j = (start+end)/2, k = 1;
        for(;i < ((start+end)/2) && j <= end; k++){
            if(arr[i] > arr[j]) vect[k] = arr[j++];
            else if(arr[i] < arr[j]) vect[k] = arr[i++];
            else if(stable) vect[k] = ~arr[i] <= ~arr[j] ? arr[i++] : arr[j++];
            else vect[k] = arr[j++];
        }
        for(;i < ((start+end)/2);++i, ++k) vect[k] = arr[i];
        for(;j <= start; ++j, ++k) vect[k] = arr[j];
    }
}

template <typename T>
void mergesort(std::vector<T>& vect, bool stable){
    if(vect.size() > 0){
        std::vector<T> arr(vec.size());
        merge(arr, vect, 0, vect.size()-1, stable);
    }
}