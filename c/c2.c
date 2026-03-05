#include<stdio.h>
void name();
void sex();
void address();
void email();
int age();
void contact();
void output();

int main(){
    name();
    age();
    sex();
    address();
    contact();
    email();
    output();
    return 0;
}

void name(){
    char name[50];
    printf("Enter your Name: ");
    fgets(name, sizeof(name), stdin);
    
}

void sex(){
    char sex[15];
    printf(" Enter your sex: ");
    fgets(sex, sizeof(sex), stdin);
    
}
void address(){
    char address[200];
    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);
    
}

void email(){
    char email[30];
    printf("Enter your mail Address: ");
    fgets(email, sizeof(email), stdin);
    
}

int age(){
    int age;
    printf("Enter your Age: ");
    scanf("%d", &age);
    getchar();
    
    return age;
}

void contact(){
    char contact[15]; 
    printf("Enter your number: ");
    fgets(contact, sizeof(contact), stdin);
    
}
void output(){
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Sex %s\n", sex);
    printf("Address: %s\n", address);
    printf("Phone Number: %s", contact);
    printf("Email: %s\n", email);
}