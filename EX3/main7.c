#include <stdio.h>

int main() {
    int i = 1599;
    if (i <= 1500) {
        printf("70元");
    } else {
        int n = i - 1500;
        if (n < 100) {
            printf("%d元", 70 + n);
        } else {
            printf("%d元", 70 + (n / 100) * 10);
        }
    }
    return 0;
}
