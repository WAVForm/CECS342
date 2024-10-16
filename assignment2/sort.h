#include "ynlib.h"

struct float_arr{
    float* array;
    int size;
};

struct person{
    char* name;
    int age;
};

struct people_arr{
    struct person* array;
    int size;
};

struct float_arr make_float_arr(char* str){
    int i = 0;
    int size = 1;
    while(str[i] != '\0'){
        if(str[i] == ','){size++;}
        i++;
    }
    float* arr = (float*)malloc((size)*sizeof(float));
    
    int j = 0;
    i = 0;
    int index = 0;
    while(str[j] != '\0'){
        if(str[j] == ','){
            char* num_str = substring(str,i,j-1);
            if(!can_be_float(num_str)){exit(1);}
            arr[index++] = str_to_float(num_str);
            i = j+1;
        }
        j++;
    }

    //account for last number without comma terminator
    char* num_str = substring(str,i,j);
    if(!can_be_float(num_str)){exit(1);}
    arr[index++] = str_to_float(num_str);

    struct float_arr a;
    a.array = arr;
    a.size = size;
    return a;
}

struct person str_to_person(char* str){
    struct person p;
    int i = 0;
    int j = 0;
    str = clear_spaces(str);
    while(str[j] != ';' && str[j] != '\0'){
        if(str[j] == ','){
            p.name = substring(str, i, j-1);
            i = j+1;
        }
        j++;
    }
    p.age = str_to_int(substring(str, i, j-1));
    return p;
}

struct people_arr make_people_arr(char* str){
    int i = 0;
    int size = 1;
    while(str[i] != '\0'){
        if(str[i]==';'){size++;}
        i++;
    }
    struct person* arr = (struct person*)malloc((size)*sizeof(struct person));
    int j = 0;
    i = 0;
    int index = 0;
    while(str[j] != '\0'){
        if(str[j] == ';'){
            char* person_str = substring(str,i,j);
            arr[index++] = str_to_person(person_str);
            i = j+1;
        }
        j++;
    }
    char* person_str = substring(str,i,j);
    arr[index++] = str_to_person(person_str);
    struct people_arr a;
    a.array = arr;
    a.size = size;
    return a;
}

int compare_float_gt(const void* a, const void* b){
    return *(float*)a > *(float*)b;
}

int compare_alpha(const void* a, const void* b){
    struct person pa = *(struct person*)a;
    struct person pb = *(struct person*)b;
    if(str_eq(pa.name, pb.name)){
        return pa.age > pb.age;
    }
    else{
        return str_gt(pa.name, pb.name);
    }
}

int compare_age(const void* a, const void* b){
        struct person pa = *(struct person*)a;
        struct person pb = *(struct person*)b;
        if(pa.age == pb.age){
            return str_gt(pa.name,pb.name);
        }
        else{
            return pa.age < pb.age;
        }
};