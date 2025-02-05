#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_value(a, b) a>b ? a : b

typedef struct Node {
    struct Node *previous;
    long long value;
    long long maximum;
} Node;

typedef struct Queue {
    Node *inputStack;
    Node *outputStack;
} Queue;

Queue *CreateQueue() {
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->inputStack = NULL;
    newQueue->outputStack = NULL;
    return newQueue;
}

Node *Push(Node *stack, long long number) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->previous = stack;
    newNode->value = number;
    newNode->maximum = (stack == NULL) ? number : max_value(number, stack->maximum);
    return newNode;
}

Node *Pop(Node *stack) {
    Node *nextNode = stack->previous;
    free(stack);
    return nextNode;
}

void Enqueue(Queue *queue, long long number) {
    queue->inputStack = Push(queue->inputStack, number);
}

long long Dequeue(Queue *queue) {
    if (queue->outputStack == NULL) {
        while (queue->inputStack != NULL) {
            Node *step = queue->inputStack->previous;
            queue->inputStack->previous = queue->outputStack;

            if (queue->outputStack == NULL) {
                queue->inputStack->maximum = queue->inputStack->value;
            } else {
                queue->inputStack->maximum = max_value(queue->inputStack->value, queue->outputStack->maximum);
            }

            queue->outputStack = queue->inputStack;
            queue->inputStack = step;
        }
    }
    
    long long result = queue->outputStack->value;
    queue->outputStack = Pop(queue->outputStack);
    return result;
}

long long GetMaximum(Queue *queue) {
    if (queue->inputStack == NULL) {
        return queue->outputStack->maximum;
    }
    if (queue->outputStack == NULL) {
        return queue->inputStack->maximum;
    }
    return max_value(queue->inputStack->maximum, queue->outputStack->maximum);
}

int IsQueueEmpty(Queue *queue) {
    return (queue->inputStack == NULL && queue->outputStack == NULL);
}

int main(int argc, char **argv) {
    char command[7];
    Queue *queue = CreateQueue();
    
    scanf("%s", command);
    while (strcmp(command, "END") != 0) {
        if (strcmp(command, "ENQ") == 0) {
            long long value;
            scanf("%lld", &value);
            Enqueue(queue, value);
        } else if (strcmp(command, "DEQ") == 0) {
            printf("%lld\n", Dequeue(queue));
        } else if (strcmp(command, "MAX") == 0) {
            printf("%lld\n", GetMaximum(queue));
        } else {
            printf(IsQueueEmpty(queue) ? "true\n" : "false\n");
        }
        scanf("%s", command);
    }

    while (!IsQueueEmpty(queue)) {
        Dequeue(queue);
    }
    
    free(queue);
    return 0;
}