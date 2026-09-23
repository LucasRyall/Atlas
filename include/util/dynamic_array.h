#ifndef DYNAMICARRAY
#define DYNAMICARRAY

#include <stddef.h>


typedef struct DynamicArray {
    size_t length;
    size_t capacity;
    void** data;
} DynamicArray;

#endif
