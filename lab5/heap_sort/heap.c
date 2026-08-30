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

/* Restore Max Heap property */
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /* Check left child */
    if (left < n && a[left] > a[largest])
        largest = left;

    /* Check right child */
    if (right < n && a[right] > a[largest])
        largest = right;

    /* If largest is not the root */
    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

/* Heap Sort */
void heapSort(int a[], int n)
{
    /* Build Max Heap */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Extract elements one by one */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        /* Restore heap property */
        heapify(a, i, 0);
    }
}

/* Generate random elements and store them in a file */
void generateFile(int n)
{
    FILE *fp = fopen(FILENAME, "w");

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
    FILE *fp = fopen(FILENAME, "r");

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
        printf("%d ", a[i]);

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

    /* Apply Heap Sort */
    heapSort(a, n);

    printf("\nSorted elements using Heap Sort:\n");
    display(a, n);

    free(a);

    return 0;
}