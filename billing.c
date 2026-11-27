#include <stdio.h>
#include "canteen.h"

double calculate_total(Order *order) {
    order->subtotal = 0.0;
    for (int i = 0; i < order->item_count; i++)
        order->subtotal += order->items[i].price * order->items[i].quantity;
    order->discount = order->customer == STUDENT ? order->subtotal * 0.10 : 0.0;
    order->total = order->subtotal - order->discount;
    return order->total;
}

void print_receipt(const Order *order) {
    const char *customer = order->customer == STUDENT ? "Student" : "Regular";
    const char *payment = order->payment == CASH ? "Cash" :
                          order->payment == UPI ? "UPI" : "Card";

    printf("\n=============== FINAL RECEIPT ===============\n");
    printf("Order ID      : %d\n", order->order_id);
    printf("Customer type : %s\n", customer);
    printf("Payment mode  : %s\n", payment);
    printf("-----------------------------------------------\n");
    printf("%-20s %-5s %-10s\n", "ITEM", "QTY", "AMOUNT");
    for (int i = 0; i < order->item_count; i++) {
        double amount = order->items[i].price * order->items[i].quantity;
        printf("%-20s %-5d Rs.%-7.2f\n", order->items[i].name,
               order->items[i].quantity, amount);
    }
    printf("-----------------------------------------------\n");
    printf("Subtotal       : Rs. %.2f\n", order->subtotal);
    printf("Discount       : Rs. %.2f\n", order->discount);
    printf("Final total    : Rs. %.2f\n", order->total);
    printf("===============================================\n");
}
