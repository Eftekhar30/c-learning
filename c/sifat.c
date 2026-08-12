#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =====================================================
   STRUCTURES
   ===================================================== */

struct Case {
    int caseID;
    char title[50];
    char investigator[50];
    char status[30];
    struct Case *next;
};

struct Evidence {
    int evidenceID;
    int caseID;
    char type[50];
    char source[50];
    char status[30];
    char collectedBy[50];
    struct Evidence *next;
};

/* Stack for Evidence Activity History */
struct Action {
    int evidenceID;
    char action[50];
    struct Action *next;
};


/* =====================================================
   GLOBAL POINTERS
   ===================================================== */

struct Case *caseHead = NULL;
struct Evidence *evidenceHead = NULL;
struct Action *top = NULL;


/* =====================================================
   STACK FUNCTIONS
   ===================================================== */

void pushAction(int evidenceID, char action[]) {

    struct Action *newNode;

    newNode = (struct Action *)malloc(sizeof(struct Action));

    newNode->evidenceID = evidenceID;
    strcpy(newNode->action, action);

    newNode->next = top;
    top = newNode;
}


void showHistory() {

    struct Action *temp = top;

    if (temp == NULL) {
        printf("\nNo activity history available.\n");
        return;
    }

    printf("\n========== EVIDENCE ACTIVITY HISTORY ==========\n");

    while (temp != NULL) {

        printf("Evidence E%d -> %s\n",
               temp->evidenceID,
               temp->action);

        temp = temp->next;
    }
}


/* =====================================================
   ADMIN LOGIN
   ===================================================== */

int login() {

    char username[30];
    char password[30];

    printf("\n====================================\n");
    printf("        ADMIN LOGIN\n");
    printf("====================================\n");

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "1234") == 0) {

        printf("\nLogin successful!\n");
        return 1;
    }

    printf("\nInvalid username or password!\n");

    return 0;
}


/* =====================================================
   CASE MANAGEMENT
   ===================================================== */

void addCase() {

    struct Case *newNode;

    newNode = (struct Case *)malloc(sizeof(struct Case));

    printf("\nEnter Case ID: ");
    scanf("%d", &newNode->caseID);

    printf("Enter Case Title: ");
    scanf(" %[^\n]", newNode->title);

    printf("Enter Investigator Name: ");
    scanf(" %[^\n]", newNode->investigator);

    strcpy(newNode->status, "Open");

    newNode->next = NULL;

    if (caseHead == NULL) {

        caseHead = newNode;

    } else {

        struct Case *temp = caseHead;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("\nCase created successfully!\n");
}


void displayCases() {

    struct Case *temp = caseHead;

    if (temp == NULL) {
        printf("\nNo cases available.\n");
        return;
    }

    printf("\n========== CASE LIST ==========\n");

    while (temp != NULL) {

        printf("\nCase ID       : C%d", temp->caseID);
        printf("\nTitle         : %s", temp->title);
        printf("\nInvestigator  : %s", temp->investigator);
        printf("\nStatus        : %s", temp->status);
        printf("\n-------------------------------");

        temp = temp->next;
    }

    printf("\n");
}


void searchCase() {

    int id;
    int found = 0;

    struct Case *temp = caseHead;

    printf("\nEnter Case ID: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->caseID == id) {

            printf("\n========== CASE FOUND ==========\n");

            printf("Case ID      : C%d\n", temp->caseID);
            printf("Title        : %s\n", temp->title);
            printf("Investigator : %s\n", temp->investigator);
            printf("Status       : %s\n", temp->status);

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("\nCase not found!\n");
    }
}


/* =====================================================
   EVIDENCE MANAGEMENT
   ===================================================== */

void addEvidence() {

    struct Evidence *newNode;

    newNode = (struct Evidence *)malloc(sizeof(struct Evidence));

    printf("\nEnter Evidence ID: ");
    scanf("%d", &newNode->evidenceID);

    printf("Enter Case ID: ");
    scanf("%d", &newNode->caseID);

    printf("Enter Evidence Type: ");
    scanf(" %[^\n]", newNode->type);

    printf("Enter Source: ");
    scanf(" %[^\n]", newNode->source);

    printf("Collected By: ");
    scanf(" %[^\n]", newNode->collectedBy);

    strcpy(newNode->status, "Collected");

    newNode->next = NULL;

    if (evidenceHead == NULL) {

        evidenceHead = newNode;

    } else {

        struct Evidence *temp = evidenceHead;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    pushAction(newNode->evidenceID, "Evidence Added");

    printf("\nEvidence added successfully!\n");
}


void displayEvidence() {

    struct Evidence *temp = evidenceHead;

    if (temp == NULL) {
        printf("\nNo evidence available.\n");
        return;
    }

    printf("\n========== EVIDENCE LIST ==========\n");

    while (temp != NULL) {

        printf("\nEvidence ID : E%d", temp->evidenceID);
        printf("\nCase ID     : C%d", temp->caseID);
        printf("\nType        : %s", temp->type);
        printf("\nSource      : %s", temp->source);
        printf("\nCollected By: %s", temp->collectedBy);
        printf("\nStatus      : %s", temp->status);

        printf("\n-----------------------------------");

        temp = temp->next;
    }

    printf("\n");
}


void searchEvidence() {

    int id;
    int found = 0;

    struct Evidence *temp = evidenceHead;

    printf("\nEnter Evidence ID: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->evidenceID == id) {

            printf("\n========== EVIDENCE FOUND ==========\n");

            printf("Evidence ID : E%d\n", temp->evidenceID);
            printf("Case ID     : C%d\n", temp->caseID);
            printf("Type        : %s\n", temp->type);
            printf("Source      : %s\n", temp->source);
            printf("Collected By: %s\n", temp->collectedBy);
            printf("Status      : %s\n", temp->status);

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("\nEvidence not found!\n");
    }
}


/* =====================================================
   UPDATE EVIDENCE STATUS
   ===================================================== */

void updateEvidence() {

    int id;
    int choice;

    struct Evidence *temp = evidenceHead;

    printf("\nEnter Evidence ID: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->evidenceID == id) {

            printf("\nCurrent Status: %s\n", temp->status);

            printf("\n1. Collected");
            printf("\n2. Under Investigation");
            printf("\n3. Verified");
            printf("\n4. Archived");

            printf("\nEnter choice: ");
            scanf("%d", &choice);

            switch (choice) {

                case 1:
                    strcpy(temp->status, "Collected");
                    break;

                case 2:
                    strcpy(temp->status, "Under Investigation");
                    break;

                case 3:
                    strcpy(temp->status, "Verified");
                    break;

                case 4:
                    strcpy(temp->status, "Archived");
                    break;

                default:
                    printf("\nInvalid choice!\n");
                    return;
            }

            pushAction(temp->evidenceID, "Evidence Status Updated");

            printf("\nEvidence status updated successfully!\n");

            return;
        }

        temp = temp->next;
    }

    printf("\nEvidence not found!\n");
}


/* =====================================================
   PROCESS EVIDENCE
   ===================================================== */

void processEvidence() {

    int id;

    struct Evidence *temp = evidenceHead;

    printf("\nEnter Evidence ID: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->evidenceID == id) {

            strcpy(temp->status, "Under Investigation");

            pushAction(temp->evidenceID,
                       "Evidence Processing Started");

            printf("\nEvidence E%d is now under investigation.\n",
                   id);

            return;
        }

        temp = temp->next;
    }

    printf("\nEvidence not found!\n");
}


/* =====================================================
   CASE STATUS UPDATE
   ===================================================== */

void updateCaseStatus() {

    int id;
    int choice;

    struct Case *temp = caseHead;

    printf("\nEnter Case ID: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->caseID == id) {

            printf("\nCurrent Status: %s\n", temp->status);

            printf("\n1. Open");
            printf("\n2. Under Investigation");
            printf("\n3. Closed");

            printf("\nEnter choice: ");
            scanf("%d", &choice);

            switch (choice) {

                case 1:
                    strcpy(temp->status, "Open");
                    break;

                case 2:
                    strcpy(temp->status, "Under Investigation");
                    break;

                case 3:
                    strcpy(temp->status, "Closed");
                    break;

                default:
                    printf("\nInvalid choice!\n");
                    return;
            }

            printf("\nCase status updated!\n");

            return;
        }

        temp = temp->next;
    }

    printf("\nCase not found!\n");
}


/* =====================================================
   MAIN MENU
   ===================================================== */

int main() {

    int choice;

    printf("\n");
    printf("============================================\n");
    printf("       CYBER CRIME EVIDENCE MANAGER\n");
    printf("============================================\n");

    /* Login */
    if (!login()) {
        printf("\nAccess denied!\n");
        return 0;
    }


    while (1) {

        printf("\n\n");
        printf("============================================\n");
        printf("              MAIN MENU\n");
        printf("============================================\n");

        printf("1. Create New Case\n");
        printf("2. Display All Cases\n");
        printf("3. Search Case\n");
        printf("4. Update Case Status\n");

        printf("\n5. Add Evidence\n");
        printf("6. Display All Evidence\n");
        printf("7. Search Evidence\n");
        printf("8. Update Evidence Status\n");
        printf("9. Process Evidence\n");

        printf("\n10. Show Evidence Activity History\n");
        printf("11. Exit\n");

        printf("--------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {

            case 1:
                addCase();
                break;

            case 2:
                displayCases();
                break;

            case 3:
                searchCase();
                break;

            case 4:
                updateCaseStatus();
                break;

            case 5:
                addEvidence();
                break;

            case 6:
                displayEvidence();
                break;

            case 7:
                searchEvidence();
                break;

            case 8:
                updateEvidence();
                break;

            case 9:
                processEvidence();
                break;

            case 10:
                showHistory();
                break;

            case 11:
                printf("\nThank you for using the system!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}