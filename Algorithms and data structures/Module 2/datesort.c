#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100000

struct Date {
    int Day;
    int Month;
    int Year;
};

void radixSort(struct Date *dates, int n) {
    struct Date *buffer = malloc(n * sizeof(struct Date));

    // Сортировка по дням
    int dayCount[MAX_NUM] = {0};
    for (int i = 0; i < n; i++) {
        dayCount[dates[i].Day]++;
    }
    for (int i = 1; i < MAX_NUM; i++) {
        dayCount[i] += dayCount[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        buffer[--dayCount[dates[i].Day]] = dates[i];
    }
    for (int i = 0; i < n; i++) {
        dates[i] = buffer[i];
    }

     // Сортировка по месяцам
    int monthCount[MAX_NUM] = {0};
    for (int i = 0; i < n; i++) {
        monthCount[dates[i].Month]++;
    }
    for (int i = 1; i < MAX_NUM; i++) {
        monthCount[i] += monthCount[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        buffer[--monthCount[dates[i].Month]] = dates[i];
    }
    for(int i = 0; i < n; i++) {
        dates[i] = buffer[i];
    }

    // Сортировка по годам
    int yearCount[MAX_NUM] = {0};
    for (int i = 0; i < n; i++) {
        yearCount[dates[i].Year]++;
    }
    for (int i = 1; i < MAX_NUM; i++) {
        yearCount[i] += yearCount[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        buffer[--yearCount[dates[i].Year]] = dates[i];
    }
     for(int i = 0; i < n; i++) {
        dates[i] = buffer[i];
    }

    free(buffer);
}

int main() {
    int n;
    scanf("%d", &n);

    struct Date *dates = malloc(n * sizeof(struct Date));
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }

    radixSort(dates, n);

    for (int i = 0; i < n; i++) {
        printf("%04d %02d %02d\n", dates[i].Year, dates[i].Month, dates[i].Day);
    }

    free(dates);
    return 0;
}