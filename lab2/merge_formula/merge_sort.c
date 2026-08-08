#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *fp;
    int n;

    fp = fopen("merge_data.txt","w");

    fprintf(fp,"#N MergeSort ModifiedMergeSort\n");

    for(n=1000;n<=100000;n+=5000)
    {
        double merge = n * log2((double)n);
        double modified = n * (log((double)n)/log(3.0));

        fprintf(fp,"%d %.2lf %.2lf\n",n,merge,modified);
    }

    fclose(fp);

    FILE *gp=fopen("merge_plot.gp","w");

    fprintf(gp, "set terminal png size 2000,1600\n");
    fprintf(gp, "set output 'merge_formula.png'\n");
    fprintf(gp,"set title 'Merge Sort vs Modified Merge Sort'\n");
    fprintf(gp,"set xlabel 'Input Size (N)'\n");
    fprintf(gp,"set ylabel 'n log n'\n");
    fprintf(gp,"set grid\n");
    fprintf(gp,"plot 'merge_data.txt' using 1:2 with lines lw 2 title 'Merge Sort',\\\n");
    fprintf(gp,"'merge_data.txt' using 1:3 with lines lw 2 title 'Modified Merge Sort'\n");
    fprintf(gp,"pause -1\n");

    fclose(gp);

    system("gnuplot merge_plot.gp");

    return 0;
}