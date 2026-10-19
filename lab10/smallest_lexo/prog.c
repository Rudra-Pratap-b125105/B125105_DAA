#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int parent[MAX], size[MAX], A[MAX];

typedef struct {
    int root;
    int index;
} Position;

typedef struct {
    int root;
    int value;
} Value;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (size[a] < size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];
}

int comparePosition(const void *a, const void *b) {
    const Position *x = a;
    const Position *y = b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->index > y->index) - (x->index < y->index);
}

int compareValue(const void *a, const void *b) {
    const Value *x = a;
    const Value *y = b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->value > y->value) - (x->value < y->value);
}

int main() {
    int n, m;
    static Position positions[MAX];
    static Value values[MAX];

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    for (int i = 1; i <= n; i++) {
        int r = find(i);

        positions[i - 1].root = r;
        positions[i - 1].index = i;

        values[i - 1].root = r;
        values[i - 1].value = A[i];
    }

    qsort(positions, n, sizeof(Position), comparePosition);
    qsort(values, n, sizeof(Value), compareValue);

    for (int i = 0; i < n; i++)
        A[positions[i].index] = values[i].value;

    for (int i = 1; i <= n; i++) {
        if (i > 1)
            printf(" ");

        printf("%d", A[i]);
    }

    printf("\n");
    return 0;
}