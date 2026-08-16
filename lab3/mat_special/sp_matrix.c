#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Allocate matrix */
int **allocateMatrix(int n)
{
    int **A = (int **)malloc(n * sizeof(int *));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));

        if (A[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    return A;
}

/* Free matrix */
void freeMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}

/* Add matrices */
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* Subtract matrices */
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

/*
   Divide matrix into four blocks and obtain:

   A1 = A11
   A2 = A12

   Since the matrix has the special structure:

       A11 = A22
       A12 = A21
*/
void getBlocks(int **A, int **A1, int **A2, int n)
{
    int k = n / 2;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
        }
    }
}

/*
   Special-pattern matrix multiplication

   A = | A1 A2 |
       | A2 A1 |

   B = | B1 B2 |
       | B2 B1 |
*/
void specialMultiply(int **A, int **B, int **C, int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    /* Allocate blocks */
    int **A1 = allocateMatrix(k);
    int **A2 = allocateMatrix(k);

    int **B1 = allocateMatrix(k);
    int **B2 = allocateMatrix(k);

    /* Temporary matrices */
    int **Aplus = allocateMatrix(k);
    int **Aminus = allocateMatrix(k);

    int **Bplus = allocateMatrix(k);
    int **Bminus = allocateMatrix(k);

    /* Results of two recursive multiplications */
    int **P = allocateMatrix(k);
    int **Q = allocateMatrix(k);

    int **C1 = allocateMatrix(k);
    int **C2 = allocateMatrix(k);

    /*
       Divide A and B into their two unique blocks
    */
    getBlocks(A, A1, A2, n);
    getBlocks(B, B1, B2, n);

    /*
       Aplus  = A1 + A2
       Aminus = A1 - A2
    */
    addMatrix(A1, A2, Aplus, k);
    subtractMatrix(A1, A2, Aminus, k);

    /*
       Bplus  = B1 + B2
       Bminus = B1 - B2
    */
    addMatrix(B1, B2, Bplus, k);
    subtractMatrix(B1, B2, Bminus, k);

    /*
       P = (A1 + A2)(B1 + B2)
    */
    specialMultiply(Aplus, Bplus, P, k);

    /*
       Q = (A1 - A2)(B1 - B2)
    */
    specialMultiply(Aminus, Bminus, Q, k);

    /*
       C1 = (P + Q) / 2
       C2 = (P - Q) / 2
    */
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    /*
       Construct:

           C = | C1 C2 |
               | C2 C1 |
    */
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];

            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }

    /* Free memory */
    freeMatrix(A1, k);
    freeMatrix(A2, k);
    freeMatrix(B1, k);
    freeMatrix(B2, k);

    freeMatrix(Aplus, k);
    freeMatrix(Aminus, k);
    freeMatrix(Bplus, k);
    freeMatrix(Bminus, k);

    freeMatrix(P, k);
    freeMatrix(Q, k);

    freeMatrix(C1, k);
    freeMatrix(C2, k);
}

/* Display matrix */
void displayMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%6d", A[i][j]);

        printf("\n");
    }
}

/* Check special structure */
int isSpecial(int **A, int n)
{
    int k = n / 2;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (A[i][j] != A[i + k][j + k])
                return 0;

            if (A[i][j + k] != A[i + k][j])
                return 0;
        }
    }

    return 1;
}

int main()
{
    int n;

    printf("Enter matrix size n (power of 2): ");
    scanf("%d", &n);

    /* Check size */
    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Error: n must be a positive power of 2.\n");
        return 1;
    }

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    /* Input A */
    printf("\nEnter Matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    /* Input B */
    printf("\nEnter Matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    /* Validate structure */
    if (!isSpecial(A, n) || !isSpecial(B, n))
    {
        printf("\nError: Matrices do not have the required");
        printf(" special structure.\n");

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);

        return 1;
    }

    printf("\nMatrix A:\n");
    displayMatrix(A, n);

    printf("\nMatrix B:\n");
    displayMatrix(B, n);

    /* Perform multiplication */
    clock_t start = clock();

    specialMultiply(A, B, C, n);

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nResult A x B:\n");
    displayMatrix(C, n);

    printf("\nExecution Time: %.6f seconds\n", timeTaken);

    /* Free memory */
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}