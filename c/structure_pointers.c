#include<stdio.h>
#include<string.h>
struct Structure{
    char name[15];
    int value;
};
void swap();

int main()
{
    struct Structure v1, v2;
    
    printf("Enter name and value #1: ");
    scanf("%s %d", v1.name, &v1.value);
    
    printf("Enter name and value #2: ");
    scanf("%s %d", v2.name, &v2.value);

    if(v2.value>v1.value)
        swap(&v1,&v2);

    printf("\nResults:\n");
    printf("Name: %s, Value: %d\n", v1.name, v1.value);
    printf("Name: %s, Value: %d\n", v2.name, v2.value);

    return 0;
}

void swap(struct Structure *a, struct Structure *b){
    struct Structure temp;

    strcpy(temp.name, a->name);
    temp.value = a->value;
    strcpy(a->name, b->name);
    a->value = b->value;
    strcpy(b->name, temp.name);
    b->value = temp.value;
    
}