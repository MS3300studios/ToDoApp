#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#define maxString 50 

typedef struct toDo {
    char toDo[maxString];
    struct toDo *next;
} toDo;

toDo *addToDo(char input[maxString]){
    toDo *newTodo = NULL;
    newTodo = malloc(sizeof(toDo));
    if(newTodo != NULL){
        strcpy(newTodo->toDo ,input);
        newTodo->next = NULL;
    }
    else{
        printf("allocating memory error");
    }
    printf("added todo: \ntext: \"%s\" \nadress: %p\n", newTodo->toDo, newTodo);
    return newTodo;
}

void printToDo(toDo *element, int num){
    if(element == NULL){
            printf("%s is NULL\n", element);
        }
    else{
        printf("%d) name: \"%s\" | adress: %p | next adress: %p\n",
            num,
            element->toDo,
            element,
            element->next
        );
    }
}

void PrintList(toDo *firstItem){
    printf("Printing list: \n");
    toDo *current = NULL;
    current = firstItem;
    if(current == NULL){
        printf("list is empty\n");
    }
    else{
        int count = 1;
        //while is not null
        while(current){
            printToDo(current, count);
            current = current->next;
            count++;
        }
    }
}

int main() {   
    toDo *first = NULL;
    toDo *current = NULL;

    int choice;

    while(1){
        printf("\n\n----------------------------\n");
        printf("|ENTER THE ACCORDING NUMBER\n");
        printf("|1. Add todo\n");
        printf("|2. Remove todo\n");
        printf("|3. View todos\n");
        printf("|0. Exit\n");
        printf(">");
        int result = scanf("%d", &choice);
        if(result != 0){
            switch (choice)
            {
                case 1: {
                    printf("enter your todos (limit: %d characters), press # to stop adding todos\n", maxString);
                    char userInput[maxString];
                    getchar();
                    gets(userInput);
                    if(first == NULL){
                        first = addToDo(userInput);
                        if(first!=NULL){ //if success
                            current = first; 
                        }
                    }
                    else{
                        current->next = addToDo(userInput);
                        if(current->next != NULL){ //if success
                            current = current -> next; //assign new current
                        }
                    }
                   
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                    printf("\nremoving element");
                    sleep(2);
                    system("cls");
                    break;
                case 3:
                    PrintList(first);
                    system("pause");
                    system("cls");
                    break;
                case 0:
                    printf("thank you for using the program!");
                    sleep(2);
                    exit(0);
                    break;
                
                default:
                    printf("incorrect command, type 1, 2, 3, or if you want to exit: 0\n");
                    break;
            }
        }
        else{
            printf("enter a numeric value!\n");
            sleep(2);
            break;
        }
        
    }

    return 0;
}


// first = addToDo("wdadwadadawd");

// printToDo(first, 0);