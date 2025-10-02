#include <stdio.h>

int main(void) {
    int n = 6; 
    for (int i = 1; i <= n; i++) {
  
        for (int s = 0; s < n - i; s++) {
            printf("  "); 
        }
  
        for (int k = 0; k < i; k++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}
