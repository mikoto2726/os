#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BITS_PER_WORD (sizeof(unsigned int) * 8)

typedef struct {
    unsigned int *bits;
    unsigned int size;
} SET;

SET* set_create(unsigned int n) {
    SET* set = (SET*)malloc(sizeof(SET));
    if (set == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // ビット列のサイズを計算して割り当てる
    unsigned int array_size = n / BITS_PER_WORD + 1;
    set->bits = (unsigned int*)calloc(array_size, sizeof(unsigned int));
    if (set->bits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    set->size = n + 1; // 要素数を設定

    return set;
}

void set_destroy(SET* set) {
    free(set->bits);
    free(set);
}

int set_count(const SET* set) {
    int count = 0;
    unsigned int i, j;

    for (i = 0; i < set->size / BITS_PER_WORD; i++) {
        for (j = 0; j < BITS_PER_WORD; j++) {
            if (set->bits[i] & (1 << j)) {
                count++;
            }
        }
    }

    return count;
}

void set_append(SET* set, unsigned int value) {
    if (value >= set->size) {
        fprintf(stderr, "Value out of range\n");
        return;
    }

    set->bits[value / BITS_PER_WORD] |= (1 << (value % BITS_PER_WORD));
}

void set_remove(SET* set, unsigned int value) {
    if (value >= set->size) {
        fprintf(stderr, "Value out of range\n");
        return;
    }

    set->bits[value / BITS_PER_WORD] &= ~(1 << (value % BITS_PER_WORD));
}

bool set_contains(const SET* set, unsigned int value) {
    if (value >= set->size) {
        return false;
    }

    return set->bits[value / BITS_PER_WORD] & (1 << (value % BITS_PER_WORD));
}

void set_print(const SET* set) {
    unsigned int i, j;

    printf("{");
    for (i = 0; i < set->size; i++) {
        if (set_contains(set, i)) {
            printf("%u, ", i);
        }
    }
    printf("\b\b}\n"); // 最後のカンマを削除して表示
}

int main() {
    SET* set = set_create(10);

    set_append(set, 2);
    set_append(set, 5);
    set_append(set, 8);

    printf("Set count: %d\n", set_count(set));
    printf("Set contains 5: %s\n", set_contains(set, 5) ? "true" : "false");

    printf("Set: ");
    set_print(set);

    set_destroy(set);

    return 0;
}
