#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    int n, element, flag = 0;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Enter key to search: ");
    scanf("%d", &element);
    int low = 0, high = n - 1, mid;
    while(low <= high){
        mid = (low + high) / 2;
        if(arr[mid] == element){
            printf("Element found at index %d", mid);
            flag = 1;
            break;
        }
        else if(element > arr[mid]){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    if(flag == 0) printf("Element not found.");
    return 0;
}