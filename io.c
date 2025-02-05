#include "io.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char* developers[] = {"Skyline Corp", "Urban Builders", "Nova Construction", "EcoHomes", "Metro Development"};
const char* neighborhoods[] = {"Downtown", "Riverside", "Sunset Valley", "Greenfield", "Hilltop"};

void generate_data(Container* container, size_t count) {
    srand(time(NULL));
    for (size_t i = 0; i < count; i++) {
        Building building = {
            .type = rand() % 3,
            .year = 1980 + rand() % 41,
            .has_elevator = rand() % 2,
            .has_trash_chute = rand() % 2,
            .apartments_count = 10 + rand() % 90,
            .floors_count = 1 + rand() % 20,
            .avg_apartment_area = (rand() % 1000) / 10.0
        };
        strncpy(building.developer, developers[rand() % 5], sizeof(building.developer));
        strncpy(building.neighborhood, neighborhoods[rand() % 5], sizeof(building.neighborhood));
        container_add(container, &building);
    }
}

void print_data(const Container* container, FILE* output) {
    fprintf(output, "Developer,Neighborhood,Type,Year,Elevator,TrashChute,Apartments,Floors,AvgArea\n");
    for (size_t i = 0; i < container->size; i++) {
        Building* b = container_get(container, i);
        fprintf(output, "%s,%s,%d,%d,%s,%s,%d,%d,%.2f\n",
                b->developer, b->neighborhood, b->type, b->year,
                b->has_elevator ? "YES" : "NO",
                b->has_trash_chute ? "YES" : "NO",
                b->apartments_count, b->floors_count, b->avg_apartment_area);
    }
}

void read_data(Container* container, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    fgets(buffer, sizeof(buffer), file); // Пропуск заголовка
    while (fgets(buffer, sizeof(buffer), file)) {
        Building building;
        if (sscanf(buffer, "%99[^,],%99[^,],%d,%d,%d,%d,%d,%d,%lf",
                   building.developer, building.neighborhood,
                   (int*)&building.type, &building.year,
                   &building.has_elevator, &building.has_trash_chute,
                   &building.apartments_count, &building.floors_count,
                   &building.avg_apartment_area) == 9) {
            container_add(container, &building);
        } else {
            fprintf(stderr, "Warning: Invalid data format in line: %s", buffer);
        }
    }
    fclose(file);
}

void write_data(const Container* container, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    print_data(container, file);
    fclose(file);
}

