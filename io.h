#ifndef IO_H
#define IO_H

#include "container.h"
#include <stdio.h> 

void generate_data(Container* container, size_t count);
void print_data(const Container* container, FILE* output); 
void read_data(Container* container, const char* filename);
void write_data(const Container* container, const char* filename);

#endif