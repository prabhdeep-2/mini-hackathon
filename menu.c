#include "canteen.h"

int find_item(const MenuItem menu[], int count, int item_id) {
    for (int i = 0; i < count; i++) {
        if (menu[i].id == item_id) return i;
    }
    return -1;
}

void create_default_menu(MenuItem menu[], int *count) {
    MenuItem defaults[MAX_ITEMS] = {
        {1, "Samosa", 15.00, 20, 0},
        {2, "Aloo Paratha", 40.00, 15, 0},
        {3, "Veg Sandwich", 50.00, 12, 0},
        {4, "Masala Dosa", 70.00, 10, 0},
        {5, "Chole Bhature", 80.00, 10, 0},
        {6, "Tea", 10.00, 30, 0},
        {7, "Cold Drink", 30.00, 20, 0},
        {8, "Fresh Juice", 45.00, 15, 0}
    };
    for (int i = 0; i < MAX_ITEMS; i++) menu[i] = defaults[i];
    *count = MAX_ITEMS;
}
