#ifndef CONTAINER_H
#define CONTAINER_H

#include "building.h"
#include <stddef.h>

typedef struct {
    Building* data;
    size_t size;  
    size_t capacity;
} Container;

void container_init(Container* container);
void container_free(Container* container);
size_t container_size(const Container* container);
Building* container_get(const Container* container, size_t index);
void container_add(Container* container, const Building* building);
void container_remove(Container* container, size_t index);
void container_clear(Container* container);

Building* container_begin(const Container* container);
Building* container_end(const Container* container);
Building* container_next(const Container* container, Building* current);
Building* container_prev(const Container* container, Building* current);

void container_from_array(Container* container, const Building* array, size_t size);
void container_to_array(const Container* container, Building* array, size_t size);

#endif 
