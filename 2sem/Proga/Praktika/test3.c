#include <stdio.h>
#include <stdlib.h>
#define N 20 

int sr_arifm(int arr[], int n){
int i, sr_arifm = 0; 
for (i=0;i<n;i++){
        sr_arifm += arr[i];
    }
    sr_arifm = sr_arifm/n;
    return sr_arifm;
}
    
 int main(){
     int a = 0, i;
    int arr[N];
    int n = 0;
    while(getchar() != '\n' && n<N){
        scanf("%d", &arr[n]);
        n++;
    }

    for (i = 0; i < n; i++){
        if (arr[i]>sr_arifm(arr, n)){
            a++;
        }
    }
    printf("%d\n", a);
    return 0;
}
