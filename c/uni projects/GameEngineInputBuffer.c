#include <stdio.h>
#include <string.h>

#define bSizeE 5 

typedef struct {
    char action[20];
} Input;

Input buffer[bSizeE];
int front = 0;
int rear = -1;
int count = 0;

void enqueue(const char* action) {
    if (count == bSizeE) {
        printf("Input Buffer Full! Dropped action: %s\n", action);
        return;
    }

    rear = (rear + 1) % bSizeE;
    strcpy(buffer[rear].action, action);
    count++;
    
    printf("Player pressed: %s (Buffer: %d/%d)\n", action, count, bSizeE);
}

void dequeue() {
    if (count == 0) {
        printf("Character is idle.\n");
        return;
    }

    char* actionPlay = buffer[front].action;
    front = (front + 1) % bSizeE;
    count--;

    printf("Playing animation: %s... (Remaining in buffer: %d)\n", actionPlay, count);
}

int main() {
    printf("--- GAME STARTED ---\n\n");

    enqueue("JUMP");
    enqueue("SHOOT");
    enqueue("RELOAD");
    enqueue("CROUCH");
    enqueue("HEAL");
    enqueue("DODGE");

    printf("\n--- QUEUE LOOP ---\n");
    while (count > 0) {
        dequeue();
    }

    printf("\n--- CHARACTER IS IDLE. ---\n");
    return 0;
}