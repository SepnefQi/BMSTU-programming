#include <stdio.h>
#include <stdlib.h>

struct Task {
    int low, high;
};

void swap(int *a, int *b) {
    int moment = *a;
    *a = *b;
    *b = moment;
}

int partition(int a[], int low, int high) {
    int base = a[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (a[j] < base) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void push(struct Task **stack, int *top, int low, int high) {
    (*top)++;
    (*stack)[*top].low = low;
    (*stack)[*top].high = high;
}

// функция для извлечения элемента из стека
struct Task pop(struct Task *stack, int *top) {
    return stack[(*top)--];
}

void quickSort(int a[], int n) {
    int top = -1;
    struct Task* stack = malloc(n * sizeof(struct Task));

    push(&stack, &top, 0, n - 1);

    while (top >= 0) {
        struct Task task = pop(stack, &top);
        int low = task.low;
        int high = task.high;

        if (low == -1 && high == -1) break; // Стек пуст
        
        if (low < high) {
            int base = partition(a, low, high);
            push(&stack, &top, low, base - 1);
            push(&stack, &top, base + 1, high);
        }
    }
    free(stack);
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    quickSort(a, n);

    for (int i = 0; i < n; i++) printf("%d ", a[i]);

    free(a);

    return 0;
}
