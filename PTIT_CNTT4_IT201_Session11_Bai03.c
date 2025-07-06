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
    printf("NULL\n");
}

int found(Node* head) {
    Node* temp = head;
    int count;
    printf(" phan tu muon tim : ", &count);
    scanf("%d",&count);
    int l=0;
    while (temp != NULL) {
        if (count == temp->data) {
            l++;
        }
        temp = temp->next;
    }
    if (l > 0) {
        printf(" true ");
    }else {
        printf(" false ");
    }
}

int main() {
    Node* head = NULL;

    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);

    printList(head);
    found(head);

    return 0;
}