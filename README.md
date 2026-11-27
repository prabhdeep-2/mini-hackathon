# Smart Canteen Billing System

This is the working C model based on the Smart Canteen Billing Team Guide.

## Features

- Display canteen menu
- Create an order with multiple items
- Check available stock
- Apply a 10% student discount
- Accept cash, UPI, or card payment
- Print a receipt
- Save menu and stock data in `data/menu.dat`
- Save completed sales in `data/sales.csv`
- Show total sales, average order value, and best-selling item

## Build and run

```bash
make
./canteen
```

On Windows, run:

```bash
gcc -Wall -Wextra -std=c11 -g -Iinclude -o canteen.exe src/*.c
canteen.exe
```

## Suggested class demonstration

1. Choose `1` to show the menu.
2. Choose `2` to create a bill.
3. Select `2` for a student customer.
4. Add Samosa with quantity `2`.
5. Choose `2` when asked whether to add another item.
6. Choose UPI using option `2`.
7. Show the receipt and the 10% discount.
8. Choose `3` to show the sales summary.
9. Close and reopen the program to demonstrate saved data.
