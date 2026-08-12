#include <stdio.h>
int main() {
    int arr[100], n, target, count = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d sorted elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Target: ");
    scanf("%d", &target);

    int low = 0, high = n - 1;

    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == target) {
            count++;
            printf("Element found at position %d\n", mid + 1);
            break;
        }
        else if(arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    if(count == 0) {
        printf("Element not found\n");
    }
    return 0;
}