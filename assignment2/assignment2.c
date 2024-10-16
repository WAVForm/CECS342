#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "ynlib.h"

int main(int argc, char* argv[]){
    char* nums_str = "645.41, 37.59, 76.41, 5.31, -34.23, 1.11, 1.10, 23.46, 635.47, -876.32, 467.83, 62.25";
    char* people_str = "Hal, 20; Susann, 31; Dwight, 19; Kassandra, 21; Lawrence, 25; Cindy, 22; Cory, 27; Mac, 19; Romana, 27; Doretha, 32; Danna, 20; Zara, 23; Rosalyn, 26; Risa, 24; Benny, 28; Juan, 33; Natalie, 25";
    struct float_arr nums = make_float_arr(nums_str);
    struct people_arr people = make_people_arr(people_str);

    //sort ages
    qsort(nums.array, nums.size, sizeof(float), compare_float_gt);
    printf("Sorted numbers: \n");
    int i = 0;
    while(i < nums.size){
        printf("%f\n", nums.array[i]);
        i++;
    }
    printf("\n\n");

    //alphabetically, then age
    qsort(people.array, people.size, sizeof(struct person), compare_alpha);
    printf("Sorted people by alphabetically: \n");
    i = 0;
    while(i < people.size){
        printf("%s, %d\n",people.array[i].name, people.array[i].age);
        i++;
    }

    printf("\n\n");

    //age, then alphabetically
    qsort(people.array, people.size, sizeof(struct person), compare_age);
    printf("Sorted people by age (descending): \n");
    i = 0;
    while(i < people.size){
        printf("%s, %d\n",people.array[i].name, people.array[i].age);
        i++;
    }

    printf("\n\n");
}