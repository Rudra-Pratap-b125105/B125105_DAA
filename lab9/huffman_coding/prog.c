#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *data[MAX];
    int size;
} MinHeap;

typedef struct {
    char symbol;
    int freq;
    int length;
    unsigned long long code;
} SymbolInfo;

Node *createNode(char symbol, int freq) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->symbol = symbol;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void swap(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->data[parent]->freq <= heap->data[index]->freq)
            break;

        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

void heapifyDown(MinHeap *heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->size &&
            heap->data[left]->freq < heap->data[smallest]->freq)
            smallest = left;

        if (right < heap->size &&
            heap->data[right]->freq < heap->data[smallest]->freq)
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

void insert(MinHeap *heap, Node *node) {
    heap->data[heap->size] = node;
    heap->size++;

    heapifyUp(heap, heap->size - 1);
}

Node *extractMin(MinHeap *heap) {
    Node *result = heap->data[0];

    heap->size--;
    heap->data[0] = heap->data[heap->size];

    if (heap->size > 0)
        heapifyDown(heap, 0);

    return result;
}

void findLengths(Node *root, int depth, SymbolInfo info[], int *count) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        info[*count].symbol = root->symbol;
        info[*count].freq = root->freq;
        info[*count].length = depth;
        (*count)++;
        return;
    }

    findLengths(root->left, depth + 1, info, count);
    findLengths(root->right, depth + 1, info, count);
}

int compareSymbols(const void *a, const void *b) {
    SymbolInfo *x = (SymbolInfo *)a;
    SymbolInfo *y = (SymbolInfo *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol - (unsigned char)y->symbol;
}

void printCode(unsigned long long code, int length) {
    for (int i = length - 1; i >= 0; i--)
        printf("%llu", (code >> i) & 1ULL);
}

int main() {
    int n;
    MinHeap heap = { .size = 0 };

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    SymbolInfo info[MAX];

    printf("Enter symbol and frequency:\n");

    for (int i = 0; i < n; i++) {
        char symbol;
        int freq;

        scanf(" %c %d", &symbol, &freq);

        Node *node = createNode(symbol, freq);
        insert(&heap, node);
    }

    while (heap.size > 1) {
        Node *left = extractMin(&heap);
        Node *right = extractMin(&heap);

        Node *parent = createNode('\0',
                                  left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        insert(&heap, parent);
    }

    Node *root = extractMin(&heap);

    int count = 0;
    findLengths(root, 0, info, &count);

    qsort(info, count, sizeof(SymbolInfo), compareSymbols);

    unsigned long long code = 0;
    int previousLength = info[0].length;

    info[0].code = 0;

    for (int i = 1; i < count; i++) {
        code = info[i - 1].code + 1;

        if (info[i].length > previousLength)
            code <<= (info[i].length - previousLength);

        info[i].code = code;
        previousLength = info[i].length;
    }

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < count; i++) {
        printf("%c\t%d\t\t%d\t",
               info[i].symbol,
               info[i].freq,
               info[i].length);

        printCode(info[i].code, info[i].length);
        printf("\n");
    }

    return 0;
}
