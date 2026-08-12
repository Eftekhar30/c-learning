#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int target = 8;
    int low = 0, high = 4, mid;
    int found = 0;

    while (low <= high) {
        mid = (low + high) / 2;

        if (arr[mid] == target) {
            found = 1;
            break;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (found) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    return 0;
}