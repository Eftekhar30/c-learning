#include <stdio.h>
int main()

{
    char name[50];
    int age;
    char sex[15];
    char address[200];
    int contact[14];
    char email[30];

    printf("Enter your Name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your Age: ");
    scanf("%d", &age);
    getchar();

    printf(" Enter your sex: ");
    fgets(sex, sizeof(sex), stdin);

    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);

    printf("Enter your number: ");
    scanf("%d", &contact);
    getchar();

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);

    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Sex; %s\n", sex);
    printf("Address: %s\n", address);
    printf("Phone Number: %d\n", contact);
    printf("Email: %s\n", email);


}