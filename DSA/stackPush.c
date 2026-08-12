#include <stdio.h>

int main() {
    int stack[8] = {1, 2, 3, 4, 5};
    int stacksize = 8;
    int top = 4;
    int item = 10;

    if (top == stacksize - 1) {
        printf("overflow\n");
        return 0;
    }

    top = top + 1;
    stack[top] = item;

    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }

    return 0;
}