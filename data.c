#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Student {
    int data;
    struct Student* next;
    struct Student* prev;
} Student;

Student* head = NULL;

// Create new node
Student* createNode(int value) {
    Student* newNode = (Student*)malloc(sizeof(Student));
    newNode->data = value;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

// Insert at front
void insertFront(int value) {
    Student* newNode = createNode(value);
    if (!head) {
        head = newNode;
    } else {
        Student* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
}

// Insert at rear
void insertRear(int value) {
    Student* newNode = createNode(value);
    if (!head) {
        head = newNode;
    } else {
        Student* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}

// Display all
void displayAll() {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    Student* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Delete front
void deleteFront() {
    if (!head) return;

    if (head->next == head) {
        free(head);
        head = NULL;
    } else {
        Student* tail = head->prev;
        Student* temp = head;
        head = head->next;
        tail->next = head;
        head->prev = tail;
        free(temp);
    }
}

// Delete rear
void deleteRear() {
    if (!head) return;

    if (head->next == head) {
        free(head);
        head = NULL;
    } else {
        Student* tail = head->prev;
        tail->prev->next = head;
        head->prev = tail->prev;
        free(tail);
    }
}

// Get front
int getFront() {
    if (!head) return -1;
    return head->data;
}

// Get rear
int getRear() {
    if (!head) return -1;
    return head->prev->data;
}

// Insert at specific position
void insertAtPosition(int value, int pos) {
    if (pos == 0) {
        insertFront(value);
        return;
    }
    Student* temp = head;
    for (int i = 0; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }
    Student* newNode = createNode(value);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

// Delete specific by value
void deleteByValue(int value) {
    if (!head) return;
    Student* temp = head;
    do {
        if (temp->data == value) {
            if (temp == head && head->next == head) {
                free(head);
                head = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == head)
                    head = temp->next;
                free(temp);
            }
            return;
        }
        temp = temp->next;
    } while (temp != head);
}

// Get value by position
int getByPosition(int pos) {
    if (!head) return -1;
    Student* temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
        if (temp == head) return -1;
    }
    return temp->data;
}

int main() {
    insertFront(10);
    insertRear(20);
    insertRear(30);
    insertAtPosition(15, 1);
    displayAll(); // 10 15 20 30
    deleteByValue(20);
    displayAll(); // 10 15 30
    printf("Front: %d, Rear: %d\n", getFront(), getRear());
    printf("Value at pos 1: %d\n", getByPosition(1));
    deleteFront();
    deleteRear();
    displayAll(); // 15
    return 0;
}