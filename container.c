#include "container.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void container_init(Container* container) {
    container->data = NULL;
    container->size = 0;
    container->capacity = 0;
}

void container_free(Container* container) {
    free(container->data);
    container->data = NULL;
    container->size = 0;
    container->capacity = 0;
}

size_t container_size(const Container* container) {
    return container->size;
}

Building* container_get(const Container* container, size_t index) {
    if (index < container->size) {
        return &container->data[index];
    }
    return NULL;
}

void container_add(Container* container, const Building* building) {
    if (container->size == container->capacity) {
        container->capacity = container->capacity == 0 ? 10 : container->capacity * 2;
        container->data = realloc(container->data, container->capacity * sizeof(Building));
        if (!container->data) {
            fprintf(stderr, "Error: Unable to allocate memory\n");
            exit(EXIT_FAILURE);
        }
    }
    container->data[container->size++] = *building;
}

void container_remove(Container* container, size_t index) {
    if (index < container->size) {
        memmove(&container->data[index], &container->data[index + 1],
                (container->size - index - 1) * sizeof(Building));
        container->size--;
    }
}

void container_clear(Container* container) {
    container->size = 0;
}

Building* container_begin(const Container* container) {
    if (container->size > 0) {
        return &container->data[0];
    }
    return NULL;
}

Building* container_end(const Container* container) {
    if (container->size > 0) {
        return &container->data[container->size];
    }
    return NULL;
}

Building* container_next(const Container* container, Building* current) {
    if (current >= container_begin(container) && current < container_end(container) - 1) {
        return current + 1;
    }
    return NULL;
}

Building* container_prev(const Container* container, Building* current) {
    if (current > container_begin(container) && current < container_end(container)) {
        return current - 1;
    }
    return NULL;
}

void container_from_array(Container* container, const Building* array, size_t size) {
    container_clear(container);
    for (size_t i = 0; i < size; i++) {
        container_add(container, &array[i]);
    }
}

void container_to_array(const Container* container, Building* array, size_t size) {
    if (size >= container->size) {
        memcpy(array, container->data, container->size * sizeof(Building));
    }
}
