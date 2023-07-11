#include <stdio.h>



int isSorted(int* array, int max, int n) {
    printf("%d\n", array[0]);

    if(n == 0){
        return 1;
    }

    if(array[0] > max){
        return 0;
    }

    if(array[1] < array[0] && n > 1){
        return 0;
    }

    return isSorted(array + 1, max, n-1);

}
void main(){
    int arr1[5] = {3,4,8,21};
    int max = 20;
    int n = 4;
    printf("%d\n", isSorted(arr1, max, n));
}