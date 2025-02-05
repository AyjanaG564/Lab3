#ifndef SORT_H
#define SORT_H

#include "container.h"

typedef int (*Comparator)(const void*, const void*);

void sort_bubble(Container* container, Comparator cmp);
int compare_year_asc(const void* a, const void* b);
int compare_year_desc(const void* a, const void* b);

#endif 
