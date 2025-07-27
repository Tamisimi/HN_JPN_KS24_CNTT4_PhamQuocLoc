#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1000
#define MAX_STACK 1000

typedef struct {
    char action;
    char value;
} Operation;

typedef struct {
    Operation data[MAX_STACK];
    int top;
} Stack;

typedef struct {
    char text[MAX_TEXT];
    int textLength;
    Stack undoStack;
    Stack redoStack;
} TextEditor;

void initEditor(TextEditor *editor) {
    editor->textLength = 0;
    editor->text[0] = '\0';
    editor->undoStack.top = -1;
    editor->redoStack.top = -1;
}

void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_STACK - 1;
}

void push(Stack *stack, Operation op) {
    if (isFull(stack)) {
        printf("Stack full, cannot add!\n");
        return;
    }
    stack->data[++stack->top] = op;
}

Operation pop(Stack *stack) {
    if (isEmpty(stack)) {
        Operation empty = {'\0', '\0'};
        return empty;
    }
    return stack->data[stack->top--];
}

void insertChar(TextEditor *editor, char c) {
    if (editor->textLength >= MAX_TEXT - 1) {
        printf("Text full, cannot add!\n");
        return;
    }
    editor->text[editor->textLength++] = c;
    editor->text[editor->textLength] = '\0';
    Operation op = {'I', c};
    push(&editor->undoStack, op);
    editor->redoStack.top = -1;
    printf("Added char '%c'\n", c);
}

void undo(TextEditor *editor) {
    if (isEmpty(&editor->undoStack)) {
        printf("Nothing to undo!\n");
        return;
    }
    Operation op = pop(&editor->undoStack);
    if (op.action == 'I' && editor->textLength > 0) {
        editor->text[--editor->textLength] = '\0';
        push(&editor->redoStack, op);
        printf("Undid: removed char '%c'\n", op.value);
    }
}

void redo(TextEditor *editor) {
    if (isEmpty(&editor->redoStack)) {
        printf("Nothing to redo!\n");
        return;
    }
    Operation op = pop(&editor->redoStack);
    if (op.action == 'I') {
        insertChar(editor, op.value);
    }
}

void displayText(TextEditor *editor) {
    if (editor->textLength == 0) {
        printf("Text is empty!\n");
    } else {
        printf("Current text: %s\n", editor->text);
    }
}

int main() {
    TextEditor editor;
    initEditor(&editor);
    int choice;
    char value;

    do {
        printf("===== TEXT EDITOR =====\n");
        printf("1. INSERT\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter char: ");
                scanf(" %c", &value);
                insertChar(&editor, value);
                break;
            case 2:
                undo(&editor);
                break;
            case 3:
                redo(&editor);
                break;
            case 4:
                displayText(&editor);
                break;
            case 5:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
        printf("\n");
    } while (1);

    return 0;
}