#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int A[], int n, long long *comparisons)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            (*comparisons)++;

            if (A[j] < A[min])
                min = j;
        }
        /* Exchange A[i] and A[min] */
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

void display(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal Array:\n");
    display(A, n);
    long long comparisons = 0;
    clock_t start = clock();
    selectionSort(A, n, &comparisons);
    clock_t end = clock();
    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nSorted Array:\n");
    display(A, n);
    printf("\nNumber of comparisons: %lld\n", comparisons);
    printf("Execution time: %.6f seconds\n", timeTaken);
    printf("\nTheoretical comparisons:\n");
    printf("n(n-1)/2 = %lld\n",
           (long long)n * (n - 1) / 2);

    printf("\nTime Complexity:\n");
    printf("Best Case  : Theta(n^2)\n");
    printf("Worst Case : Theta(n^2)\n");

    free(A);

    return 0;
}