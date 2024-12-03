// Add element at the end of an array, at the beginning of an array and in the middle of an array.
//If there are 3 elements entered by user via commandline, 1st at start, 2nd at end and 3rd at middle.
//IF only there are 2 elements then 1st at beginning and 2nd at the end. and if only 1, then at the beginning.
// Sort the array in ascending manner and then also reverse the array.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

int main(int argc, char *argv[])
{
    int *arr = (int *)malloc(SIZE * sizeof(int));
    if(arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    int arr1[] = {77, 24, 93, 89, 61, 26, 11, 52, 35};
    int size = sizeof(arr1)/sizeof(arr1[0]);
    for(int i = 0; i < size; i++)
    {
        arr[i] = arr1[i];
    }

    printf("Displaying the the elements in the dynamically allocated array.\n");

    for(int i = 0; i < SIZE; i++)
    {
        printf("%d\t", arr[i]);
    }

     

    return 0;
}