#include <stdio.h>
#include "canteen.h"

void show_title(void) {
    printf("\n===============================================\n");
    printf("          SMART CANTEEN BILLING SYSTEM\n");
    printf("===============================================\n");
}

int read_int(const char *prompt, int min, int max) {
    char buffer[64];
    int value;

    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof buffer, stdin)) return min;
        if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max)
            return value;
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

void show_menu(const MenuItem menu[], int count) {
    printf("\n---------------- CANTEEN MENU ----------------\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "ITEM", "PRICE", "STOCK");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s Rs.%-7.2f %-10d\n",
               menu[i].id, menu[i].name, menu[i].price, menu[i].stock);
    }
}
