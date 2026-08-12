#include <stdio.h>
#include <string.h>
#define MAX_BUSES 20
#define MAX_STOPS 10
#define NAME_LEN 40
#define STOP_LEN 30
#define QUEUE_SIZE 10
#define STACK_SIZE 10
struct Bus {
    int id;
    char name[NAME_LEN];
    char startPoint[STOP_LEN];
    char endPoint[STOP_LEN];
    char stops[MAX_STOPS][STOP_LEN];
    int stopCount;
};
struct Bus buses[MAX_BUSES];
int busCount = 0;
char passengerQueue[QUEUE_SIZE][NAME_LEN];
int front = -1;
int rear = -1;
char searchStack[STACK_SIZE][100];
int top = -1;
void initializeBuses(void);
void showMenu(void);
void trimNewline(char str[]);
void toLowerCase(char dest[], const char src[]);
void searchBusByName(void);
void searchBusByID(void);
void findBusesBetween(void);
void showCompleteRoute(void);
void printBusInfo(struct Bus b);
void printRoute(struct Bus b);
int findStopIndex(struct Bus b, const char location[]);
int binarySearchBusID(int targetID);
int isQueueFull(void);
int isQueueEmpty(void);
void enqueuePassenger(void);
void dequeuePassenger(void);
void displayQueue(void);
int isStackFull(void);
int isStackEmpty(void);
void pushSearch(const char record[]);
void popSearch(void);
void displayStack(void);
int main(void)
{
    int choice;
    char input[20];
    initializeBuses();
    printf("============================================\n");
    printf("       DHAKA LOCAL BUS ROUTE FINDER\n");
    printf("============================================\n");
    printf("Sample/static data for academic use only.\n");
    do {
        showMenu();
        printf("Enter your choice: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("\nInvalid input! Enter a number from 1 to 10.\n");
            continue;
        }
        switch (choice) {
            case 1:
                searchBusByName();
                break;
            case 2:
                searchBusByID();
                break;
            case 3:
                findBusesBetween();
                break;
            case 4:
                showCompleteRoute();
                break;
            case 5:
                enqueuePassenger();
                break;
            case 6:
                dequeuePassenger();
                break;
            case 7:
                displayQueue();
                break;
            case 8:
                displayStack();
                break;
            case 9:
                popSearch();
                break;
            case 10:
                printf("\nThank you for using the system!\n");
                break;
            default:
                printf("\nInvalid menu choice!\n");
        }
        printf("\n");
    } while (choice != 10);
    return 0;
}
void showMenu(void)
{
    printf("\n============================================\n");
    printf("       DHAKA LOCAL BUS ROUTE FINDER\n");
    printf("============================================\n");
    printf("1. Search Bus by Name\n");
    printf("2. Search Bus by ID\n");
    printf("3. Find Buses Between Two Locations\n");
    printf("4. Show Complete Bus Route\n");
    printf("5. Add Passenger to Queue\n");
    printf("6. Serve Passenger\n");
    printf("7. Show Waiting Passengers\n");
    printf("8. Show Search History\n");
    printf("9. Remove Last Search\n");
    printf("10. Exit\n");
    printf("============================================\n");
}
void trimNewline(char str[])
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}
void toLowerCase(char dest[], const char src[])
{
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        if (src[i] >= 'A' && src[i] <= 'Z')
            dest[i] = src[i] + ('a' - 'A');
        else
            dest[i] = src[i];
    }
    dest[i] = '\0';
}
void initializeBuses(void)
{
    struct Bus temp[MAX_BUSES] = {
        {1, "BRTC", "Gabtoli", "Motijheel",
        {"Gabtoli","Technical","Mirpur 1","Mirpur 10",
         "Agargaon","Farmgate","Karwan Bazar","Motijheel"}, 8},
        {2, "Trust Transport", "Uttara", "Sayedabad",
        {"Uttara","Airport","Mohakhali","Farmgate",
         "Shahbagh","Motijheel","Sayedabad"}, 7},
        {3, "Turag Paribahan", "Mirpur 12", "Azimpur",
        {"Mirpur 12","Mirpur 10","Agargaon","Farmgate",
         "New Market","Azimpur"}, 6},
        {4, "Bikalpa Paribahan", "Gabtoli", "Jatrabari",
        {"Gabtoli","Technical","Kalyanpur","Shyamoli",
         "Asad Gate","Dhanmondi","Jatrabari"}, 7},
        {5, "Rajdhani Paribahan", "Uttara", "Motijheel",
        {"Uttara","Airport","Banani","Mohakhali",
         "Farmgate","Karwan Bazar","Motijheel"}, 7},
        {6, "Ajmeri Glory", "Gabtoli", "Sayedabad",
        {"Gabtoli","Mirpur 1","Mirpur 10","Agargaon",
         "Farmgate","Shahbagh","Motijheel","Sayedabad"}, 8},
        {7, "Green Anabil", "Mohammadpur", "Jatrabari",
        {"Mohammadpur","Asad Gate","Dhanmondi","Science Lab",
         "New Market","Motijheel","Jatrabari"}, 7},
        {8, "Shikor Paribahan", "Mirpur 10", "Sayedabad",
        {"Mirpur 10","Agargaon","Farmgate","Karwan Bazar",
         "Shahbagh","Motijheel","Sayedabad"}, 7},
        {9, "Airport Rider", "Airport", "Motijheel",
        {"Airport","Khilkhet","Banani","Mohakhali",
         "Farmgate","Karwan Bazar","Motijheel"}, 7},
        {10, "Gulistan Chaka", "Gabtoli", "Gulistan",
        {"Gabtoli","Technical","Mirpur 1","Kazipara",
         "Shewrapara","Farmgate","Gulistan"}, 7},
        {11, "City Link", "Uttara", "Jatrabari",
        {"Uttara","Airport","Mohakhali","Mouchak",
         "Malibagh","Motijheel","Jatrabari"}, 7},
        {12, "Anabil Super", "Mirpur 1", "Motijheel",
        {"Mirpur 1","Mirpur 10","Agargaon","Farmgate",
         "Karwan Bazar","Shahbagh","Motijheel"}, 7},
        {13, "Prochesta", "Gabtoli", "Azimpur",
        {"Gabtoli","Kalyanpur","Shyamoli","Asad Gate",
         "Dhanmondi","New Market","Azimpur"}, 7},
        {14, "Etihad Paribahan", "Mirpur 12", "Sayedabad",
        {"Mirpur 12","Mirpur 10","Farmgate","Karwan Bazar",
         "Shahbagh","Motijheel","Sayedabad"}, 7},
        {15, "Projapoti", "Uttara", "Gulistan",
        {"Uttara","Airport","Banani","Mohakhali",
         "Farmgate","Shahbagh","Gulistan"}, 7},
        {16, "Nurjahan Paribahan", "Mohammadpur", "Sayedabad",
        {"Mohammadpur","Dhanmondi","Science Lab","New Market",
         "Motijheel","Sayedabad"}, 6},
        {17, "Boishakhi", "Gabtoli", "Jatrabari",
        {"Gabtoli","Technical","Mirpur 1","Farmgate",
         "Karwan Bazar","Motijheel","Jatrabari"}, 7},
        {18, "Deshbandhu", "Mirpur 10", "Gulistan",
        {"Mirpur 10","Agargaon","Farmgate","Shahbagh",
         "Motijheel","Gulistan"}, 6},
        {19, "Shovan Paribahan", "Uttara", "Sayedabad",
        {"Uttara","Khilkhet","Mohakhali","Mouchak",
         "Malibagh","Motijheel","Sayedabad"}, 7},
        {20, "Himachal Paribahan", "Gabtoli", "Motijheel",
        {"Gabtoli","Mirpur 1","Mirpur 10","Farmgate",
         "Karwan Bazar","Shahbagh","Motijheel"}, 7}
    };
    int i;
    for (i = 0; i < MAX_BUSES; i++)
        buses[i] = temp[i];
    busCount = MAX_BUSES;
}
void searchBusByName(void)
{
    char input[NAME_LEN];
    char inputLower[NAME_LEN];
    char nameLower[NAME_LEN];
    char history[100];
    int i, found = 0;
    printf("\nEnter Bus Name: ");
    fgets(input, sizeof(input), stdin);
    trimNewline(input);
    toLowerCase(inputLower, input);
    for (i = 0; i < busCount; i++) {
        toLowerCase(nameLower, buses[i].name);
        if (strcmp(nameLower, inputLower) == 0) {
            printf("\nBus Found!\n");
            printBusInfo(buses[i]);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nBus not found.\n");
    sprintf(history, "Bus Name Search: %s", input);
    pushSearch(history);
}
int binarySearchBusID(int targetID)
{
    int low = 0;
    int high = busCount - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (buses[mid].id == targetID)
            return mid;
        if (buses[mid].id < targetID)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
void searchBusByID(void)
{
    char input[20];
    char history[100];
    int targetID, index;
    printf("\nEnter Bus ID: ");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &targetID) != 1) {
        printf("\nInvalid Bus ID input.\n");
        return;
    }
    index = binarySearchBusID(targetID);
    if (index != -1) {
        printf("\nBus Found!\n");
        printBusInfo(buses[index]);
    } else {
        printf("\nBus not found.\n");
    }
    sprintf(history, "Bus ID Search: %d", targetID);
    pushSearch(history);
}
int findStopIndex(struct Bus b, const char location[])
{
    char locationLower[STOP_LEN];
    char stopLower[STOP_LEN];
    int i;
    toLowerCase(locationLower, location);
    for (i = 0; i < b.stopCount; i++) {
        toLowerCase(stopLower, b.stops[i]);
        if (strcmp(stopLower, locationLower) == 0)
            return i;
    }
    return -1;
}
void findBusesBetween(void)
{
    char from[STOP_LEN];
    char to[STOP_LEN];
    char history[100];
    int i, fromIndex, toIndex;
    int matchCount = 0;
    printf("\nEnter Starting Location: ");
    fgets(from, sizeof(from), stdin);
    trimNewline(from);
    printf("Enter Destination: ");
    fgets(to, sizeof(to), stdin);
    trimNewline(to);
    printf("\nAvailable Buses:\n");
    for (i = 0; i < busCount; i++) {
        fromIndex = findStopIndex(buses[i], from);
        toIndex = findStopIndex(buses[i], to);
        if (fromIndex != -1 && toIndex != -1 &&
            fromIndex < toIndex) {
            matchCount++;
            printf("\n%d. %s\n", matchCount, buses[i].name);
            printRoute(buses[i]);
        }
    }
    if (matchCount == 0) {
        printf("No buses found between \"%s\" and \"%s\".\n",
               from, to);
    }
    sprintf(history, "Route Search: %s to %s", from, to);
    pushSearch(history);
}
void showCompleteRoute(void)
{
    char input[NAME_LEN];
    char inputLower[NAME_LEN];
    char nameLower[NAME_LEN];
    char buffer[20];
    char history[100];
    int choice, id, index, i, found = 0;
    printf("\nSearch Route By:\n");
    printf("1. Bus ID\n");
    printf("2. Bus Name\n");
    printf("Enter choice: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &choice) != 1) {
        printf("\nInvalid choice.\n");
        return;
    }
    if (choice == 1) {
        printf("Enter Bus ID: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &id) != 1) {
            printf("\nInvalid Bus ID.\n");
            return;
        }
        index = binarySearchBusID(id);
        if (index != -1) {
            printf("\nBus Name: %s\n", buses[index].name);
            printRoute(buses[index]);
            found = 1;
        }
        sprintf(history, "Viewed Route of Bus ID: %d", id);
    } else if (choice == 2) {
        printf("Enter Bus Name: ");
        fgets(input, sizeof(input), stdin);
        trimNewline(input);
        toLowerCase(inputLower, input);
        for (i = 0; i < busCount; i++) {
            toLowerCase(nameLower, buses[i].name);
            if (strcmp(nameLower, inputLower) == 0) {
                printf("\nBus Name: %s\n", buses[i].name);
                printRoute(buses[i]);
                found = 1;
                break;
            }
        }
        sprintf(history, "Viewed Route of Bus: %s", input);
    } else {
        printf("\nInvalid choice.\n");
        return;
    }
    if (!found)
        printf("\nBus not found.\n");
    pushSearch(history);
}
void printBusInfo(struct Bus b)
{
    printf("Bus ID         : %d\n", b.id);
    printf("Bus Name       : %s\n", b.name);
    printf("Starting Point : %s\n", b.startPoint);
    printf("Ending Point   : %s\n", b.endPoint);
    printf("Route          : ");
    printRoute(b);
}
void printRoute(struct Bus b)
{
    int i;
    for (i = 0; i < b.stopCount; i++) {
        printf("%s", b.stops[i]);
        if (i < b.stopCount - 1)
            printf(" -> ");
    }
    printf("\n");
}
int isQueueFull(void)
{
    return rear == QUEUE_SIZE - 1;
}
int isQueueEmpty(void)
{
    return front == -1;
}
void enqueuePassenger(void)
{
    char name[NAME_LEN];
    if (isQueueFull()) {
        printf("\nQueue Overflow! Queue is full.\n");
        return;
    }
    printf("\nEnter Passenger Name: ");
    fgets(name, sizeof(name), stdin);
    trimNewline(name);
    if (front == -1)
        front = 0;
    rear++;
    strcpy(passengerQueue[rear], name);
    printf("Passenger \"%s\" added to Queue.\n", name);
}
void dequeuePassenger(void)
{
    if (isQueueEmpty()) {
        printf("\nQueue Underflow! Queue is empty.\n");
        return;
    }
    printf("\nServing Passenger: %s\n", passengerQueue[front]);
    front++;
    if (front > rear) {
        front = -1;
        rear = -1;
    }
}
void displayQueue(void)
{
    int i;
    if (isQueueEmpty()) {
        printf("\nQueue is empty. No passengers are waiting.\n");
        return;
    }
    printf("\nWaiting Passengers (Front -> Rear):\n");
    for (i = front; i <= rear; i++)
        printf("%d. %s\n", i - front + 1, passengerQueue[i]);
}
int isStackFull(void)
{
    return top == STACK_SIZE - 1;
}
int isStackEmpty(void)
{
    return top == -1;
}
void pushSearch(const char record[])
{
    if (isStackFull()) {
        printf("\nStack Overflow! Search history is full.\n");
        return;
    }
    top++;
    strcpy(searchStack[top], record);
}
void popSearch(void)
{
    if (isStackEmpty()) {
        printf("\nStack Underflow! Search history is empty.\n");
        return;
    }
    printf("\nRemoved Last Search: %s\n", searchStack[top]);
    top--;
}
void displayStack(void)
{
    int i;
    if (isStackEmpty()) {
        printf("\nStack is empty. No search history.\n");
        return;
    }
    printf("\nSearch History (Most Recent First):\n");
    for (i = top; i >= 0; i--)
        printf("%d. %s\n", top - i + 1, searchStack[i]);
}