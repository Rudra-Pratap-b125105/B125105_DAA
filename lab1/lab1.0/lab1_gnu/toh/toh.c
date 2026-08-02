#include <stdio.h>
#include <stdlib.h>

unsigned long long moves(int n){
    return (1ULL << n) - 1;
}

void TOH(int n, char from, char aux, char to){
    if(n==1)
    {
        printf("Move Disk 1 : %c -> %c\n", from, to);
        return;
    }
    TOH(n-1, from, to, aux);
    printf("Move Disk %d : %c -> %c\n", n, from, to);
    TOH(n-1, aux, from, to);
}

int main()
{
    int n;
    printf("Enter number of discs : ");
    scanf("%d",&n);
    printf("\nSequence of Moves\n\n");
    TOH(n,'A','B','C');

    printf("\nTotal Moves = %llu\n",moves(n));

    FILE *fp=fopen("toh.dat","w");

    fprintf(fp,"#Discs Moves\n");

    for(int i=1;i<=20;i++)
        fprintf(fp,"%d %llu\n",i,moves(i));

    fclose(fp);

    FILE *gp=fopen("toh.gnu","w");
    fprintf(gp,"set terminal qt\n");
    // fprintf(gp, "set terminal png size 1000,800\n");
    // fprintf(gp, "set output 'toh_for3.png'\n");
    fprintf(gp,"set title 'Tower of Hanoi Analysis'\n");
    fprintf(gp,"set xlabel 'Number of Discs (n)'\n");
    fprintf(gp,"set ylabel 'Total Moves (2^n - 1)'\n");
    fprintf(gp,"set grid\n");
    fprintf(gp,"set key off\n");
    fprintf(gp,
    "plot 'toh.dat' using 1:2 with linespoints "
    "lw 2 pt 7 lc rgb 'blue'\n");

    fclose(gp);
    printf("\nOpening Graph...\n");
    system("gnuplot -persist toh.gnu");
    return 0;
}
/*
The plotted points form an exponential curve, showing that the number of moves grows as 2ⁿ − 1. 
This demonstrates that the recursive Tower of Hanoi algorithm has exponential time complexity, O(2ⁿ).
*/