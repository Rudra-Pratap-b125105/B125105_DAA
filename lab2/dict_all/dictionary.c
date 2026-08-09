#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START 1000
#define END 50000
#define STEP 1000
#define REP 100

// DATA STRUCTURES

typedef struct {
    int *a, n, cap;
} UA;

typedef struct {
    int *a, n, cap;
} SA;

typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

typedef struct DNode {
    int key;
    struct DNode *prev, *next;
} DNode;

// ARRAY FUNCTIONS

void uaInit(UA *x,int n) {
    x->cap=n+REP+10;
    x->a=malloc(x->cap*sizeof(int));
    x->n=n;
    for(int i=0;i<n;i++) x->a[i]=rand();
}

void saInit(SA *x,int n) {
    x->cap=n+REP+10;
    x->a=malloc(x->cap*sizeof(int));
    x->n=n;
    for(int i=0;i<n;i++) x->a[i]=i*2;
}

int uaSearch(UA *x,int k) {
    for(int i=0;i<x->n;i++)
        if(x->a[i]==k) return i;
    return -1;
}

int saSearch(SA *x,int k) {
    int l=0,r=x->n-1;
    while(l<=r) {
        int m=(l+r)/2;
        if(x->a[m]==k) return m;
        if(x->a[m]<k) l=m+1;
        else r=m-1;
    }
    return -1;
}

void uaInsert(UA *x,int k) {
    x->a[x->n++]=k;
}

void saInsert(SA *x,int k) {
    int i=x->n-1;
    while(i>=0 && x->a[i]>k) {
        x->a[i+1]=x->a[i];
        i--;
    }
    x->a[i+1]=k;
    x->n++;
}

void uaDelete(UA *x,int p) {
    for(int i=p;i<x->n-1;i++)
        x->a[i]=x->a[i+1];
    x->n--;
}

void saDelete(SA *x,int p) {
    for(int i=p;i<x->n-1;i++)
        x->a[i]=x->a[i+1];
    x->n--;
}

int uaMin(UA *x) {
    int m=x->a[0];
    for(int i=1;i<x->n;i++)
        if(x->a[i]<m) m=x->a[i];
    return m;
}

int uaMax(UA *x) {
    int m=x->a[0];
    for(int i=1;i<x->n;i++)
        if(x->a[i]>m) m=x->a[i];
    return m;
}

int saMin(SA *x) { return x->a[0]; }
int saMax(SA *x) { return x->a[x->n-1]; }

int uaPred(UA *x,int k) {
    int p=-1;
    for(int i=0;i<x->n;i++)
        if(x->a[i]<k && (p==-1 || x->a[i]>p)) p=x->a[i];
    return p;
}

int uaSucc(UA *x,int k) {
    int s=-1;
    for(int i=0;i<x->n;i++)
        if(x->a[i]>k && (s==-1 || x->a[i]<s)) s=x->a[i];
    return s;
}

int saPred(SA *x,int k) {
    int l=0,r=x->n-1,p=-1;
    while(l<=r) {
        int m=(l+r)/2;
        if(x->a[m]<k) p=x->a[m],l=m+1;
        else r=m-1;
    }
    return p;
}

int saSucc(SA *x,int k) {
    int l=0,r=x->n-1,s=-1;
    while(l<=r) {
        int m=(l+r)/2;
        if(x->a[m]>k) s=x->a[m],r=m-1;
        else l=m+1;
    }
    return s;
}

// SINGLY LINKED LIST

SNode *sInsertUnsorted(SNode **h,int k) {
    SNode *p=malloc(sizeof(SNode));
    p->key=k;p->next=*h;*h=p;
    return p;
}

SNode *sInsertSorted(SNode **h,int k) {
    SNode *p=malloc(sizeof(SNode));
    p->key=k;

    if(!*h || (*h)->key>=k) {
        p->next=*h;*h=p;return p;
    }

    SNode *q=*h;
    while(q->next && q->next->key<k) q=q->next;

    p->next=q->next;q->next=p;
    return p;
}

SNode *sBuild(int n,int sorted) {
    SNode *h=NULL;
    for(int i=0;i<n;i++)
        if(sorted) sInsertSorted(&h,i*2);
        else sInsertUnsorted(&h,rand());
    return h;
}

SNode *sSearch(SNode *h,int k) {
    while(h) {
        if(h->key==k) return h;
        h=h->next;
    }
    return NULL;
}

void sDelete(SNode **h,SNode *x) {
    if(!*h || !x) return;

    if(*h==x) {
        *h=x->next;
        free(x);
        return;
    }

    SNode *p=*h;
    while(p->next && p->next!=x) p=p->next;

    if(p->next==x) {
        p->next=x->next;
        free(x);
    }
}

int sMin(SNode *h) {
    int m=h->key;
    for(h=h->next;h;h=h->next)
        if(h->key<m) m=h->key;
    return m;
}

int sMax(SNode *h) {
    int m=h->key;
    for(h=h->next;h;h=h->next)
        if(h->key>m) m=h->key;
    return m;
}

int ssMin(SNode *h) { return h->key; }

int ssMax(SNode *h) {
    while(h->next) h=h->next;
    return h->key;
}

int sPred(SNode *h,int k) {
    int p=-1;
    while(h) {
        if(h->key<k && (p==-1||h->key>p)) p=h->key;
        h=h->next;
    }
    return p;
}

int sSucc(SNode *h,int k) {
    int s=-1;
    while(h) {
        if(h->key>k && (s==-1||h->key<s)) s=h->key;
        h=h->next;
    }
    return s;
}

int ssPred(SNode *h,int k) {
    int p=-1;
    while(h && h->key<k) {
        p=h->key;
        h=h->next;
    }
    return p;
}

int ssSucc(SNode *h,int k) {
    while(h && h->key<=k) h=h->next;
    return h?h->key:-1;
}

// DOUBLY LINKED LIST

DNode *dInsertUnsorted(DNode **h,int k) {
    DNode *p=malloc(sizeof(DNode));
    p->key=k;p->prev=NULL;p->next=*h;
    if(*h) (*h)->prev=p;
    *h=p;
    return p;
}

DNode *dInsertSorted(DNode **h,int k) {
    DNode *p=malloc(sizeof(DNode));
    p->key=k;p->prev=p->next=NULL;

    if(!*h || (*h)->key>=k) {
        p->next=*h;
        if(*h) (*h)->prev=p;
        *h=p;
        return p;
    }

    DNode *q=*h;
    while(q->next && q->next->key<k) q=q->next;

    p->next=q->next;
    p->prev=q;

    if(q->next) q->next->prev=p;
    q->next=p;

    return p;
}

DNode *dBuild(int n,int sorted) {
    DNode *h=NULL;
    for(int i=0;i<n;i++)
        if(sorted) dInsertSorted(&h,i*2);
        else dInsertUnsorted(&h,rand());
    return h;
}

DNode *dSearch(DNode *h,int k) {
    while(h) {
        if(h->key==k) return h;
        h=h->next;
    }
    return NULL;
}

void dDelete(DNode **h,DNode *x) {
    if(!x) return;

    if(x->prev) x->prev->next=x->next;
    else *h=x->next;

    if(x->next) x->next->prev=x->prev;

    free(x);
}

int dMin(DNode *h) {
    int m=h->key;
    for(h=h->next;h;h=h->next)
        if(h->key<m) m=h->key;
    return m;
}

int dMax(DNode *h) {
    int m=h->key;
    for(h=h->next;h;h=h->next)
        if(h->key>m) m=h->key;
    return m;
}

int ddMin(DNode *h) { return h->key; }

int ddMax(DNode *h) {
    while(h->next) h=h->next;
    return h->key;
}

int dPred(DNode *h,int k) {
    int p=-1;
    while(h) {
        if(h->key<k && (p==-1||h->key>p)) p=h->key;
        h=h->next;
    }
    return p;
}

int dSucc(DNode *h,int k) {
    int s=-1;
    while(h) {
        if(h->key>k && (s==-1||h->key<s)) s=h->key;
        h=h->next;
    }
    return s;
}

int ddPred(DNode *h,int k) {
    int p=-1;
    while(h && h->key<k) {
        p=h->key;
        h=h->next;
    }
    return p;
}

int ddSucc(DNode *h,int k) {
    while(h && h->key<=k) h=h->next;
    return h?h->key:-1;
}

// FREE FUNCTIONS

void freeS(SNode *h) {
    while(h) {
        SNode *p=h;
        h=h->next;
        free(p);
    }
}

void freeD(DNode *h) {
    while(h) {
        DNode *p=h;
        h=h->next;
        free(p);
    }
}

// BENCHMARK

#define TIME(F) ({                                      \
    clock_t _s=clock();                                 \
    for(int _i=0;_i<REP;_i++) F;                        \
    (double)(clock()-_s)/CLOCKS_PER_SEC;                \
})

void benchmark(int n,FILE *fs,FILE *fi,FILE *fd,
               FILE *fmax,FILE *fmin,FILE *fp,FILE *fq)
{
    UA ua; SA sa;
    SNode *us=sBuild(n,0), *ss=sBuild(n,1);
    DNode *ud=dBuild(n,0), *sd=dBuild(n,1);

    uaInit(&ua,n);
    saInit(&sa,n);

    int absent=-1;
    int big=n*2+1;

    double a,b,c,d,e,f;

    // SEARCH

    a=TIME(uaSearch(&ua,absent));
    b=TIME(saSearch(&sa,absent));
    c=TIME(sSearch(us,absent));
    d=TIME(sSearch(ss,absent));
    e=TIME(dSearch(ud,absent));
    f=TIME(dSearch(sd,absent));

    fprintf(fs,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // MAXIMUM

    a=TIME(uaMax(&ua));
    b=TIME(saMax(&sa));
    c=TIME(sMax(us));
    d=TIME(ssMax(ss));
    e=TIME(dMax(ud));
    f=TIME(ddMax(sd));

    fprintf(fmax,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // MINIMUM

    a=TIME(uaMin(&ua));
    b=TIME(saMin(&sa));
    c=TIME(sMin(us));
    d=TIME(ssMin(ss));
    e=TIME(dMin(ud));
    f=TIME(ddMin(sd));

    fprintf(fmin,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // PREDECESSOR

    a=TIME(uaPred(&ua,big));
    b=TIME(saPred(&sa,big));
    c=TIME(sPred(us,big));
    d=TIME(ssPred(ss,big));
    e=TIME(dPred(ud,big));
    f=TIME(ddPred(sd,big));

    fprintf(fp,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // SUCCESSOR

    a=TIME(uaSucc(&ua,absent));
    b=TIME(saSucc(&sa,absent));
    c=TIME(sSucc(us,absent));
    d=TIME(ssSucc(ss,absent));
    e=TIME(dSucc(ud,absent));
    f=TIME(ddSucc(sd,absent));

    fprintf(fq,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // INSERT

    int key=-1000000000;

    // Each insertion is timed independently. 
    //The structure is restored after timing.

    a=TIME(uaInsert(&ua,key));
    ua.n-=REP;

    b=TIME(saInsert(&sa,key));
    saInit(&sa,n);

    c=TIME(sInsertUnsorted(&us,key));
    for(int i=0;i<REP;i++) {
        SNode *x=sSearch(us,key);
        sDelete(&us,x);
    }

    d=TIME(sInsertSorted(&ss,key));
    for(int i=0;i<REP;i++) {
        SNode *x=sSearch(ss,key);
        sDelete(&ss,x);
    }

    e=TIME(dInsertUnsorted(&ud,key));
    for(int i=0;i<REP;i++) {
        DNode *x=dSearch(ud,key);
        dDelete(&ud,x);
    }

    f=TIME(dInsertSorted(&sd,key));
    for(int i=0;i<REP;i++) {
        DNode *x=dSearch(sd,key);
        dDelete(&sd,x);
    }

    fprintf(fi,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    // DELETE

    // Delete(D,x) receives the actual pointer x. 
    //Search is performed BEFORE timing.

    SNode *sx;
    DNode *dx;

    /* Array deletion */

    uaInsert(&ua,key);
    int up=ua.n-1;

    clock_t t=clock();
    for(int i=0;i<REP;i++) {
        uaDelete(&ua,up);
        uaInsert(&ua,key);
    }
    a=(double)(clock()-t)/CLOCKS_PER_SEC;

    ua.n--;

    saInsert(&sa,key);
    int sp=0;

    t=clock();
    for(int i=0;i<REP;i++) {
        saDelete(&sa,sp);
        saInsert(&sa,key);
    }
    b=(double)(clock()-t)/CLOCKS_PER_SEC;

    sa.n--;

    /* SLL deletion */

    sx=sInsertUnsorted(&us,key);

    t=clock();
    for(int i=0;i<REP;i++) {
        sDelete(&us,sx);
        sx=sInsertUnsorted(&us,key);
    }
    c=(double)(clock()-t)/CLOCKS_PER_SEC;

    sDelete(&us,sx);

    sx=sInsertSorted(&ss,key);

    t=clock();
    for(int i=0;i<REP;i++) {
        sDelete(&ss,sx);
        sx=sInsertSorted(&ss,key);
    }
    d=(double)(clock()-t)/CLOCKS_PER_SEC;

    sDelete(&ss,sx);

    /* DLL deletion */

    dx=dInsertUnsorted(&ud,key);

    t=clock();
    for(int i=0;i<REP;i++) {
        dDelete(&ud,dx);
        dx=dInsertUnsorted(&ud,key);
    }
    e=(double)(clock()-t)/CLOCKS_PER_SEC;

    dDelete(&ud,dx);

    dx=dInsertSorted(&sd,key);

    t=clock();
    for(int i=0;i<REP;i++) {
        dDelete(&sd,dx);
        dx=dInsertSorted(&sd,key);
    }
    f=(double)(clock()-t)/CLOCKS_PER_SEC;

    dDelete(&sd,dx);

    fprintf(fd,"%d,%g,%g,%g,%g,%g,%g\n",n,a,b,c,d,e,f);

    free(ua.a);
    free(sa.a);
    freeS(us);
    freeS(ss);
    freeD(ud);
    freeD(sd);
}

// MAIN

int main()
{
    srand(time(NULL));

    FILE *fs=fopen("search.csv","w");
    FILE *fi=fopen("insert.csv","w");
    FILE *fd=fopen("delete.csv","w");
    FILE *fmax=fopen("maximum.csv","w");
    FILE *fmin=fopen("minimum.csv","w");
    FILE *fp=fopen("predecessor.csv","w");
    FILE *fq=fopen("successor.csv","w");

    if(!fs||!fi||!fd||!fmax||!fmin||!fp||!fq) {
        printf("File error!\n");
        return 1;
    }

    char *head=
        "Size,UnsortedArray,SortedArray,"
        "UnsortedSLL,SortedSLL,UnsortedDLL,SortedDLL\n";

    fputs(head,fs);
    fputs(head,fi);
    fputs(head,fd);
    fputs(head,fmax);
    fputs(head,fmin);
    fputs(head,fp);
    fputs(head,fq);

    for(int n=START;n<=END;n+=STEP) {
        printf("n = %d done\n",n);

        benchmark(n,fs,fi,fd,fmax,fmin,fp,fq);
    }

    fclose(fs); fclose(fi); fclose(fd);
    fclose(fmax); fclose(fmin);
    fclose(fp); fclose(fq);


    // GNUPLOT SCRIPT

    FILE *g = fopen("plot.gp", "w");

    fprintf(g, "set datafile separator ','\n");
    fprintf(g, "set grid\n");
    fprintf(g, "set xlabel 'Input Size (n)'\n");
    fprintf(g, "set ylabel 'Execution Time (seconds)'\n");

    char *files[] = {
         "search.csv",
        "insert.csv",
        "delete.csv",
        "maximum.csv",
        "minimum.csv",
        "predecessor.csv",
        "successor.csv"
    };

    char *titles[] = {
        "Search",
        "Insert",
        "Delete",
        "Maximum",
        "Minimum",
        "Predecessor",
        "Successor"
    };

    char *outputs[] = {
        "search.png",
        "insert.png",
        "delete.png",
        "maximum.png",
        "minimum.png",
        "predecessor.png",
        "successor.png"
    };

    for(int j = 0; j < 7; j++)
    {
        fprintf(g, "set terminal pngcairo size 1000,700\n");

        fprintf(g, "set output '%s'\n", outputs[j]);
        
        fprintf(g, "set title 'Dictionary - %s Operation'\n",
            titles[j]);

        fprintf(g,
            "plot '%s' using 1:2 with linespoints "
            "title 'Unsorted Array',"
            "'%s' using 1:3 with linespoints "
            "title 'Sorted Array',"
            "'%s' using 1:4 with linespoints "
            "title 'Unsorted SLL',"
            "'%s' using 1:5 with linespoints "
            "title 'Sorted SLL',"
            "'%s' using 1:6 with linespoints "
            "title 'Unsorted DLL',"
            "'%s' using 1:7 with linespoints "
            "title 'Sorted DLL'\n",
            files[j], files[j], files[j],
            files[j], files[j], files[j]);

        fprintf(g, "set output\n");
    }

    fclose(g);

    printf("\nGenerating all graphs...\n");

    system("gnuplot plot.gp");

    printf("\nAll 7 graphs generated successfully!\n");

    return 0;
}