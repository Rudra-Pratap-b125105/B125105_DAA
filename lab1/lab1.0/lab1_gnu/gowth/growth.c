#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    double exp_base;  
    double log2_pow;  
    double n_pow;     
    double log_pow;   
    double constant;  
} FunctionClass;

// Comparison function
int compare(const void *a, const void *b) {
    FunctionClass *A = (FunctionClass *)a;
    FunctionClass *B = (FunctionClass *)b;
    
    if (A->exp_base != B->exp_base) return (A->exp_base < B->exp_base) ? -1 : 1;
    if (A->log2_pow != B->log2_pow) return (A->log2_pow < B->log2_pow) ? -1 : 1;
    if (A->n_pow != B->n_pow)       return (A->n_pow < B->n_pow) ? -1 : 1;
    if (A->log_pow != B->log_pow)   return (A->log_pow < B->log_pow) ? -1 : 1;
    if (A->constant != B->constant) return (A->constant < B->constant) ? -1 : 1;
    
    return 0;
}

int main() {
    FunctionClass items[] = {
        {"1 / n",          1, 0, -1,   0, 1},
        {"log2(n)",        1, 0, 0,    1, 1},
        {"12 * sqrt(n)",   1, 0, 0.5,  0, 12},
        {"50 * n^0.5",     1, 0, 0.5,  0, 50},
        {"n^0.51",         1, 0, 0.51, 0, 1},
        {"2^32 * n",       1, 0, 1,    0, 4294967296.0},
        {"n * log2(n)",    1, 0, 1,    1, 1},            
        {"n^2 - 324",      1, 0, 2,    0, 1},
        {"100n^2 + 6n",    1, 0, 2,    0, 100},
        {"2n^3",           1, 0, 3,    0, 2},
        {"n^(log2 n)",     1, 1, 0,    0, 1},
        {"3^n",            3, 0, 0,    0, 1}
    };

    int num_items = sizeof(items) / sizeof(items[0]);

    qsort(items, num_items, sizeof(FunctionClass), compare);

    printf("Functions strictly ordered by increasing asymptotic growth rate:\n");
    for (int i = 0; i < num_items; i++) {
        printf("%2d. %-20s\n", i + 1, items[i].name);
    }

    FILE *gp = popen("gnuplot -persistant", "w");
    if (gp == NULL) {
        perror("Error opening gnuplot. Make sure gnuplot is installed.");
        return 1;
    }

    //fprintf(gp, "set terminal png size 1000,800\n");
    fprintf(gp, "set output 'growth_rates.png'\n");
    fprintf(gp, "set logscale xy\n");             
    fprintf(gp, "set xrange [1:1e12]\n");   
    fprintf(gp, "set yrange [1e-13:1e200]\n");
    fprintf(gp, "set title 'Asymptotic Growth Rates of Functions'\n");
    fprintf(gp, "set xlabel 'n'\n");
    fprintf(gp, "set ylabel 'f(n)'\n");
    fprintf(gp, "set key spacing 1.5\n");      
    fprintf(gp, "set key outside right center\n");

    fprintf(gp, "plot "
                "x*(log(x)/log(2)) title 'n log2(n)', "
                "12*x**(0.5) title '12 * n^{0.5}', "
                "1.0/x title '1/n', "
                "(x <= 1e6 ? x**(log(x)/log(2)) : 1/0) title 'n^{log2 n}', "
                "100*x**2 + 6*x title '100n^2 + 6n', "
                "x**(0.51) title 'n^{0.51}', "
                "(x > 18 ? x**2 - 324 : 1/0) title 'n^2 - 324', "
                "50*x**(0.50) title '50 * n^{0.5}', "
                "2*x**3 title '2n^3', "
                "(x <= 415 ? 3**x : 1/0) title '3^n', "
                "x*4294967296.0 title '2^{32} * n', "
                "(log(x)/log(2)) title 'log2(n)' \n");

    fprintf(gp, "exit\n");
    pclose(gp);
    
    return 0;
}