#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define sCap 4

int qIds[sCap];
char qMethods[sCap][10];
char qEndpoints[sCap][50];

int front = 0;
int rear = -1;
int count = 0;

void enqueue(int req_id, const char* req_method, const char* req_endpoint) {
    if (count >= sCap) {
        printf("[HTTP: 429] Dropping Request #%d\n", req_id);
        return; 
    }

    rear = (rear + 1) % sCap;

    qIds[rear] = req_id;
    strcpy(qMethods[rear], req_method);
    strcpy(qEndpoints[rear], req_endpoint);
    
    count++;
    printf("[HTTP: 202] Enqueued Request #%d (Load: %d/%d)\n", req_id, count, sCap);
}

void dequeue() {
    if (count == 0) {
        printf("[SERVER] Idle... no pending requests to process.\n");
        return;
    }

    int pId = qIds[front];
    char* pMethod = qMethods[front];
    char* pEndpoint = qEndpoints[front];

    count--;

    printf("[SERVER PROCESSING] Finished Request #%d (%s %s) | Remaining load: %d\n", 
           pId, pMethod, pEndpoint, count);

    front = (front + 1) % sCap;
}

int main() {
    printf("=== SERVER (Max Capacity: %d) ===\n\n", sCap);

    int choice;            // Added variable for the user's menu choice
    int next_id = 1;       // Added variable to automatically generate request IDs
    char req_method[10];   // Added variable to hold the user's method input
    char req_endpoint[50]; // Added variable to hold the user's endpoint input

    while (1) {            // Added infinite loop for the interactive menu
        printf("\n1. Send API Request\n2. Process Queue\n3. Exit\nChoose: "); // Added menu prompt
        scanf("%d", &choice); // Added scanf to read user choice

        if (choice == 1) {                          // Added condition for enqueuing data
            printf("Method (e.g., GET): ");         // Added prompt for the HTTP method
            scanf("%s", req_method);                // Added scanf to read the HTTP method
            printf("Endpoint (e.g., /api/users): "); // Added prompt for the endpoint
            scanf("%s", req_endpoint);              // Added scanf to read the endpoint
            enqueue(next_id, req_method, req_endpoint); // Added call to the unchanged enqueue function
            next_id++;                              // Added increment for the next request ID
        } else if (choice == 2) {                   // Added condition for processing a request
            dequeue();                              // Added call to the unchanged dequeue function
        } else if (choice == 3) {                   // Added condition for exiting the application
            break;                                  // Added break to exit the loop gracefully
        } else {                                    // Added catch for invalid input
            printf("Invalid choice.\n");            // Added error message
        }
    }                                               // Added closing brace for the while loop

    printf("\n=== SERVER IDLE ===\n");
    return 0;
}