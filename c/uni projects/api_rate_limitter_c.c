#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Request {
    int requestId;
    char method[10];
    char endpoint[50];
    struct Request* next;
} Request;

typedef struct RateLimiter {
    Request* front;
    Request* rear;
    int current_size;
    int max_capacity;
} RateLimiter;

RateLimiter* createRateLimiter(int capacity) {
    RateLimiter* rl = (RateLimiter*)malloc(sizeof(RateLimiter));
    rl->front = NULL;
    rl->rear = NULL;
    rl->current_size = 0;
    rl->max_capacity = capacity;
    return rl;
}

void handleIncomingRequest(RateLimiter* rl, int id, const char* method, const char* endpoint) {
    printf("[INCOMING] Request #%d: %s %s... ", id, method, endpoint);

    if (rl->current_size >= rl->max_capacity) {
        printf("FAILED (HTTP 429: Too Many Requests)\n");
        return; 
    }

    Request* newReq = (Request*)malloc(sizeof(Request));
    newReq->requestId = id;
    strcpy(newReq->method, method);
    strcpy(newReq->endpoint, endpoint);
    newReq->next = NULL;

    if (rl->rear == NULL) {
        rl->front = rl->rear = newReq;
    } else {
        rl->rear->next = newReq;
        rl->rear = newReq;
    }
    
    rl->current_size++;
    printf("ACCEPTED (Queue: %d/%d)\n", rl->current_size, rl->max_capacity);
}

void processNextRequest(RateLimiter* rl) {
    if (rl->front == NULL) {
        printf("[SERVER] Idle.. no pending requests.\n");
        return;
    }

    Request* reqToProcess = rl->front;

    rl->front = rl->front->next;
    if (rl->front == NULL) {
        rl->rear = NULL; 
    }

    rl->current_size--;

    printf("[SERVER] Processed Request #%d (%s %s) | Remaining in queue: %d\n", 
           reqToProcess->requestId, reqToProcess->method, reqToProcess->endpoint, rl->current_size);

    free(reqToProcess);
}

int main() {
    RateLimiter* apiGateway = createRateLimiter(4);

    printf("=== SERVER STARTED (Max Queue Capacity: 3) ===\n\n");

    handleIncomingRequest(apiGateway, 1, "GET", "/api/users");
    handleIncomingRequest(apiGateway, 2, "POST", "/api/login");
    handleIncomingRequest(apiGateway, 3, "GET", "/api/dashboard");
    handleIncomingRequest(apiGateway, 4, "DELETE", "/api/users/99"); 
    handleIncomingRequest(apiGateway, 5, "PUT", "/api/settings");    

    printf("\n=== BEGIN PROCESSING LOOP ===\n");

    while (apiGateway->current_size > 0) {
        processNextRequest(apiGateway);
        sleep(1); 
    }

    printf("\n=== SERVER IDLE ===\n");
    return 0;
}