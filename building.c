#include "building.h"
#include <string.h>

int compare_apartments_asc(const void* a, const void* b) {
    const Building* b1 = (const Building*)a;
    const Building* b2 = (const Building*)b;
    return b1->apartments_count - b2->apartments_count;
}

const char* get_building_type(BuildingType type) {
    switch (type) {
        case PANEL: return "Panel";
        case BRICK: return "Brick";
        case MONOLITHIC: return "Monolithic";
        default: return "Unknown";
    }
}

