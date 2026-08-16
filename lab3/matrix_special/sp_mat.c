#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
    Special matrix structure:

             | M1  M2 |
        M =  | M2  M1 |

    Each M1 and M2 also has the same recursive structure.
*/


/*
   MATRIX MEMORY FUNCTIONS
*/

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

            for (int j = 0; j < i; j++)
                free(A[j]);

            free(A);
            exit(1);
        }
    }

    return A;
}


void freeMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}


/*
   BASIC MATRIX OPERATIONS
*/

void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}


/*
   GENERATE RANDOM SPECIAL-PATTERN MATRIX

   M = | M1 M2 |
       | M2 M1 |

   M1 and M2 themselves follow the same structure.
*/

void generateSpecialMatrix(int **A, int n)
{
    /*
        Base case:
        A 1 x 1 matrix contains a random integer.
    */
    if (n == 1)
    {
        A[0][0] = rand() % 10 + 1;
        return;
    }

    int k = n / 2;

    /*
        Generate the two unique blocks.

        M1 and M2 must themselves have the
        recursive special structure.
    */

    int **M1 = allocateMatrix(k);
    int **M2 = allocateMatrix(k);

    generateSpecialMatrix(M1, k);
    generateSpecialMatrix(M2, k);

    /*
        Construct:

             | M1 M2 |
        A =  | M2 M1 |
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A[i][j]         = M1[i][j];
            A[i][j + k]     = M2[i][j];

            A[i + k][j]     = M2[i][j];
            A[i + k][j + k] = M1[i][j];
        }
    }

    freeMatrix(M1, k);
    freeMatrix(M2, k);
}


/* =========================================================
   DIVIDE AND CONQUER SPECIAL MATRIX MULTIPLICATION

   A = | A1 A2 |
       | A2 A1 |

   B = | B1 B2 |
       | B2 B1 |

   Calculate:

   P = (A1 + A2)(B1 + B2)

   Q = (A1 - A2)(B1 - B2)

   C1 = (P + Q) / 2

   C2 = (P - Q) / 2

   C = | C1 C2 |
       | C2 C1 |

   Recurrence:

   T(n) = 2T(n/2) + O(n^2)

   Therefore:

   T(n) = O(n^2)
   ========================================================= */

void specialMultiply(int **A, int **B, int **C, int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    /*
        Unique blocks of A and B
    */

    int **A1 = allocateMatrix(k);
    int **A2 = allocateMatrix(k);

    int **B1 = allocateMatrix(k);
    int **B2 = allocateMatrix(k);

    /*
        Temporary matrices
    */

    int **Aplus  = allocateMatrix(k);
    int **Aminus = allocateMatrix(k);

    int **Bplus  = allocateMatrix(k);
    int **Bminus = allocateMatrix(k);

    /*
        Results of recursive multiplications
    */

    int **P = allocateMatrix(k);
    int **Q = allocateMatrix(k);

    int **C1 = allocateMatrix(k);
    int **C2 = allocateMatrix(k);


    /*
       Divide A and B into four blocks
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }


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
       Two recursive multiplications

       P = (A1 + A2)(B1 + B2)

       Q = (A1 - A2)(B1 - B2)
    */

    specialMultiply(Aplus, Bplus, P, k);

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
       Construct result:

              | C1 C2 |
       C =    | C2 C1 |
     */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j]         = C1[i][j];
            C[i][j + k]     = C2[i][j];

            C[i + k][j]     = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }


    /*
       Free memory
     */

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


/* 
   CONVENTIONAL MATRIX MULTIPLICATION

   Used only to verify the result for small n.
   Complexity = O(n^3)
  */

void conventionalMultiply(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


/*
   VERIFY TWO MATRICES
 */

int compareMatrices(int **A, int **B, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != B[i][j])
                return 0;
        }
    }

    return 1;
}


/* 
   DISPLAY MATRIX
 */

void displayMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", A[i][j]);
        }

        printf("\n");
    }
}


/* 
   MAIN
 */

int main()
{
    /*
        Maximum matrix size for experiment.

        You can increase this if your computer has
        sufficient memory and processing power.
    */

    int maxN = 256;

    /*
        Number of repetitions.

        Repeating the operation gives a more reliable
        clock() measurement.
    */

    int repetitions = 5;

    /*
        Seed random number generator.
    */

    srand((unsigned int)time(NULL));


    /*
       Open CSV file
    */

    FILE *csv = fopen("special_matrix_results.csv", "w");

    if (csv == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }


    /*
        CSV header
    */

    fprintf(csv,
            "n,n_squared,average_time,time_div_n_squared\n");


    /*
       Open GNUplot data file
    */

    FILE *data = fopen("special_matrix_results.dat", "w");

    if (data == NULL)
    {
        printf("Error creating data file.\n");

        fclose(csv);

        return 1;
    }


    /*
        Data file header
    */

    fprintf(data,
            "# n n_squared average_time time_div_n_squared\n");


    /* 
       Print table heading
     */

    printf("\n");
    printf("===============================================================\n");
    printf(" SPECIAL-PATTERN MATRIX MULTIPLICATION\n");
    printf(" DIVIDE AND CONQUER COMPLEXITY VALIDATION\n");
    printf("===============================================================\n");

    printf("\n");
    printf("%8s %15s %20s %20s\n",
           "n",
           "n^2",
           "Average Time(s)",
           "Time/n^2");

    printf("---------------------------------------------------------------\n");


    /*
        Used to create theoretical curve:

             T(n) = C*n^2

        C is calculated from the largest input.
    */

    double theoreticalConstant = 0.0;


    /* 
       Run experiment for:

       2, 4, 8, 16, ..., maxN
     */

    for (int n = 2; n <= maxN; n *= 2)
    {
        /*
            Allocate matrices
        */

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);


        /*
            Generate random matrices with the
            required recursive special structure.
        */

        generateSpecialMatrix(A, n);
        generateSpecialMatrix(B, n);


        /*
            Correctness validation
            -------------------------------------------------

            For small n, compare D&C result against
            conventional matrix multiplication.
        */

        if (n <= 16)
        {
            int **C1 = allocateMatrix(n);
            int **C2 = allocateMatrix(n);

            specialMultiply(A, B, C1, n);

            conventionalMultiply(A, B, C2, n);

            if (compareMatrices(C1, C2, n))
            {
                printf("\nCorrectness check n=%d : PASSED\n", n);
            }
            else
            {
                printf("\nCorrectness check n=%d : FAILED\n", n);

                freeMatrix(C1, n);
                freeMatrix(C2, n);

                freeMatrix(A, n);
                freeMatrix(B, n);
                freeMatrix(C, n);

                fclose(csv);
                fclose(data);

                return 1;
            }

            freeMatrix(C1, n);
            freeMatrix(C2, n);
        }


        /*
            Measure execution time
        */

        clock_t start = clock();


        for (int r = 0; r < repetitions; r++)
        {
            specialMultiply(A, B, C, n);
        }


        clock_t end = clock();


        /*
            Total time
        */

        double totalTime =
            (double)(end - start) / CLOCKS_PER_SEC;


        /*
            Average time
        */

        double averageTime =
            totalTime / repetitions;


        /*
            Theoretical n^2
        */

        long long nSquared =
            (long long)n * n;


        /*
            Time / n^2
        */

        double timeRatio =
            averageTime / (double)nSquared;


        /*
            Store theoretical constant from largest n.
        */

        if (n == maxN)
        {
            theoreticalConstant = timeRatio;
        }


        /*
            Print results
        */

        printf("%8d %15lld %20.9f %20.12e\n",
               n,
               nSquared,
               averageTime,
               timeRatio);


        /*
            Write to CSV
        */

        fprintf(csv,
                "%d,%lld,%.12f,%.12e\n",
                n,
                nSquared,
                averageTime,
                timeRatio);


        /*
            Write to GNUplot data file
        */

        fprintf(data,
                "%d %lld %.12f %.12e\n",
                n,
                nSquared,
                averageTime,
                timeRatio);


        /*
            Free matrices
        */

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }


    fclose(csv);
    fclose(data);


    /*
       Create GNUplot script
    */

    FILE *gp = fopen("plot.gnu", "w");

    if (gp == NULL)
    {
        printf("\nError creating GNUplot script.\n");
        return 1;
    }


    /*
        If theoreticalConstant is zero, avoid division issues.
    */

    if (theoreticalConstant <= 0)
        theoreticalConstant = 1.0;


    /*
        GRAPH 1
        Execution Time vs n

    */

    fprintf(gp,
        "set terminal png size 1000,600\n"
        "set output 'time_vs_n.png'\n"

        "set title 'Special Matrix Multiplication - Time vs n'\n"
        "set xlabel 'Input Size (n)'\n"
        "set ylabel 'Execution Time (seconds)'\n"

        "set grid\n"
        "set logscale x 2\n"

        "plot 'special_matrix_results.dat' "
        "using 1:3 with linespoints lw 2 "
        "title 'Measured Time'\n"
    );


    /*
        GRAPH 2
        Execution Time vs n^2
    */

    fprintf(gp,
        "set output 'time_vs_n_squared.png'\n"

        "set title 'Validation of O(n^2): Time vs n^2'\n"
        "set xlabel 'n^2'\n"
        "set ylabel 'Execution Time (seconds)'\n"

        "unset logscale x\n"
        "set grid\n"

        "C = %.12e\n"
        "theory(x) = C*x\n"

        "plot 'special_matrix_results.dat' "
        "using 2:3 with linespoints lw 2 "
        "title 'Measured Time', \\ \n"

        "     theory(x) with lines lw 2 "
        "title 'Theoretical C*n^2'\n",
        theoreticalConstant
    );


    /*
        GRAPH 3
        Time / n^2 vs n
    */

    fprintf(gp,
        "set output 'time_ratio_vs_n.png'\n"

        "set title 'Validation of O(n^2): Time / n^2 vs n'\n"
        "set xlabel 'Input Size (n)'\n"
        "set ylabel 'Time / n^2'\n"

        "set logscale x 2\n"
        "set grid\n"

        "plot 'special_matrix_results.dat' "
        "using 1:4 with linespoints lw 2 "
        "title 'Measured Time / n^2'\n"
    );


    fclose(gp);


    /* -----------------------------------------------------
       Run GNUplot
       ----------------------------------------------------- */

    printf("\n===============================================================\n");
    printf("Generating GNUplot graphs...\n");
    printf("===============================================================\n");

    int result = system("gnuplot plot.gnu");


    if (result != 0)
    {
        printf("\nGNUplot could not be executed.\n");
        printf("Make sure GNUplot is installed and in PATH.\n");
    }
    else
    {
        printf("\nGraphs generated successfully:\n");

        printf("1. time_vs_n.png\n");
        printf("2. time_vs_n_squared.png\n");
        printf("3. time_ratio_vs_n.png\n");
    }


    /*
        -----------------------------------------------------
        Open graphs automatically
        -----------------------------------------------------
    */

#ifdef __APPLE__

    system("open time_vs_n.png");
    system("open time_vs_n_squared.png");
    system("open time_ratio_vs_n.png");

#endif


#ifdef __linux__

    system("xdg-open time_vs_n.png >/dev/null 2>&1");
    system("xdg-open time_vs_n_squared.png >/dev/null 2>&1");
    system("xdg-open time_ratio_vs_n.png >/dev/null 2>&1");

#endif


    printf("\nData files generated:\n");
    printf("1. special_matrix_results.csv\n");
    printf("2. special_matrix_results.dat\n");
    printf("3. plot.gnu\n");


    printf("\nTheoretical Complexity:\n");
    printf("T(n) = 2T(n/2) + O(n^2)\n");
    printf("Therefore, T(n) = O(n^2)\n");


    return 0;
}