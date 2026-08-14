//                                    ID: 253-35-383
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char username[30];
    int rank;
    int ping;
} Player;

typedef struct QNode {
    Player player;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front; 
    QNode* rear; 
    int size;
} Queue;


typedef struct LNode {
    Player player;
    struct LNode* next;
} LNode;

typedef struct {
    LNode* head;
} Lobby;

typedef struct MNode {
    char mapName[30];
    struct MNode* next;
} MNode;

typedef struct {
    MNode* currentMap;
} MapRotation;

void setupDatabase(Player db[]) {
    db[0] = (Player){"shadow ninja", 50, 24};
    db[1] = (Player){"faze optic", 75, 12};
    db[2] = (Player){"noob slayer", 10, 89};
    db[3] = (Player){"pro sniper", 99, 5};
    db[4] = (Player){"casual gamer", 25, 45};
}

void sanitizeInput(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

int findPlayerIndex(Player db[], char name[], int totalPlayers) {
    for (int i = 0; i < totalPlayers; i++) {
        if (strcmp(db[i].username, name) == 0) {
            return i;
        }
    }
    return -1; 
}

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void enqueue(Queue* q, Player p) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->player = p;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

Player dequeue(Queue* q) {
    Player emptyPlayer = {"", 0, 0};
    if (q->front == NULL) return emptyPlayer;

    QNode* temp = q->front;
    Player p = temp->player;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp); 
    q->size--;
    return p;
}

void initLobby(Lobby* l) {
    l->head = NULL;
}

void addToLobby(Lobby* l, Player p) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->player = p;
    newNode->next = l->head;
    l->head = newNode;
}

void clearLobby(Lobby* l) {
    LNode* current = l->head;
    while (current != NULL) {
        LNode* next = current->next;
        free(current);
        current = next;
    }
    l->head = NULL;
}

void setupMaps(MapRotation* m) {
    char mapNames[3][30] = {"Dust II", "Mirage", "Inferno"};
    MNode* head = NULL;
    MNode* prev = NULL;

    for (int i = 0; i < 3; i++) {
        MNode* newNode = (MNode*)malloc(sizeof(MNode));
        strcpy(newNode->mapName, mapNames[i]);
        
        if (head == NULL) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
    }
    prev->next = head; 
    m->currentMap = head;
}

int main() {
    Player playerDB[5];
    setupDatabase(playerDB);

    Queue matchQueue;
    initQueue(&matchQueue);

    Lobby activeLobby;
    initLobby(&activeLobby);

    MapRotation maps;
    setupMaps(&maps);

    int choice;
    char input[30];

    do {
        printf("\n=======================================\n");
        printf("    MATCHMAKING SERVER - ADMIN PANEL   \n");
        printf("=======================================\n");
        printf(" Current Map Rotation: %s\n", maps.currentMap->mapName);
        printf(" Queue Size: %d/3 Players\n", matchQueue.size);
        printf("=======================================\n");
        printf(" [1] View Player Database\n");
        printf(" [2] Search Player Status\n");
        printf(" [3] Add Player to Queue\n");
        printf(" [4] Start Match (Pops Queue -> Lobby)\n");
        printf(" [5] End Match (Clears Lobby -> Rotates Map)\n");
        printf(" [6] Shutdown Server\n");
        printf("=======================================\n");
        printf("root@server:~# ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\n--- REGISTERED PLAYERS ---\n");
            for(int i = 0; i < 5; i++) {
                printf("USER: %-15s | RANK: %-3d | PING: %dms\n", playerDB[i].username, playerDB[i].rank, playerDB[i].ping);
            }
        } 
        else if (choice == 2) {
            printf("Enter username to query: ");
            scanf(" %[^\n]", input);
            sanitizeInput(input);
            
            int index = findPlayerIndex(playerDB, input, 5);
            if (index != -1) {
                printf("\n=> FOUND: %s is Rank %d with %dms ping.\n", playerDB[index].username, playerDB[index].rank, playerDB[index].ping);
            } else {
                printf("\n=> ERROR: Player not found in database.\n");
            }
        } 
        else if (choice == 3) {
            printf("Enter username to queue: ");
            scanf(" %[^\n]", input);
            sanitizeInput(input);
            
            int index = findPlayerIndex(playerDB, input, 5);
            if (index != -1) {
                enqueue(&matchQueue, playerDB[index]);
                printf("\n=> SUCCESS: %s added to matchmaking queue.\n", playerDB[index].username);
            } else {
                printf("\n=> ERROR: Unregistered players cannot queue.\n");
            }
        } 
        else if (choice == 4) {
            if (matchQueue.size >= 3) {
                clearLobby(&activeLobby);
                
                for (int i = 0; i < 3; i++) {
                    addToLobby(&activeLobby, dequeue(&matchQueue));
                }
                
                printf("\n=> MATCH STARTED ON %s!\n", maps.currentMap->mapName);
                printf("--- ACTIVE SESSION ROSTER ---\n");
                
                LNode* current = activeLobby.head;
                while (current != NULL) {
                    printf("- %s\n", current->player.username);
                    current = current->next;
                }
            } else {
                printf("\n=> ERROR: Not enough players. Waiting for %d more.\n", 3 - matchQueue.size);
            }
        } 
        else if (choice == 5) {
            if (activeLobby.head != NULL) {
                clearLobby(&activeLobby);
                
                maps.currentMap = maps.currentMap->next;
                
                printf("\n=> MATCH CONCLUDED. Lobby cleared.\n");
                printf("=> Map rotated to: %s\n", maps.currentMap->mapName);
            } else {
                printf("\n=> ERROR: No active match to end.\n");
            }
        }

    } while (choice != 6);

    clearLobby(&activeLobby);
    while (matchQueue.size > 0) dequeue(&matchQueue);
    
    printf("\nServer shutting down... Goodbye.\n");
    return 0;
}
