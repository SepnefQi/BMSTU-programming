#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    ASSIGN,
    AT,
    END
} Optype;

typedef struct HashItem {
    int64_t key;
    int64_t value;
    struct HashItem* next;
} HashItem;

typedef struct HashTable {
    size_t capacity;
    size_t size;
    HashItem** table;
} HashTable;

uint64_t hash(int64_t i, size_t m) {
    return i % m;
}

HashTable* create(size_t capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->table = (HashItem**)calloc(capacity, sizeof(HashItem*));
    return ht;
}

HashItem* findItem(HashTable* ht, int64_t key) {
    uint64_t index = hash(key, ht->capacity);
    HashItem* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void InOrUp(HashTable* ht, int64_t key, int64_t value) {
    uint64_t index = hash(key, ht->capacity);
    HashItem* item = findItem(ht, key);
    if (item != NULL) {
        item->value = value;
    } else {
        HashItem* newItem = (HashItem*)malloc(sizeof(HashItem));
        newItem->key = key;
        newItem->value = value;
        newItem->next = ht->table[index];
        ht->table[index] = newItem;
        ht->size++;
    }
}


void del(HashTable* ht, int64_t key) {
    uint64_t index = hash(key, ht->capacity);
    HashItem* current = ht->table[index];
    HashItem* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int64_t getElement(HashTable* ht, int64_t key) {
    HashItem* item = findItem(ht, key);
    return item != NULL ? item->value : 0;
}


void freeHash(HashTable* ht) {
    if(ht == NULL) return;
    for (size_t i = 0; i < ht->capacity; i++) {
        HashItem* current = ht->table[i];
        while (current != NULL) {
            HashItem* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

//т.к. строковый тип не имеет однозначного преобразования в целочисленный
Optype parseCommand(const char* command) {
    if (strncmp(command, "ASSIGN", 6) == 0) return ASSIGN;
    if (strncmp(command, "AT", 2) == 0) return AT;
    return END;
}


int main() {
    int m;
    scanf("%d", &m);

    HashTable* ht = create(m);

    char command[10];
    int64_t i, v;
    
    while (scanf("%s", command)==1) {
        switch (parseCommand(command)) {
           case ASSIGN:
                scanf("%lld %lld", &i, &v);
                if (v == 0) del(ht, i);
                else InOrUp(ht, i, v);
                break;
           case AT:
                scanf("%lld", &i);
                printf("%lld\n", getElement(ht, i));
                break;
           case END:
                break;
        }
    }
    freeHash(ht);
    return 0;
}