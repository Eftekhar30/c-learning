#include <stdio.h>
#include <math.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int is_t_prime(int num) {
    int root = sqrt(num);
    return (root * root == num && is_prime(root));
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (is_t_prime(arr[i])) {
            printf("YES\n", arr[i]);
        } else {
            printf("NO\n", arr[i]);
        }
    }

    return 0;
}
