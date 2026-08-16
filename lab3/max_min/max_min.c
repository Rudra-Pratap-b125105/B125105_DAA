#include <stdio.h>

struct Result{
    int max;
    int min;
};

/* Divide and Conquer function */
struct Result maxMin(int a[], int low, int high)
{
    struct Result result, left, right;

    /* Base case: only one element */
    if (low == high)
    {
        result.max = a[low];
        result.min = a[low];
        return result;
    }

    /* Base case: two elements */
    if (high == low + 1)
    {
        if (a[low] > a[high])
        {
            result.max = a[low];
            result.min = a[high];
        }
        else
        {
            result.max = a[high];
            result.min = a[low];
        }

        return result;
    }

    /* Divide */
    int mid = low + (high - low) / 2;

    /* Conquer */
    left = maxMin(a, low, mid);
    right = maxMin(a, mid + 1, high);

    /* Combine */
    result.max = (left.max > right.max) ? left.max : right.max;
    result.min = (left.min < right.min) ? left.min : right.min;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    struct Result result = maxMin(a, 0, n - 1);

    printf("\nMaximum element = %d\n", result.max);
    printf("Minimum element = %d\n", result.min);

    return 0;
}