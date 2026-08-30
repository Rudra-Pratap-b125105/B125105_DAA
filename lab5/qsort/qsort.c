#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "input.txt"

/* Swap two elements */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition the array */
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

/* Quick Sort */
void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

/* Generate random elements and store them in a file */
void generateFile(int n)
{
    FILE *fp;

    fp = fopen(FILENAME, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        int value = rand() % 1000;
        fprintf(fp, "%d ", value);
    }

    fclose(fp);
}

/* Read elements from file */
void readFromFile(int a[], int n)
{
    FILE *fp;

    fp = fopen(FILENAME, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a[i]);
    }

    fclose(fp);
}

/* Display array */
void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 0;
    }

    int *a = (int *)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    /* Initialize random number generator */
    srand(time(NULL));

    /* Generate and store random elements */
    generateFile(n);

    /* Read elements from file */
    readFromFile(a, n);

    printf("\nElements read from file:\n");
    display(a, n);

    /* Sort using Quick Sort */
    quickSort(a, 0, n - 1);

    printf("\nSorted elements using Quick Sort:\n");
    display(a, n);

    free(a);

    return 0;
}