#include "sort.h"

void sort_bubble(Container* container, Comparator cmp) {
    if (container->size < 2) {
        return; 
    }

    for (size_t i = 0; i < container->size - 1; i++) {
        for (size_t j = 0; j < container->size - i - 1; j++) {
            Building* current = &container->data[j];
            Building* next = &container->data[j + 1];
            if (cmp(current, next) > 0) {
                Building temp = *current;
                *current = *next;
                *next = temp;
            }
        }
    }
}

int compare_year_asc(const void* a, const void* b) {
    Building* building_a = (Building*)a;
    Building* building_b = (Building*)b;
    return building_a->year - building_b->year;
}

int compare_year_desc(const void* a, const void* b) {
    Building* building_a = (Building*)a;
    Building* building_b = (Building*)b;
    return building_b->year - building_a->year;
}
