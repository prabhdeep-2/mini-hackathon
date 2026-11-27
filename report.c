#include <stdio.h>
#include "canteen.h"

void show_sales_summary(const MenuItem menu[], int menu_count,
                        double total_sales, int order_count) {
    int best = 0;
    for (int i = 1; i < menu_count; i++)
        if (menu[i].sold > menu[best].sold) best = i;

    printf("\n--------------- SALES SUMMARY ----------------\n");
    printf("Completed orders : %d\n", order_count);
    printf("Total sales      : Rs. %.2f\n", total_sales);
    if (order_count > 0) {
        printf("Average order    : Rs. %.2f\n", total_sales / order_count);
        printf("Best-selling item: %s (%d sold)\n",
               menu[best].name, menu[best].sold);
    } else {
        printf("No orders completed yet.\n");
    }
    printf("-----------------------------------------------\n");
}
