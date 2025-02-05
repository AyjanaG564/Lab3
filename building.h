#ifndef BUILDING_H
#define BUILDING_H

typedef enum {
    PANEL,
    BRICK,
    MONOLITHIC
} BuildingType;

typedef struct {
    char developer[100];
    char neighborhood[100];
    BuildingType type;
    int year;
    int has_elevator;
    int has_trash_chute;
    int apartments_count;
    int floors_count;
    double avg_apartment_area;
} Building;

int compare_apartments_asc(const void* a, const void* b);
const char* get_building_type(BuildingType type);

#endif

