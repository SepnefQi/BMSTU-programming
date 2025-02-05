#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *buffer;
    int head;
    int tail;
    int size;
    int count;
} cirque;

void InitQueue(cirque *queue) {
    queue->buffer = (int *)malloc(4 * sizeof(int));
    queue->size = 4;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
}

bool QueueEmpty(cirque *queue) {
    return queue->count == 0;
}

void resize(cirque *queue) {
    int newSize = queue->size * 2;
    int *newBuffer = (int *)malloc(newSize * sizeof(int));

    for (int i = 0; i < queue->count; i++) {
        newBuffer[i] = queue->buffer[(queue->head + i) % queue->size];
    }

    free(queue->buffer);
    queue->buffer = newBuffer;
    queue->head = 0;
    queue->tail = queue->count;
    queue->size = newSize;
}

void Enqueue(cirque *queue, int value) {
    if (queue->count == queue->size) {
        resize(queue);
    }
    queue->buffer[queue->tail] = value;
    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;
}

int Dequeue(cirque *queue) {
    if (QueueEmpty(queue)) {
        return -1;
    }
    int value = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->count--;
    return value;
}

void FreeQueue(cirque *queue) {
    free(queue->buffer);
}

int main() {
    cirque queue;
    InitQueue(&queue);

    char command[10];
    
    scanf("%s", command);
    while ((strcmp(command, "END"))) {
        if (strcmp(command, "ENQ") == 0) {
            int value;
            scanf("%d", &value);
            Enqueue(&queue, value);
        } else if (strcmp(command, "DEQ") == 0) printf("%d\n", Dequeue(&queue));
        else if (strcmp(command, "EMPTY") == 0) {
            printf("%s\n", QueueEmpty(&queue) ? "true" : "false");
        }
        scanf("%s", command);
    }
    
    FreeQueue(&queue);
    return 0;
}