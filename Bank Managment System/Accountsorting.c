#include <stdio.h>
#include <string.h>
void insertionSort(int arr[], int n);
void printArray(int arr[], int n);

// int main()
// {
//     FILE *fptr;
//     fptr = fopen("sort.txt", "r+");
//     if (fptr == NULL)
//     {

//         fptr = fopen("sort.txt", "w+");

//         printf("Error: Could not open file.\n");
//         return 1;
//     }
//     int acc = 0;
//     printf("Enter your acc number \n");
//     scanf("%d", &acc);
//     fprintf(fptr, "acc no : %d\n", acc);
//     fflush(fptr);
//     rewind(fptr);

//     int stor[100];
//     int count = 0;

//     while (fscanf(fptr, "acc no : %d\n", &stor[count]) == 1)
//     {
//         count++;
//     }
//     fclose(fptr);

//     printf("Original array: ");
//     printArray(stor, count);

//     insertionSort(stor, count);

//     printf("after sorting array: ");

//     printArray(stor, count);

//     return 0;
// }

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}