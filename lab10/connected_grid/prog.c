
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *parent, *size;
unsigned char *land;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (size[a] < size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];

    return 1;
}

int main(void) {
    int R, C, k;

    if (scanf("%d %d %d", &R, &C, &k) != 3)
        return 1;

    if (R <= 0 || C <= 0 || k < 0 || R > INT_MAX / C) {
        printf("Invalid dimensions or operation count.\n");
        return 1;
    }

    int N = R * C;

    parent = malloc((size_t)N * sizeof(int));
    size = malloc((size_t)N * sizeof(int));
    land = calloc((size_t)N, sizeof(unsigned char));

    if (parent == NULL || size == NULL || land == NULL) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(size);
        free(land);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int islands = 0;

    for (int i = 0; i < k; i++) {
        int r, c;

        if (scanf("%d %d", &r, &c) != 2 ||
            r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid coordinate.\n");
            free(parent);
            free(size);
            free(land);
            return 1;
        }

        int id = r * C + c;

        if (land[id]) {
            if (i > 0)
                printf(" ");
            printf("%d", islands);
            continue;
        }

        land[id] = 1;
        islands++;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;

            int nid = nr * C + nc;

            if (land[nid] && unite(id, nid))
                islands--;
        }

        if (i > 0)
            printf(" ");
        printf("%d", islands);
    }

    printf("\n");

    free(parent);
    free(size);
    free(land);

    return 0;
}
