#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>

#define maxString 50 


typedef struct toDo {
    char toDo[maxString];
    struct toDo *next;
} toDo;

//global variables
toDo *first = NULL;
toDo *current = NULL;

//reserve memory, fill memory with data, return pointer to filled memory 
//!!! the 'next' value is filled outside of this function
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
    return newTodo;
}

int removeToDo(int number, toDo *firstItem){
    toDo *currentNode = firstItem;
    toDo *nextNode = currentNode->next; 

    if(number==1){
        printf("deleting: %s", currentNode->toDo);
        first = currentNode->next;
        free(currentNode);
        return 0;
    }
    int count = 1;
    //while current is not null
    while(currentNode){ 
        if(count == number-1){
            currentNode->next = currentNode->next->next; //excluding node from pointer path
            printf("\n deleting: %s",nextNode->toDo);
            free(nextNode);
            //setting global current pointer to the end of the list
            while(currentNode){
                if(currentNode->next==NULL){
                    current = currentNode;
                }
                currentNode = currentNode->next;
            }
            break;
        }
        
        currentNode = currentNode->next;
        nextNode = currentNode->next;
        count++;
    }
    return 0;
}

void printToDo(toDo *element, int num){
    if(element == NULL){
            printf("%s is NULL\n", element);
        }
    else{
        printf("-------------------------------------\n");
        printf("%d)\nname: %sadress: %p \nnext adress: %p\n",
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

void initialFetchData(void){
    FILE *file = fopen("todos.txt", "r");

    //getting data from file
    if(file == NULL){
        printf("critical error, could not find source file. Closing program in 4 seconds\n");
        sleep(4);
        exit(1); //1 = error;
    }
    else{ 
        char sentence[maxString];
        while(fgets(sentence, maxString, file)) {
            if(first == NULL){
                first = addToDo(sentence);
                if(first!=NULL){ //if success
                    current = first;
                }
            }
            else{
                current->next = addToDo(sentence);
                if(current->next != NULL){ //if success
                    current = current -> next; //assign new current
                }
            }
        } 
        
    }
    fclose(file);
}

void saveDataToFile(toDo *firstNode){
    printf("your current todos: \n");
    PrintList(first);
    printf("____________________________________________\n");
    printf("are you sure you want to overwrite the data?\n");
    printf("|1. yes\n");
    printf("|0. no\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        FILE *file = fopen("todos.txt", "w");
        if(file == NULL){
            printf("critical error, could not find source file. Closing program in 4 seconds\n");
            sleep(4);
            exit(1); //1 = error;
        }
        else{
            toDo *currentEl = firstNode;
            while(currentEl){
                printf("%s", currentEl->toDo);
                fputs(currentEl->toDo, file);
                currentEl = currentEl->next;
            }
            fclose(file);
        }
    }
    else if(choice == 0){
        //...
    }
    else{
        printf("that is not a correct number. Choose either 1 or 0!\n");
    }

}

int main() {  
    initialFetchData(); 
    int choice;

    while(1){
        printf("----------------------------\n");
        printf("|ENTER THE ACCORDING NUMBER\n");
        printf("|1. Add todo\n");
        printf("|2. Remove todo\n");
        printf("|3. View todos\n");
        printf("|4. Save todos\n");
        printf("|0. Exit\n");
        printf(">");
        int result = scanf("%d", &choice);
        if(result != 0){
            switch (choice)
            {
                case 1: {
                    printf("enter your todo (limit: %d characters)\n", maxString);
                    char userInput[maxString];
                    getchar();
                    fgets(userInput, maxString, stdin);
                    if(first == NULL){
                        first = addToDo(userInput);
                        if(first!=NULL){ //if success
                            printf("%s",first->toDo);
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
                    system("cls");
                    PrintList(first);
                    printf("\n===================\n");
                    printf("which todo would you like to remove? Type the number:\n");
                    int toBeDeleted;
                    scanf("%d", &toBeDeleted);
                    int result = removeToDo(toBeDeleted, first);
                    if(result==1){
                        printf("such number does not exist!\n");
                    }
                    // else{
                        // printf("\nsuccessfully deleted\n");
                    // }
                    system("pause");
                    // sleep(2);
                    // system("cls");
                    break;
                case 3:
                    PrintList(first);
                    system("pause");
                    system("cls");
                    break;
                case 4:
                    saveDataToFile(first);
                    break;
                case 0:
                    printf("thank you for using the program!");
                    sleep(2);
                    exit(0);
                    break;
                
                default:
                    printf("incorrect command, type 1, 2, 3, 4, or if you want to exit: 0\n");
                    system("pause");
                    system("cls");
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