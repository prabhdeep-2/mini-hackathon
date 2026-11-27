#include <stdio.h>
#include <string.h>
#include "canteen.h"

int add_item_to_order(const MenuItem menu[], int menu_count, Order *order) {
    int item_id = read_int("Enter item ID (0 to finish): ", 0, 8);
    if (item_id == 0) return 0;

    int menu_index = find_item(menu, menu_count, item_id);
    if (menu_index == -1) {
        printf("Item not found.\n");
        return 1;
    }

    int quantity = read_int("Enter quantity: ", 1, 100);
    int existing = -1;
    for (int i = 0; i < order->item_count; i++) {
        if (order->items[i].item_id == item_id) existing = i;
    }

    int already = existing >= 0 ? order->items[existing].quantity : 0;
    if (already + quantity > menu[menu_index].stock) {
        printf("Not enough stock. Only %d item(s) available.\n",
               menu[menu_index].stock - already);
        return 1;
    }

    if (existing >= 0) {
        order->items[existing].quantity += quantity;
    } else if (order->item_count < MAX_ORDER_ITEMS) {
        OrderItem *line = &order->items[order->item_count++];
        line->item_id = item_id;
        snprintf(line->name, NAME_LEN, "%s", menu[menu_index].name);
        line->price = menu[menu_index].price;
        line->quantity = quantity;
    }

    printf("Item added to order successfully.\n");
    return 1;
}
