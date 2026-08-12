#include <stdio.h>

int main() {
    int stack[8] = {1, 2, 3, 4, 5};
    int stacksize = 8;
    int top = 4;
    int item;

    if (top == - 1) {
        printf("underflow\n");
        return 0;
    }
 
    item = stack[top];
    top = top - 1;

    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }

    return 0;
}