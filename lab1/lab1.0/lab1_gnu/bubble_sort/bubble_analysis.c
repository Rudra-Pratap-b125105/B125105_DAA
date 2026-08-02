#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copyArray(int src[], int dest[], int n){
    for(int i=0;i<n;i++)
        dest[i]=src[i];
}

long bubbleOptimized(int a[], int n){
    long comparisons=0;
    for(int i=0;i<n-1;i++){
        int swapped=0;
        for(int j=0;j<n-i-1;j++){
            comparisons++;
            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                swapped=1;
            }
        }
        if(!swapped)
            break;
    }
    return comparisons;
}

long bubbleNormal(int a[], int n)
{
    long comparisons=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            comparisons++;

            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    return comparisons;
}

int main()
{
    srand(time(NULL));
    FILE *fp=fopen("bubble.dat","w");
    fprintf(fp,"#Size Optimized Normal\n");
    for(int n=100;n<=2000;n+=100){
        int *arr=malloc(n*sizeof(int));
        int *a1=malloc(n*sizeof(int));
        int *a2=malloc(n*sizeof(int));

        for(int i=0;i<n;i++)
            arr[i]=rand()%10000;

        copyArray(arr,a1,n);
        copyArray(arr,a2,n);

        long opt=bubbleOptimized(a1,n);
        long nor=bubbleNormal(a2,n);

        fprintf(fp,"%d %ld %ld\n",n,opt,nor);

        free(arr);
        free(a1);
        free(a2);
    }
    fclose(fp);
    FILE *gp=fopen("bubble.gnu","w");
    fprintf(gp,"set terminal qt\n");
    // fprintf(gp, "set terminal png size 1000,800\n");
    // fprintf(gp, "set output 'bubble_analysis.png'\n");
    
    fprintf(gp,"set title 'Bubble Sort Performance Analysis'\n");
    fprintf(gp,"set xlabel 'Array Size (n)'\n");
    fprintf(gp,"set ylabel 'Number of Comparisons'\n");
    fprintf(gp,"set grid\n");
    fprintf(gp,"set key top left\n");

    fprintf(gp,
    "plot 'bubble.dat' using 1:2 with linespoints lw 2 pt 7 title 'Optimized',\\\n"
    "     'bubble.dat' using 1:3 with linespoints lw 2 pt 5 title 'Normal'\n");

    fclose(gp);
    printf("Generating graph...\n");
    system("gnuplot -persist bubble.gnu");
    return 0;
}