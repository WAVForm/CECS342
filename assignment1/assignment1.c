
//includes
#include <stdio.h>
#include <stdlib.h>

char* arr_to_str(int* a, int n){
    char* str = (char*)malloc((n*sizeof(char))+1);
    for(int i = 0; i < n; i++){
      str[i] = (char)(a[i]+'0');
    }
    str[n] = '\0';
    return str;
}

void copy_arr(int* from, int* to, int n){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }
}

int str_match(char* arr, char* sorted, int n){
    for(int i = 0; i < n; i++){
        if(arr[i] != sorted[i]){
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

int merge_test(){
    int test1[] = {3,9,2,9,0,9,5,3,9,7};
    int n1 = sizeof(test1)/sizeof(test1[0]);
    int test2[] = {6,6,2,8,7,2,2,4};
    int n2 = sizeof(test2)/sizeof(test2[0]);
    int test3[] = {3,8,5,0,4,0,2,2,0};
    int n3 = sizeof(test3)/sizeof(test3[0]);
    int test4[] = {9,4,2,4,0,2,7};
    int n4 = sizeof(test4)/sizeof(test4[0]);
    int test5[] = {8,9,3,4,2,2,7,6,8};
    int n5 = sizeof(test5)/sizeof(test5[0]);
    int test6[] = {0};
    int n6 = sizeof(test6)/sizeof(test6[0]);
    int test7[] = {1,2,3,4,5};
    int n7 = sizeof(test7)/sizeof(test7[0]);

    merge_sort(test1, n1);
    if(!str_match(arr_to_str(test1, n1),"0233579999",n1)){
        return 1;
    }
    merge_sort(test2, n2);
    if(!str_match(arr_to_str(test2, n2), "22246678", n2)){
        return 2;
    }
    merge_sort(test3, n3);
    if(!str_match(arr_to_str(test3, n3), "000223458", n3)){
        return 3;
    }
    merge_sort(test4, n4);
    if(!str_match(arr_to_str(test4, n4), "0224479", n4)){
        return 4;
    }
    merge_sort(test5, n5);
    if(!str_match(arr_to_str(test5, n5), "223467889", n5)){
        return 5;
    }
    merge_sort(test6, n6);
    if(!str_match(arr_to_str(test6, n6), "0", n6)){
        return 6;
    }
    merge_sort(test7, n7);
    if(!str_match(arr_to_str(test7, n7), "12345", n7)){
        return 7;
    }
    return 0;
}

int quick_test(){
    int test1[] = {3,9,2,9,0,9,5,3,9,7};
    int n1 = sizeof(test1)/sizeof(test1[0]);
    int test2[] = {6,6,2,8,7,2,2,4};
    int n2 = sizeof(test2)/sizeof(test2[0]);
    int test3[] = {3,8,5,0,4,0,2,2,0};
    int n3 = sizeof(test3)/sizeof(test3[0]);
    int test4[] = {9,4,2,4,0,2,7};
    int n4 = sizeof(test4)/sizeof(test4[0]);
    int test5[] = {8,9,3,4,2,2,7,6,8};
    int n5 = sizeof(test5)/sizeof(test5[0]);
    int test6[] = {0};
    int n6 = sizeof(test6)/sizeof(test6[0]);
    int test7[] = {1,2,3,4,5};
    int n7 = sizeof(test7)/sizeof(test7[0]);

    quick_sort(test1, n1);
    if(!str_match(arr_to_str(test1, n1),"0233579999",n1)){
        return 1;
    }
    quick_sort(test2, n2);
    if(!str_match(arr_to_str(test2, n2), "22246678", n2)){
        return 2;
    }
    quick_sort(test3, n3);
    if(!str_match(arr_to_str(test3, n3), "000223458", n3)){
        return 3;
    }
    quick_sort(test4, n4);
    if(!str_match(arr_to_str(test4, n4), "0224479", n4)){
        return 4;
    }
    quick_sort(test5, n5);
    if(!str_match(arr_to_str(test5, n5), "223467889", n5)){
        return 5;
    }
    quick_sort(test6, n6);
    if(!str_match(arr_to_str(test6, n6), "0", n6)){
        return 6;
    }
    quick_sort(test7, n7);
    if(!str_match(arr_to_str(test7, n7), "12345", n7)){
        return 7;
    }
    return 0;
}

int main(){
    int m = merge_test();
    if(m != 0){
        printf("Merge Test failed at %d\n", m);
        return -1;
    }
    int q = quick_test();
    if(q != 0){
        printf("Quick Test failed at %d\n", q);
        return -1;
    }
    return 0;
}
