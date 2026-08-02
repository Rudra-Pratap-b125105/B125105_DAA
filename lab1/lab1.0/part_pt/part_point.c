#include <stdio.h>

int ft(int A[], int n)
{
    int low = 0, high = n - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(A[mid] == 0)
        {
            low = mid + 1;
        }
        else
        {
            if(mid == 0 || A[mid - 1] == 0)
                return mid;
            high = mid - 1;
        }
    }
    return -1;      
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter elements (0's followed by 1's):\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }
        

    int pos = ft(A, n);
    if(pos == -1)
        printf("No transition found.\n");
    else
        printf("Transition occurs at index %d\n", pos);

    return 0;
}