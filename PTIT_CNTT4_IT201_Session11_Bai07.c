#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;


Node *insertAtHead(Node* head, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}



void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

Node* insertAtPosition(Node* head, int value, int position) {

    Node* newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;


    if (position <= 0 || head == NULL) {
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        return newNode;
    }


    Node* current = head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }


    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL)
        current->next->prev = newNode;
    current->next = newNode;

    return head;
}


int main() {
    Node* head = NULL;

    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);


    printf("truoc khi xoa:\n");
    printList(head);

    int n,m;
    printf("nhap so bat ki: ");
    scanf("%d", &n);
    printf("vi tri muon them:");
    scanf("%d", &m);
    head = insertAtPosition(head, n, m);

    printf("sau khi them:\n");
    printList(head);

    return 0;
}