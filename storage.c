#include <stdio.h>
#include <sys/stat.h>
#include "canteen.h"

static void ensure_data_directory(void) {
#ifdef _WIN32
    _mkdir(DATA_DIR);
#else
    mkdir(DATA_DIR, 0777);
#endif
}

int save_menu(const char *path, const MenuItem menu[], int count) {
    ensure_data_directory();
    FILE *file = fopen(path, "wb");
    if (!file) return 0;
    int ok = fwrite(&count, sizeof count, 1, file) == 1 &&
             fwrite(menu, sizeof(MenuItem), count, file) == (size_t)count;
    fclose(file);
    return ok;
}

int load_menu(const char *path, MenuItem menu[], int max_count) {
    FILE *file = fopen(path, "rb");
    if (!file) return 0;
    int count = 0;
    if (fread(&count, sizeof count, 1, file) != 1 || count < 1 || count > max_count) {
        fclose(file);
        return 0;
    }
    if (fread(menu, sizeof(MenuItem), count, file) != (size_t)count) count = 0;
    fclose(file);
    return count;
}

int append_sale(const char *path, const Order *order) {
    ensure_data_directory();
    FILE *file = fopen(path, "a");
    if (!file) return 0;
    fprintf(file, "%d,%ld,%.2f,%.2f,%.2f\n", order->order_id,
            (long)order->created_at, order->subtotal, order->discount, order->total);
    fclose(file);
    return 1;
}

int load_sales_summary(const char *path, double *total_sales, int *order_count) {
    FILE *file = fopen(path, "r");
    char line[160];
    int id;
    long timestamp;
    double subtotal, discount, total;
    *total_sales = 0.0;
    *order_count = 0;
    if (!file) return 1;

    while (fgets(line, sizeof line, file)) {
        if (sscanf(line, "%d,%ld,%lf,%lf,%lf", &id, &timestamp,
                   &subtotal, &discount, &total) == 5) {
            *total_sales += total;
            (*order_count)++;
        }
    }
    fclose(file);
    return 1;
}
