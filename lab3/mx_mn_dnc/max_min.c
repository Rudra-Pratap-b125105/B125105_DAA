#include <stdio.h>

struct Result
{
    int max;
    int min;
};

int comparisons = 0;

/* Display the current section */
void displaySection(int a[], int low, int high)
{
    printf("Section [%d - %d]: ", low + 1, high + 1);

    for (int i = low; i <= high; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/* Divide and Conquer */
struct Result maxMin(int a[], int low, int high)
{
    struct Result result;
    struct Result leftResult, rightResult;

    printf("\nSearching ");
    displaySection(a, low, high);

    /* One element */
    if (low == high)
    {
        printf("  -> Only one element: %d\n", a[low]);

        result.max = a[low];
        result.min = a[low];

        return result;
    }

    /* Two elements */
    if (high == low + 1)
    {
        printf("  -> Comparing %d and %d\n",
               a[low], a[high]);

        comparisons++;

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

        printf("  -> Max = %d, Min = %d\n",
               result.max, result.min);

        return result;
    }

    /* Divide */
    int mid = low + (high - low) / 2;

    printf("  -> Divide into:\n");

    printf("     Left  ");
    displaySection(a, low, mid);

    printf("     Right ");
    displaySection(a, mid + 1, high);

    /* Conquer */
    leftResult = maxMin(a, low, mid);
    rightResult = maxMin(a, mid + 1, high);

    /* Combine */

    printf("\nCombining sections [%d - %d] and [%d - %d]\n",
           low + 1, mid + 1,
           mid + 2, high + 1);

    printf("  Comparing maximums: %d vs %d\n",
           leftResult.max, rightResult.max);

    comparisons++;

    if (leftResult.max > rightResult.max)
        result.max = leftResult.max;
    else
        result.max = rightResult.max;

    printf("  -> Maximum = %d\n", result.max);

    printf("  Comparing minimums: %d vs %d\n",
           leftResult.min, rightResult.min);

    comparisons++;

    if (leftResult.min < rightResult.min)
        result.min = leftResult.min;
    else
        result.min = rightResult.min;

    printf("  -> Minimum = %d\n", result.min);

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

    printf("\n========================================\n");
    printf("   MAXIMUM AND MINIMUM USING D&C\n");
    printf("========================================\n");

    struct Result result = maxMin(a, 0, n - 1);

    printf("\n========================================\n");
    printf("              FINAL RESULT\n");
    printf("========================================\n");

    printf("Maximum element = %d\n", result.max);
    printf("Minimum element = %d\n", result.min);

    printf("\nTotal comparisons = %d\n", comparisons);

    printf("Theoretical bound (3n/2 - 2) = %.0f\n",
           (3.0 * n / 2) - 2);

    return 0;
}