// #include <stdio.h>
// #include<string.h>
// struct swe{
//     char name[20];
//     int sid;
//     double cgpa;
// };

// int main() 
// {
//     struct swe student;

//     strcpy(student.name, "Eftekhar Hossain");
//     student.sid = 123711;
//     student.cgpa = 3.22;

//     printf("student name: %s\n", student.name);
//     printf("student id: %d\n", student.sid);
//     printf("student cgpa: %.2lf\n", student.cgpa);
//     return 0;
// }


//nameshort

#include <stdio.h>
#include<string.h>

void input();
void output();
void nameshort();

struct swe{
    char name[20];
    int sid;
    double cgpa;
};


int main() 
{
    struct swe student[10];
    input(student);
    nameshort(student);
    output(student);



    return 0;
}

void input(struct swe student[]){
    printf("*****************input*************");
    for(int i; i<10;i++){
        scanf("%s%d%lf", &student[i].name, &student[i].sid, &student[i].cgpa);
    }
}
void output(struct swe student[]){
    printf("****************output******************");
    for(int i=0; i<10;i++){
        printf("%s %d %.2lf", student[i].name, student[i].sid, student[i].cgpa);
    }
}
void nameshort(struct swe student[]){
    int i,j;
    for(i=0; i<9; i++){
        for(j=i+1; j<10;j++){
            if(strcmp(student[i].name, student[j].name)>0){
                struct swe temp;
                strcpy(temp.name, student[i].name);
                temp.sid = student[i].sid;
                temp.cgpa = student[i].cgpa;

                strcpy(student[i].name, student[j].name);
                student[i].sid = student[j].sid;
                student[i].cgpa = student[j].cgpa;

                strcpy(student[j].name, temp.name);
                student[j].sid = temp.sid;
                student[j].cgpa = temp.cgpa;
            }
        }
    }
}