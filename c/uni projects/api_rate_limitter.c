#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define sCap 4

typedef struct {
    int id;
    char method[10];
    char endpoint[50];
} Request;

Request q[sCap];

int front = 0;
int rear = -1;
int count = 0;

void enqueue(int rId, const char* rMethod, const char* rEndpoint) {
    if (count >= sCap) {
        printf("[HTTP: 429] Dropping Request #%d\n", rId);
        return; 
    }

    rear = (rear + 1) % sCap;

    q[rear].id = rId;
    strcpy(q[rear].method, rMethod);
    strcpy(q[rear].endpoint, rEndpoint);
    
    count++;
    printf("[HTTP: 202] Enqueued Request #%d (Load: %d/%d)\n", rId, count, sCap);
}

void dequeue() {
    if (count == 0) {
        printf("\n--- SERVER IDLE ---\n");
        return;
    }

    Request pReq = q[front];

    count--;

    printf("Finished Request #%d (%s %s) | Remaining load: %d\n", 
           pReq.id, pReq.method, pReq.endpoint, count);

    front = (front + 1) % sCap;
}

int main() {
    printf("--- SERVER (Max Cap: %d) ---\n\n", sCap);

    enqueue(1, "GET", "/api/users");
    enqueue(2, "POST", "/api/login");
    enqueue(3, "GET", "/api/dashboard");
    enqueue(4, "DELETE", "/api/users/genix"); 
    enqueue(5, "PUT", "/api/settings");    

    printf("\n--- EVENT PROCESSING ---\n");

    while (count > 0) {
        dequeue();
        sleep(1); 
    }

    printf("\n--- SERVER IDLE ---\n");
    return 0;
}