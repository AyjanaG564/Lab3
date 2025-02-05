#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "building.h"
#include "container.h"
#include "sort.h"
#include "io.h"

#define ARG_GENERATE "--generate"
#define ARG_SORT "--sort"
#define ARG_PRINT "--print"
#define ARG_OUT "--out"
#define ARG_IN "--in"
#define ARG_TYPE "--type"

int parse_type_argument(const char* type_str);
Comparator get_comparator(int order);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [options]\n", argv[0]);
        return EXIT_FAILURE;
    }

    Container container;
    container_init(&container);

    const char* mode = argv[1];
    const char* input_file = NULL;
    const char* output_file = NULL;
    int sort_order = 1;

    for (int i = 2; i < argc; i++) {
        if (strncmp(argv[i], ARG_OUT, strlen(ARG_OUT)) == 0) {
            output_file = strchr(argv[i], '=') + 1;
        } else if (strncmp(argv[i], ARG_IN, strlen(ARG_IN)) == 0) {
            input_file = strchr(argv[i], '=') + 1;
        } else if (strncmp(argv[i], ARG_TYPE, strlen(ARG_TYPE)) == 0) {
            sort_order = parse_type_argument(strchr(argv[i], '=') + 1);
        }

    }

    if (strcmp(mode, ARG_GENERATE) == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s --generate N [--out=output.csv]\n", argv[0]);
            container_free(&container);
            return EXIT_FAILURE;
        }

        size_t count = strtoul(argv[2], NULL, 10);
        generate_data(&container, count);

        FILE* output = output_file ? fopen(output_file, "w") : stdout;
        if (!output) {
            fprintf(stderr, "Error: Unable to open output file '%s'\n", output_file);
            container_free(&container);
            return EXIT_FAILURE;
        }

        print_data(&container, output);
        if (output_file) fclose(output);
    } else if (strcmp(mode, ARG_SORT) == 0) {
        FILE* input = input_file ? fopen(input_file, "r") : stdin;
        if (!input) {
            fprintf(stderr, "Error: Unable to open input file '%s'\n", input_file);
            container_free(&container);
            return EXIT_FAILURE;
        }

        size_t count;
        fscanf(input, "%zu", &count);
        for (size_t i = 0; i < count; i++) {
            Building building;
            fscanf(input, "%99[^,],%99[^,],%d,%d,%d,%d,%d,%d,%lf",
                   building.developer, building.neighborhood,
                   (int*)&building.type, &building.year,
                   &building.has_elevator, &building.has_trash_chute,
                   &building.apartments_count, &building.floors_count,
                   &building.avg_apartment_area);
            container_add(&container, &building);
        }
        if (input_file) fclose(input);

        Comparator cmp = get_comparator(sort_order);
        sort_bubble(&container, cmp);

        FILE* output = output_file ? fopen(output_file, "w") : stdout;
        if (!output) {
            fprintf(stderr, "Error: Unable to open output file '%s'\n", output_file);
            container_free(&container);
            return EXIT_FAILURE;
        }

        print_data(&container, output);
        if (output_file) fclose(output);
    } else if (strcmp(mode, ARG_PRINT) == 0) {
        FILE* input = input_file ? fopen(input_file, "r") : stdin;
        if (!input) {
            fprintf(stderr, "Error: Unable to open input file '%s'\n", input_file);
            container_free(&container);
            return EXIT_FAILURE;
        }

        size_t count;
        fscanf(input, "%zu", &count);
        for (size_t i = 0; i < count; i++) {
            Building building;
            fscanf(input, "%99[^,],%99[^,],%d,%d,%d,%d,%d,%d,%lf",
                   building.developer, building.neighborhood,
                   (int*)&building.type, &building.year,
                   &building.has_elevator, &building.has_trash_chute,
                   &building.apartments_count, &building.floors_count,
                   &building.avg_apartment_area);
            container_add(&container, &building);
        }
        if (input_file) fclose(input);

        FILE* output = output_file ? fopen(output_file, "w") : stdout;
        if (!output) {
            fprintf(stderr, "Error: Unable to open output file '%s'\n", output_file);
            container_free(&container);
            return EXIT_FAILURE;
        }

        print_data(&container, output);
        if (output_file) fclose(output);
    } else {
        fprintf(stderr, "Unknown mode: %s\n", mode);
        container_free(&container);
        return EXIT_FAILURE;
    }

    container_free(&container);
    return EXIT_SUCCESS;
}

int parse_type_argument(const char* type_str) {
    if (strcmp(type_str, "asc") == 0) return 1;
    if (strcmp(type_str, "desc") == 0) return -1;
    return 1;
}

Comparator get_comparator(int order) {
    if (order > 0) {
        return compare_year_asc;
    } else {
        return compare_year_desc;
    }
}
