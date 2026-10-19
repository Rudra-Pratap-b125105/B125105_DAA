#include <stdio.h>

#define MAX 100005

int parent[MAX], size[MAX], parity[MAX];

int find(int x) {
    if (parent[x] != x) {
        int p = parent[x];
        parent[x] = find(p);
        parity[x] ^= parity[p];
    }
    return parent[x];
}

int addEdge(int u, int v) {
    int ru = find(u), pu = parity[u];
    int rv = find(v), pv = parity[v];

    if (ru == rv)
        return (pu ^ pv) == 1;

    if (size[ru] < size[rv]) {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;
    parity[rv] = pu ^ pv ^ 1;
    size[ru] += size[rv];

    return 1;
}

int main() {
    int V, E, u, v;

    scanf("%d %d", &V, &E);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        size[i] = 1;
        parity[i] = 0;
    }

    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);

        if (addEdge(u, v))
            printf("Edge (%d, %d): Accepted\n", u, v);
        else
            printf("Edge (%d, %d): Rejected - violates bipartiteness\n",
                   u, v);
    }

    return 0;
}