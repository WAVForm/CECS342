#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int str_len(char* str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int num_len(int num){
    int i = 0;
    while(num > 0){
        i++;
        num /= 10;
    }
    return i;
}

int str_to_int(char* str){
    int i = str_len(str)-1;
    int num = 0;
    int place = 1;
    while(i >= 0){
        num += (int)(str[i--]-'0') * (place);
        place *= 10;
    }
    return num;
}

int power(int base, int power){
    for(int i = 1; i < power; i++){
        base *= 10;
    }
    return base;
}

int reverse(int a){
    int i = num_len(a);
    int num = 0;
    int place = power(1, i);
    while(i > 0){
        num += (a%10) * place;
        i--;
        place /= 10;
        a /= 10;
    }
    return num;
}

char* haskell_array(int arr){
    int n = num_len(arr)*2;
    arr = reverse(arr);
    char* h = (char*)malloc((((n)+2)*sizeof(char))+1); //digits and commas + brackets + \0
    for(int i = 0; i < (n); i+=2){
        if(i==0){
            h[i] = '[';
        }
        else{
            h[i] = ',';
        }
        h[i+1] = (char)((arr%10)+'0');
        arr /= 10;
    }
    h[n] = ']';
    h[n+1] = '\0';
    return h;
    
}

int char_match(char a, char b){
    return (a==b)?1:0;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    if(argc != 3){
        return -1;
    }
    //arg 1 is amt, arg 2 is type
    for(int i = 0; i < str_to_int(argv[1]); i++){
        if(char_match(argv[2][0], 'C') || char_match(argv[2][0], 'c')){
            printf("%d ", rand());
        }
        else if(char_match(argv[2][0], 'H') || char_match(argv[2][0], 'h')){
            int r = rand();
            while(reverse(r) < 0){
                r = rand();
            }
            char* h = haskell_array(r);
            printf("%s ", h);
            free(h);
        }
    }
    
    
}