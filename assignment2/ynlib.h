#ifndef YNLIB_H
#define YNLIB_H

    #include <stdlib.h>

    //string functions
    char* concat_strs(char* a, char* b){
        int size = 0;
        int i = 0;
        while(a[i] != '\0'){
            size++;
            i++;
        }
        i = 0;
        while(b[i] != '\0'){
            size++;
            i++;
        }
        char* str = (char*)malloc((size+1)*sizeof(char));
        str[size] = '\0';
        i = 0;
        int str_i = 0;
        while(a[i] != '\0'){
            str[str_i] = a[i];
            i++;
            str_i++;
        }
        i = 0;
        while(b[i] != '\0'){
            str[str_i] = b[i];
            i++;
            str_i++;
        }
        return str;
    }

    int str_eq(char* a, char* b){
        int i = 0;
        while(a[i] != '\0' && b[i] != '\0' && a[i] == b[i]){
            i++;
        }
        if(a[i] == '\0' && b[i] == '\0'){
            return 1;
        }
        else{
            return 0;
        }
    }

    int str_gt(char* a, char* b){
        int i = 0;
        while(a[i] != '\0' && b[i] != '\0'){
            if((a[i]>b[i])){
                return 1;
            }
            else if(a[i]<=b[i]){
                return 0;
            }
            i++;
        }
        return 0;
    }

    int str_lt(char* a, char* b){
        int i = 0;
        while(a[i] != '\0' && b[i] != '\0'){
            if((a[i]<b[i])){
                return 1;
            }
            else if(a[i]>=b[i]){
                return 0;
            }
            i++;
        }
        return 0;
    }

    char* substring(char* str, int start_i, int end_i){
        //start and end inclusive
        if(end_i < start_i){return NULL;}
        int size = (end_i+1)-start_i;
        char* substr = (char*)malloc((size+1)*sizeof(char));
        int i = 0;
        int index = 0;
        while(str[i] != '\0'){
            if(i >= start_i && i <= end_i){
                substr[index++] = str[i];
            }
            i++;
        }
        substr[index] = '\0';
        return substr;
    }

    char* clear_spaces(char* str){
        int i = 0;
        int size = 0;
        while(str[i] != '\0'){
            if(str[i] != ' '){
                size++;
            }
            i++;
        }
        char* new_str = (char*)malloc(size*sizeof(char));
        i = 0;
        int j = 0;
        while(str[i] != '\0'){
            if(str[i] != ' '){
                new_str[j] = str[i];
                j++;
            }
            i++;
        }

        return new_str;
    }
    //string functions

    //conversions
    int str_to_int(char* arg){
        int neg = 1;
        int place = 0;
        int i = 0;
        while(arg[i] != '\0'){
            if(arg[i] < '0' && arg[i] > '9' && arg[i] != '-'){
                return -1; //only digits allowed (no negatives)
            }
            place = (place == 0)?1:place*10;
            i++;
        }
        int amt = 0;
        i = 0;
        while(arg[i] != '\0'){
            amt += (arg[i] - '0') * place;
            place /= 10;
            i++;
        }
        return amt;
    }

    char* int_to_str(int arg){
        int temp = arg;
        int size = 0;
        while(temp > 0){
            temp /= 10;
            size++;
        }
        char* str = (char*)malloc((size+1)*sizeof(char));
        str[size] = '\0';
        for(int i = size-1; i >= 0; i--){
            str[i] = (char)((arg % 10) + '0');
            arg /= 10;
        }
        return str;
    }

    float str_to_float(char* str){
        float num = 0;
        int neg = 1;
        float place = 0;
        str = clear_spaces(str);

        int i = 0;
        while(str[i] != '\0' && str[i] != '.'){
            if(str[i] == '-'){neg=-1;i++;continue;}
            place = (place==0)?1:place*10;
            i++;
        }

        i = 0;
        while(str[i] != '\0'){
            if(str[i] == '-' || str[i] == '.'){i++;continue;}
            num += (str[i] - '0') * place;
            place /= 10;
            i++;
        }
        num *= (neg==-1)?-1:1;
        return num;
    }
    //conversion

    int can_be_float(char* str){
        int i = 0;
        clear_spaces(str);
        while(str[i] != '\0'){
            if(str[i] < '0' || str[i] > '9' || str[i] != '-' || str[i] != '.'){return 1;}
            i++;
        }
        return 0;
    }

#endif