#include <stdlib.h> //for malloc and free
#include <stdio.h> //for printf

char* str_merge(char** strs, int n){
    int size = -1; //size of final string
    for(int i = 0; i < n; i++){
        int j = 0;
        while(strs[i][j++] != '\0'){
            size++; //digit / negative sign
        }
        size++; //comma
    }

    char* str = (char*)malloc((size*sizeof(char)));

    int str_i = 0;
    for(int i = 0; i < n; i++){
        int j = 0;
        while(strs[i][j] != '\0'){
            if(strs[i][j] == '-'){
                str[str_i] = '-';
            }
            else{
                str[str_i] = strs[i][j];
            }
            str_i++;
            j++;
        }

        str[str_i++] = ',';
    }
    str[size] = '\0';
    return str;
}

int int_space(int num){
    int space = 0;
    if(num == 0){
        return 1;
    }
    else if(num < 0){
        space += 1;
        num *= -1;
    }
    while(num > 0){
        space += 1;
        num /= 10;
    }
    return space;
}

int str_space(char* str){
    int n = 0;
    int i = 0;
    while(str[i] != '\0'){
        if(n==0){
            n = 1;
        }
        if(str[i] == ','){
            n++;
        }
        i++;
    }
    return n;
}

int get_end(char* str){
    int size = 0;
    int i = 0;
    while(str[i++] != '\0'){
        size++;
    }
    return size;
}

char* int_to_str(int num){
    int size = int_space(num);
    char* str = (char*)malloc((size*sizeof(char))+1);
    int j = size-1;
    int isNegative = (num < 0)?1:0;
    if(isNegative){
        num *= -1;
    }
    while(num > 0){
        str[j--] = (char)((num%10)+'0');
        num /= 10;
    }
    if(isNegative){
        str[j] = '-';
    }
    str[size] = '\0';
    return str; 
}

char* arr_to_str(int* a, int n){
    char** strs = (char**)malloc(n*sizeof(char*));
    for(int i = 0; i < n; i++){
        int temp = a[i];
        if(temp == 0){
            strs[i] = "0";
            continue;
        }
        else{
            strs[i] = int_to_str(temp);
        }
    }
    char* str = str_merge(strs, n);
    return str;
}

int* str_to_arr(char* a, int n){
    int size = str_space(a);
    int* arr = (int*)malloc(size*sizeof(int));

    int i = get_end(a);
    int arr_i = n-1;

    int number = 0;
    int isNegative = 0;
    int place = 1;
    while(i >= 0){
        if(a[i] == ','){
            if(isNegative){
                number *= -1;
            }
            arr[arr_i--] = number;
            number = 0;
            isNegative = 0;
            place = 1;
        }
        else if(a[i] == '-'){
            isNegative = 1;
        }
        else if(a[i] >= '0' && a[i] <= '9'){
            int digit = (int)(a[i]-'0');
            number += digit * place;
            place *= 10;
        }
        if(i == 0){
            if(isNegative){
                number *= -1;
            }
            arr[arr_i--] = number;
            number = 0;
            isNegative = 0;
            place = 1;
        }
        i--;
    }
    return arr;
}

void copy_arr(int* from, int* to, int n){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }
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
        int n = str_space(argv[i]);
        printf("Array of size: %d: ", n);
        int* qArr = str_to_arr(argv[i], n);
        int* mArr = str_to_arr(argv[i], n);
        quick_sort(qArr, n);
        merge_sort(mArr, n);
        if(!isSorted(qArr, n)){
            return -1;
        }
        if(!isSorted(mArr, n)){
            return -1;
        }
        free(qArr);
        free(mArr);
    }
    printf("Pass\n");
    return 0;
}
