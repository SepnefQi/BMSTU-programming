#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int end;
} Node;

typedef struct {
    Node *nodes;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = malloc(capacity * sizeof(Node));
    return heap;
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int i) {
    int mini=i, l=2*i+1, r=2*i+2;

    if (l < heap->size && heap->nodes[l].end < heap->nodes[mini].end) mini = l;
    if (r < heap->size && heap->nodes[r].end < heap->nodes[mini].end) mini = r;
    if (mini != i) {
        swap(&heap->nodes[i], &heap->nodes[mini]);
        minHeapify(heap, mini);
    }
}

Node extractMin(MinHeap *heap) {
    if (heap->size == 0) {
        Node emptyNode = {0};
        return emptyNode;
    }
    
    Node root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    
    return root;
}

void insertMinHeap(MinHeap *heap, Node node) {
    if (heap->size == heap->capacity) {
        return;
    }
    
    heap->nodes[heap->size] = node;
    int nowi = heap->size;
    heap->size++;
    
    while (nowi != 0 && heap->nodes[nowi].end < heap->nodes[(nowi - 1) / 2].end) {
        swap(&heap->nodes[nowi], &heap->nodes[(nowi - 1) / 2]);
        nowi = (nowi - 1) / 2;
    }
}

int main() {
    int n, m, nowtime=0, t1, t2;
    scanf("%d", &n);
    scanf("%d", &m);

    MinHeap *heap = createMinHeap(n);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &t1, &t2);
        nowtime = t1;

        while (heap->size > 0 && heap->nodes[0].end <= nowtime) extractMin(heap);

        if (heap->size < n) {
            insertMinHeap(heap, (Node){nowtime + t2});
        } else {
            Node finishedNode = extractMin(heap);
            insertMinHeap(heap, (Node){finishedNode.end + t2});
        }
    }

    while (heap->size > 0) {
        Node finishedNode = extractMin(heap);
        nowtime = finishedNode.end;
    }

    printf("%d", nowtime);
    free(heap->nodes);
    free(heap);
    return 0;
}