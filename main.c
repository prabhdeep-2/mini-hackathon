#include <stdio.h>
#include <time.h>
#include "canteen.h"

int main(void) {
    MenuItem menu[MAX_ITEMS];
    int menu_count = load_menu(MENU_FILE, menu, MAX_ITEMS);
    if (menu_count == 0) {
        create_default_menu(menu, &menu_count);
        save_menu(MENU_FILE, menu, menu_count);
    }

    double total_sales = 0.0;
    int order_count = 0;
    load_sales_summary(SALES_FILE, &total_sales, &order_count);
    show_title();

    while (1) {
        printf("\n1. Show menu\n2. Create new bill\n3. Show sales summary\n4. Exit\n");
        int choice = read_int("Enter your choice: ", 1, 4);
        if (choice == 1) {
            show_menu(menu, menu_count);
        } else if (choice == 2) {
            Order order = {0};
            order.order_id = order_count + 1;
            order.created_at = time(NULL);
            order.customer = (CustomerType)read_int(
                "Customer type (1-Regular, 2-Student): ", 1, 2);
            show_menu(menu, menu_count);

            while (add_item_to_order(menu, menu_count, &order)) {
                int more = read_int("Add another item? (1-Yes, 2-No): ", 1, 2);
                if (more == 2) break;
            }

            if (order.item_count == 0) {
                printf("No items were added. Bill cancelled.\n");
                continue;
            }

            calculate_total(&order);
            order.payment = (PaymentType)read_int(
                "Payment method (1-Cash, 2-UPI, 3-Card): ", 1, 3);

            for (int i = 0; i < order.item_count; i++) {
                int index = find_item(menu, menu_count, order.items[i].item_id);
                menu[index].stock -= order.items[i].quantity;
                menu[index].sold += order.items[i].quantity;
            }

            append_sale(SALES_FILE, &order);
            save_menu(MENU_FILE, menu, menu_count);
            total_sales += order.total;
            order_count++;
            print_receipt(&order);
        } else if (choice == 3) {
            show_sales_summary(menu, menu_count, total_sales, order_count);
        } else {
            printf("\nThank you for using Smart Canteen Billing System.\n");
            break;
        }
    }
    return 0;
}
