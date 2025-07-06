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

Node* deleteAtPosition(Node* head, int position) {
    if (head == NULL || position < 0) return head;

    if (position == 0) {
        Node* temp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        free(temp);
        return head;
    }


    Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) return head;

    if (current->prev != NULL)
        current->prev->next = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);
    return head;
}


void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

int main() {
    Node* head = NULL;

    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);
    head = insertAtHead(head, 4);

    printf("truoc khi xoa:\n");
    printList(head);

    int position;
    printf("vi tri muon xoa:");
    scanf("%d", &position);
    head = deleteAtPosition(head, position);
    printf("sau khi xoa:\n");
    printList(head);

    return 0;
}