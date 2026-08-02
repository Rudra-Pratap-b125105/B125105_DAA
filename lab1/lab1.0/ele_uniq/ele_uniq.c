#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int A[n];
    srand(time(NULL));

    printf("\nGenerated Array:\n");
    for(int i = 0; i < n; i++)
    {
        A[i] = rand() % 1000;
        printf("%d ", A[i]);
    }

    qsort(A, n, sizeof(int), compare);
    int duplicate = 0;
    for(int i = 0; i < n - 1; i++)
    {
        if(A[i] == A[i + 1])
        {
            duplicate = 1;
            printf("\n\nDuplicate element found: %d\n", A[i]);
            break;
        }
    }
    if(!duplicate)
        printf("\n\nNo duplicate elements found.\n");

    return 0;
}