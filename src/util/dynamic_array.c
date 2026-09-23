
#include "util/dynamic_array.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * initialises a new dynamic array with an anitial capacity
 */
DynamicArray* init_dynamic_array(size_t capacity) {
    DynamicArray* darr = malloc(sizeof(DynamicArray));
    darr->length = 0;
    darr->capacity = capacity;
    darr->data = malloc(sizeof(void*) * capacity);
    return darr;
}

/**
 * add an item to end of array, and reallocate if necessary
 */
void add(DynamicArray* darr, void* value) {
    if (darr->length == darr->capacity) {
        size_t new_capcity = darr->capacity * 2;
        void** old_data = darr->data;
        darr->data = malloc(sizeof(void*) * new_capcity);
        for (size_t i = 0; i < darr->capacity; i++) {
             darr->data[i] = old_data[i];
        }
        darr->capacity = new_capcity;
        free(old_data);
    }
    darr->data[darr->length] = value;
    darr->length++;
}

/**
 * assumes that members have been freed beforehand, otherwise memory leak
 */
void free_darr(DynamicArray* darr) {
    free(darr->data);
    free(darr);
}
