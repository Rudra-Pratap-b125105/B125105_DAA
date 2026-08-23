#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int number;
    int colour;   // 0 = Red, 1 = Blue, 2 = Yellow
} Item;


/*---------------------------------------------------------
  Function: sortByColour

  Sorts items as:
      Red -> Blue -> Yellow

  Since the input is already sorted by number and we scan
  from left to right, the numbers within each colour remain
  sorted.

  Time Complexity: O(n)
---------------------------------------------------------*/
void sortByColour(Item arr[], int n)
{
    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));

    if (red == NULL || blue == NULL || yellow == NULL)
    {
        printf("Memory allocation failed.\n");
        free(red);
        free(blue);
        free(yellow);
        exit(1);
    }

    int r = 0, b = 0, y = 0;

    /* First pass: divide items according to colour */
    for (int i = 0; i < n; i++)
    {
        if (arr[i].colour == 0)
            red[r++] = arr[i];

        else if (arr[i].colour == 1)
            blue[b++] = arr[i];

        else
            yellow[y++] = arr[i];
    }

    /* Combine the three groups */
    int k = 0;

    for (int i = 0; i < r; i++)
        arr[k++] = red[i];

    for (int i = 0; i < b; i++)
        arr[k++] = blue[i];

    for (int i = 0; i < y; i++)
        arr[k++] = yellow[i];

    free(red);
    free(blue);
    free(yellow);
}


void displayItems(Item arr[], int n)
{
    int limit = (n < 20) ? n : 20;

    printf("\nFirst %d items after sorting:\n", limit);
    printf("Number\tColour\n");

    for (int i = 0; i < limit; i++)
    {
        if (arr[i].colour == 0)
            printf("%d\tRed\n", arr[i].number);

        else if (arr[i].colour == 1)
            printf("%d\tBlue\n", arr[i].number);

        else
            printf("%d\tYellow\n", arr[i].number);
    }
}


/*---------------------------------------------------------
  Function: createGnuplotScript

  Creates the GNUplot script automatically.
---------------------------------------------------------*/
void createGnuplotScript()
{
    FILE *gp = fopen("plot.gp", "w");

    if (gp == NULL)
    {
        printf("Error creating GNUplot script.\n");
        return;
    }

    fprintf(gp, "set datafile separator ','\n");

    fprintf(gp,
            "set title 'Linear Time Validation of Colour Sorting'\n");

    fprintf(gp, "set xlabel 'Input Size (n)'\n");
    fprintf(gp, "set ylabel 'Execution Time (ms)'\n");

    fprintf(gp, "set grid\n");
    fprintf(gp, "set key top left\n");

    fprintf(gp,
            "plot 'sorting_data.csv' using 1:2 "
            "with linespoints title 'Measured Time'\n");

    fclose(gp);

    printf("\nGNUplot script created: plot.gp\n");
}

int main()
{
    FILE *fp;

    /* Create CSV file */
    fp = fopen("sorting_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }

    fprintf(fp, "n,time_ms,time_per_n\n");

    /*
       Fixed seed makes the experiment reproducible.
    */
    srand(42);

    /*
       Different input sizes are used to validate O(n).
    */
    for (int n = 100000; n <= 5000000; n += 100000)
    {
        Item *arr = malloc(n * sizeof(Item));

        if (arr == NULL)
        {
            printf("Memory allocation failed at n = %d\n", n);
            break;
        }

        /*
           Generate input.

           The numbers are already sorted:
           1, 2, 3, ..., n

           Colours are assigned randomly.
        */
        for (int i = 0; i < n; i++)
        {
            arr[i].number = i + 1;
            arr[i].colour = rand() % 3;
        }

        /*
           Measure only the sorting algorithm.
        */
        clock_t start = clock();

        sortByColour(arr, n);

        clock_t end = clock();

        double time_ms =
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        /*
           Normalized time:
               T(n) / n

           For O(n), this should approximately remain
           constant as n increases.
        */
        double time_per_n = time_ms / n;

        fprintf(fp, "%d,%.6f,%.12f\n",
                n, time_ms, time_per_n);

        printf("n = %d\tTime = %.6f ms\tT(n)/n = %.12f\n",
               n, time_ms, time_per_n);

        free(arr);
    }

    fclose(fp);

    printf("\n---------------------------------------\n");
    printf("Experimental data saved to:\n");
    printf("sorting_data.csv\n");
    printf("---------------------------------------\n");

    /*
       Create GNUplot script.
    */
    createGnuplotScript();
    printf("\nGenerating GNUplot graph...\n");

    int result = system("gnuplot -p plot.gp");

    if (result != 0)
    {
        printf("\nCould not automatically run GNUplot.\n");
        printf("Run manually:\n");
        printf("gnuplot -p plot.gp\n");
    }

    return 0;
}