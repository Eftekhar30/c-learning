#include<stdio.h>
#include<string.h>
#include<conio.h>

struct user{
    char first_name[50];
    char last_name[50];
    char email[50];
    char password[20];
    char repeat_password[20];
    struct sex{
        char male;
        char female;
    } sex;
    
    struct birth{
        int day;
        int month;
        int year;
    } birth;
} user;

void pass();
void input();
void output();

int main(){
    input();
    output();

    return 0;
}

void input(){
    char sexchk;
    printf("enter your first name: ");
    scanf("%s", user.first_name);
    printf("enter your last name: ");
    scanf("%s", user.last_name);
    printf("enter your email: ");
    scanf("%s", user.email);
    printf("enter your password: ");
    pass(user.password);
    printf("\nrepeat your password: ");
    pass(user.repeat_password);
    if(strcmp(user.password, user.repeat_password) != 0){
        printf("password doesn't match..\n");
        return;
    }
    printf("\nenter your birth date(day): ");
    scanf("%d", &user.birth.day);
    printf("enter your birth month: ");
    scanf("%d", &user.birth.month);
    printf("enter your birth year: ");
    scanf("%d", &user.birth.year);
    printf("enter your sex (if male press m/M or f/F for female): ");
    getchar();
    scanf("%c", &sexchk);

    if(sexchk == 'm' || sexchk == 'M'){
        user.sex.male = 1;    // Use = for assignment
        user.sex.female = 0;
    } else if(sexchk == 'f' || sexchk == 'F'){
        user.sex.female = 1;  // Use = for assignment
        user.sex.male = 0;
    } else {
        printf("wrong input\n");
    }
}

void output(){
    printf("\n \n \n********Your Information********\n \n");
    printf("your first name: %s\n", user.first_name);
    printf("your last name: %s\n", user.last_name);
    printf("your email address: %s\n", user.email);
    printf("your password: %s\n", user.password);
    printf("your birthdate: %d / %d / %d\n", user.birth.day, user.birth.month, user.birth.year);
    if(user.sex.male==1){
        printf("your sex is: Male\n");
    } else if(user.sex.female==1){
        printf("your sex is: Female\n");
    }
}
void pass(char pass[]) {
    char ch;
    int i;
    
    for(i = 0; i < 19; i++) { 
        ch = getch();
        
        if(ch == 13) {  
            break;
        }
        
        if(ch == 8) {
            if(i > 0) {
                i--;
                printf("\b \b");
            }
            i--;  
            continue;
        }
        
        putchar('*');
        pass[i] = ch;
    }
    pass[i] = '\0';
}