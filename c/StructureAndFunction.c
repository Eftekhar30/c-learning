#include<stdio.h>
#include<stdlib.h>
struct mystructure{
    int a;
    struct mystructure *next;
};
void print(struct mystructure *ptr){
    if(ptr == NULL){
        printf("Null");
        return;
    }
    printf("%d\n", ptr->a);
    print(ptr->next);

}

int main(){
    struct mystructure *obj_start, *obj_end, *obj;
    int n=5,x;
    obj_start =NULL;
    obj_end = NULL;
    obj = NULL;
    while(n--){
        if(obj_start == obj_end && obj_start == NULL){
            obj = (struct mystructure *)malloc(sizeof(struct mystructure));
            scanf("%d", &x);
            obj->a=x;
            obj->next=NULL;
            obj_start = obj_end = obj;
        } else{
            obj = (struct mystructure *)malloc(sizeof(struct mystructure));
            scanf("%d", &x);
            obj->a=x;
            obj->next=NULL;
            obj_end->next = obj;
            obj_end = obj;
        }
    }

    print(obj_start);
    

    return 0;
}

 