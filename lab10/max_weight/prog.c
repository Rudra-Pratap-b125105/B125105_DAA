
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int parent[MAX], size[MAX], version[MAX];
long long sum[MAX];

typedef struct {
    long long weight;
    int root;
    int version;
} Entry;

typedef struct {
    Entry *data;
    int count;
    int capacity;
} MaxHeap;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void push(MaxHeap *h, Entry e) {
    int i = h->count++;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (h->data[p].weight >= e.weight)
            break;

        h->data[i] = h->data[p];
        i = p;
    }

    h->data[i] = e;
}

Entry pop(MaxHeap *h) {
    Entry result = h->data[0];
    Entry last = h->data[--h->count];
    int i = 0;

    while (2 * i + 1 < h->count) {
        int child = 2 * i + 1;

        if (child + 1 < h->count &&
            h->data[child + 1].weight > h->data[child].weight)
            child++;

        if (last.weight >= h->data[child].weight)
            break;

        h->data[i] = h->data[child];
        i = child;
    }

    if (h->count > 0)
        h->data[i] = last;

    return result;
}

void addCandidate(MaxHeap *h, int root, int K) {
    if (size[root] <= K) {
        Entry e = {sum[root], root, version[root]};
        push(h, e);
    }
}

void unite(int u, int v, MaxHeap *h, int K) {
    int a = find(u);
    int b = find(v);

    if (a == b)
        return;

    if (size[a] < size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];
    sum[a] += sum[b];

    version[a]++;
    version[b]++;

    addCandidate(h, a, K);
}

int hasValidTop(MaxHeap *h, int K) {
    while (h->count > 0) {
        Entry e = h->data[0];

        if (parent[e.root] == e.root &&
            version[e.root] == e.version &&
            size[e.root] <= K)
            return 1;

        pop(h);
    }

    return 0;
}

int main(void) {
    int V, E, K;

    if (scanf("%d %d %d", &V, &E, &K) != 3)
        return 1;

    if (V <= 0 || V >= MAX || E < 0 || E >= MAX) {
        printf("Invalid input size.\n");
        return 1;
    }

    MaxHeap h;
    h.capacity = V + E + 5;
    h.count = 0;
    h.data = malloc((size_t)h.capacity * sizeof(Entry));

    if (h.data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 1; i <= V; i++) {
        if (scanf("%lld", &sum[i]) != 1) {
            free(h.data);
            return 1;
        }

        parent[i] = i;
        size[i] = 1;
        version[i] = 0;

        addCandidate(&h, i, K);
    }

    for (int i = 0; i < E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge.\n");
            free(h.data);
            return 1;
        }

        unite(u, v, &h, K);

        if (hasValidTop(&h, K))
            printf("%lld\n", h.data[0].weight);
        else
            printf("NONE\n");
    }

    free(h.data);
    return 0;
}
