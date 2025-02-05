#ifndef MAIN_H
#define MAIN_H

#include "container.h"
#include "building.h"
#include "sort.h"
#include "io.h"

#define ARG_GENERATE "-g"
#define ARG_SORT "-s"
#define ARG_PRINT "-P"
#define ARG_OUT "-o"
#define ARG_IN "-i"
#define ARG_TYPE "-t"
#define ARG_GENERATE '-g'
#define ARG_SORT     '-s'
#define ARG_PRINT    '-P'
#define ARG_OUT      '-o'
#define ARG_IN       '-i'
#define ARG_TYPE     '-t'

int parse_type_argument(const char *type_str);
typedef int (*Comparator)(const void *, const void *);
Comparator get_comparator(int order);

#endif 
