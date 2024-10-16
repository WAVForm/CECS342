#include <string>
#include <iostream>
#include <algorithm>
#include "sort.h"
#include "ynlib.h"

int cpp_compare_alpha(struct person& a, struct person& b){
    if(str_eq(a.name, b.name)){
        return a.age > b.age;
    }
    else{
        return str_lt(a.name, b.name);
    }
}

int cpp_compare_age(struct person& a, struct person& b){
        if(a.age == b.age){
            return str_lt(a.name,b.name);
        }
        else{
            return a.age < b.age;
        }
};

int main(int argc, char* argv[]){
    char* nums_str = "645.41, 37.59, 76.41, 5.31, -34.23, 1.11, 1.10, 23.46, 635.47, -876.32, 467.83, 62.25";
    char* people_str = "Hal, 20; Susann, 31; Dwight, 19; Kassandra, 21; Lawrence, 25; Cindy, 22; Cory, 27; Mac, 19; Romana, 27; Doretha, 32; Danna, 20; Zara, 23; Rosalyn, 26; Risa, 24; Benny, 28; Juan, 33; Natalie, 25";
    struct float_arr nums = make_float_arr(nums_str);
    struct people_arr people = make_people_arr(people_str);

    //sort ages
    std::sort(nums.array, nums.array+nums.size);
    std::cout << "Sorted Numbers: \n";
    int i = 0;
    while(i < nums.size){
        std::cout << nums.array[i] << std::endl;
        i++;
    }
    std::cout << "\n\n";

    //alphabetically, then age
    std::sort(people.array, people.array+people.size, cpp_compare_alpha);
    std::cout << "Sorted people alphabetically: \n";
    i = 0;
    while(i < people.size){
        std::cout << people.array[i].name << ","<< people.array[i].age << std::endl;
        i++;
    }

    std::cout << "\n\n";

    //age, then alphabetically
    std::sort(people.array, people.array+people.size, cpp_compare_age);
    std::cout << "Sorted people by age (descending): \n";
    i = 0;
    while(i < people.size){
        std::cout << people.array[i].name << "," << people.array[i].age << std::endl;
        i++;
    }

    std::cout << "\n\n";
}