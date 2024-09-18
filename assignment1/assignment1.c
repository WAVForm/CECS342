#include <stdlib.h>
#include <stdio.h>

char* arr_to_str(int* a, int n){
    char* str = (char*)malloc((n*sizeof(char))+1);
    for(int i = 0; i < n; i++){
      str[i] = (char)(a[i]+'0');
    }
    str[n] = '\0';
    return str;
}

int* str_to_arr(char* a, int n){
    int* arr = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        arr[i] = (int)(a[i]-'0');
    }
    return arr;
}

void copy_arr(int* from, int* to, int n){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }
}

int get_n(char* str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int isSorted(int* a, int n){
    for(int i = 0; i < n-1; i++){
        if(a[i] > a[i+1]){
            return 0;
        }
    }
    return 1;
}

void quick_sort(int *a, int n){
    //this image was used as reference: https://miro.medium.com/v2/resize:fit:577/1*bIJvejLlEshkf-ehYJJlWQ.png

    //quick sort array a with n elements
    if(n<=1){
        return;
    }
    int pivot = n-1;
    for(int i = 0; i < n; i++){
        if(a[pivot]<a[i] && pivot>i){ //if pivot is less than current
            for(int j = i; j<pivot; j++){ //move i to where pivot is, moving everything to the left
                int temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
            pivot--; //i is to the left of pivot, so pivot has moved down
            i--; //check element at new i next iteration
        }
    }
    quick_sort(a,pivot);
    quick_sort((a+pivot)+1,(n-pivot)-1);
}


void merge_sort(int *a, int n){
    //this image was used as reference: https://upload.wikimedia.org/wikipedia/commons/thumb/e/e6/Merge_sort_algorithm_diagram.svg/300px-Merge_sort_algorithm_diagram.svg.png

    //merge sort array a with n elements
    if(n <= 1){ //base case
        return;
    }

    //SPLIT
    int half = n/2;

    int* left = a; //left start
    int* right = a+(half); //right start
    int ln = half; //left element amt
    int rn = n-half; //right element amt

    merge_sort(left, ln); //sort left
    merge_sort(right, rn); //sort right

    //MERGE
    int l = 0; //current index of left
    int r = 0; //current index of right
    int *t = (int*)malloc(n*sizeof(int)); //make dynamic int array of size n

    for(int i = 0; i<n; i++){
        if(l<ln){
            if(r<rn){
                if(left[l] <= right[r]){
                    t[i] = left[l++];
                }
                else{
                    t[i] = right[r++];
                }
            }
            else{
                t[i] = left[l++];
            }
        }
        else if(r<rn){
            t[i] = right[r++];
        }
    }
    copy_arr(t,a,n); //copy array from 't' to 'a'
    free(t); //dealloc t
}

int main(int argc, char* argv[]){
    for(int i = 1; i < argc; i++){
        int n = get_n(argv[i]);
        int* qArr = str_to_arr(argv[i], n);
        int* mArr = str_to_arr(argv[i], n);
        quick_sort(qArr, n);
        merge_sort(mArr, n);
        printf("%s,%s\n", arr_to_str(qArr, n), arr_to_str(mArr, n));
        if(!isSorted(qArr, n)){
            return -1;
        }
        if(!isSorted(mArr, n)){
            return -1;
        }
        free(qArr);
        free(mArr);
    }
    printf("Good!\n");
    return 0;
}
