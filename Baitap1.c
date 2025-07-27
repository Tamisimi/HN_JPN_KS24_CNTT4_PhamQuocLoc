#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[100];
    int priority;
    char deadline[100];
}Task;

typedef struct SingleNode {
    Task task;
    struct SingleNode *next;
}SingleNode;

typedef struct DoubleNode {
    Task task;
    struct DoubleNode *next;
    struct DoubleNode *prev;
}DoubleNode;

SingleNode* head = NULL;
DoubleNode* doubleHead = NULL;
DoubleNode* doubleTail = NULL;
int currentId = 1;

SingleNode* createSingleNode(Task task) {
    SingleNode* newNode = (SingleNode*)malloc(sizeof(SingleNode));
    newNode->task = task;
    newNode->next = NULL;
    return newNode;
}

DoubleNode* createDoubleNode(Task task) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->task = task;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addTask() {
    Task task;
    task.id = currentId++;
    getchar();
    printf("Add title: ");
    fgets(task.title,100,stdin);
    task.title[strcspn(task.title , "\n")] = '\0';
    printf("Add priority: ");
    scanf("%d", &task.priority);
    getchar();
    printf("Add deadline: ");
    fgets(task.deadline,100,stdin);
    task.deadline[strcspn(task.deadline , "\n")] = '\0';
    SingleNode* newNode = createSingleNode(task);
    newNode->next = head;
    head = newNode;
    printf("Add succeedfully");
}

void displayTask() {
    if (!head) {
        printf("Empty list");
        return;
    }
    else {
        SingleNode* current = head;
        while (current != NULL) {
            printf("ID: %d | Title: %s | Priority: %d | Deadline: %s ",current->task.id, current->task.title, current->task.priority, current->task.deadline);
            printf("/n");
            current = current->next;
        }
    }
}

void deleteTask() {
    int id;
    printf("Enter Id: ");
    scanf("%d", &id);
    SingleNode* temp = head;
    SingleNode* prev = NULL;
    while (temp != NULL) {
        if (temp->task.id == id) {
            if (prev == NULL) {
                head = temp->next;
            }else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Delete Succeedfully");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Cant find the Id");
}

void updateTask() {
    int id;
    printf("Enter Id: ");
    scanf("%d", &id);
    SingleNode* current =head;
    while (current != NULL) {
        if (current->task.id == id) {
            printf("Enter new title");
            fgets(current->task.title,100,stdin);
            current->task.title[strcspn(current->task.title, "\n")] = '\0';
            printf("Enter new priority");
            scanf("%d", &current->task.priority);
            getchar();
            printf("Enter new deadline");
            fgets(current->task.deadline,100,stdin);
            current->task.deadline[strcspn(current->task.deadline, "\n")] = '\0';
            printf("Update succeedfuly");
            return;
        }
        current = current->next;
    }
    printf("Cannot find ");
}

void MarkTask() {
    int id;
    printf("Enter Id: ");
    scanf("%d", &id);
    SingleNode* temp = head;
    SingleNode* prev = NULL;
    while (temp) {
        if (temp->task.id == id) {
            if (prev == NULL) {
                head = temp->next;
            }else {
                prev->next = temp->next;
            }
            DoubleNode* doneNode = createDoubleNode(temp->task);
            if (!doubleHead) {
                doubleHead = doubleTail = doneNode;
            }else {
                doubleTail->next = doneNode;
                doneNode->prev = doubleTail;
                doubleTail = doneNode;
            }
        }
        SingleNode* next = temp->next;
        free (temp);
        temp = temp->next;
    }
    printf("Cannot found");
}

void sortTask() {
    if (head == NULL || head->next == NULL) {
        return;
    }
    for (SingleNode* i =head; i != NULL;i = i->next) {
        for (SingleNode* j = i ->next;j != NULL;j = j->next) {
            if (i->task.priority > j->task.priority) {
                Task temp = i->task;
                i->task = j->task;
                j->task = temp;
            }
        }
    }
    printf("Sort succeedfully");
}

void searchTask() {
    char keyword[100];
    printf("Enter Title: ");
    fgets(keyword,100,stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    SingleNode* current = head;
    int found = 0;
    while (current != NULL) {
        if (strstr(current->task.title, keyword)) {
            printf("ID: %d | Title: %s | Priority: %d | Deadline: %s ",current->task.id, current->task.title, current->task.priority, current->task.deadline);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Not found");
    }
}



int main() {
    Task task;
    int choice;
    do {
        printf("1. Add Task\n");
        printf("2. Display Task\n");
        printf("3. Delete Tasks\n");
        printf("4. Update Tasks\n");
        printf("5. Mark Complete Task\n");
        printf("6. Sort Tasks\n");
        printf("7. Find Task\n");
        printf("8. Exit\n");
        printf("Choose your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTask();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                updateTask();
                break;
            case 5:
                MarkTask();
                break;
            case 6:
                sortTask();
                break;
            case 7:
                searchTask();
                break;
            case 8:
                printf("Exit");
                break;
            default:
                printf("Invalid Choice\n");
        }
    }while (choice != 8);
    return 0;
}