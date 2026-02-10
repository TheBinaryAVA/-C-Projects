#include <stdio.h>
#include <stdlib.h>

/* ==============================
   STRUCTURE DEFINITION
   ============================== */

struct Node {
    int data;
    struct Node* next;
};

/* ==============================
   BASIC UTILITIES
   ============================== */

struct Node* createNode(int data) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void display(struct Node* head) {
    if (!head) {
        printf("List is empty\n");
        return;
    }
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int length(struct Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

/* ==============================
   INSERT OPERATIONS
   ============================== */

struct Node* insertBegin(struct Node* head, int data) {
    struct Node* n = createNode(data);
    n->next = head;
    return n;
}

struct Node* insertEnd(struct Node* head, int data) {
    struct Node* n = createNode(data);
    if (!head) return n;

    struct Node* temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = n;
    return head;
}

struct Node* insertAtPos(struct Node* head, int data, int pos) {
    if (pos < 1 || pos > length(head) + 1) {
        printf("Invalid position\n");
        return head;
    }

    if (pos == 1)
        return insertBegin(head, data);

    struct Node* n = createNode(data);
    struct Node* temp = head;

    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;

    n->next = temp->next;
    temp->next = n;
    return head;
}

/* ==============================
   DELETE OPERATIONS
   ============================== */

struct Node* deleteBegin(struct Node* head) {
    if (!head) return NULL;
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node* deleteEnd(struct Node* head) {
    if (!head || !head->next)
        return deleteBegin(head);

    struct Node* temp = head;
    while (temp->next->next)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
    return head;
}

struct Node* deleteValue(struct Node* head, int key) {
    if (!head) return NULL;

    if (head->data == key)
        return deleteBegin(head);

    struct Node* temp = head;
    while (temp->next && temp->next->data != key)
        temp = temp->next;

    if (temp->next) {
        struct Node* del = temp->next;
        temp->next = del->next;
        free(del);
    } else {
        printf("Value not found\n");
    }
    return head;
}

/* ==============================
   SEARCH
   ============================== */

int search(struct Node* head, int key) {
    int pos = 1;
    while (head) {
        if (head->data == key)
            return pos;
        head = head->next;
        pos++;
    }
    return -1;
}

/* ==============================
   ADVANCED OPERATIONS
   ============================== */

struct Node* reverse(struct Node* head) {
    struct Node *prev = NULL, *curr = head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void sortList(struct Node* head) {
    struct Node *i, *j;
    int temp;
    for (i = head; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int findMiddle(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->data;
}

int nthFromEnd(struct Node* head, int n) {
    struct Node *first = head, *second = head;
    for (int i = 0; i < n; i++)
        first = first->next;

    while (first) {
        first = first->next;
        second = second->next;
    }
    return second->data;
}

int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return 0;
}

void removeDuplicates(struct Node* head) {
    struct Node* curr = head;
    while (curr && curr->next) {
        if (curr->data == curr->next->data) {
            struct Node* temp = curr->next;
            curr->next = temp->next;
            free(temp);
        } else
            curr = curr->next;
    }
}

/* ==============================
   MAIN MENU
   ============================== */

int main() {
    struct Node* head = NULL;
    int choice, data, pos;

    do {
        printf("\n===== SINGLY LINKED LIST LAB =====\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete Beginning\n");
        printf("5. Delete End\n");
        printf("6. Delete Value\n");
        printf("7. Display List\n");
        printf("8. Search\n");
        printf("9. Count Nodes\n");
        printf("10. Reverse List\n");
        printf("11. Sort List\n");
        printf("12. Find Middle\n");
        printf("13. Nth from End\n");
        printf("14. Detect Loop\n");
        printf("15. Remove Duplicates (Sorted)\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                scanf("%d", &data);
                head = insertBegin(head, data);
                break;
            case 2:
                scanf("%d", &data);
                head = insertEnd(head, data);
                break;
            case 3:
                scanf("%d%d", &data, &pos);
                head = insertAtPos(head, data, pos);
                break;
            case 4:
                head = deleteBegin(head);
                break;
            case 5:
                head = deleteEnd(head);
                break;
            case 6:
                scanf("%d", &data);
                head = deleteValue(head, data);
                break;
            case 7:
                display(head);
                break;
            case 8:
                scanf("%d", &data);
                pos = search(head, data);
                printf(pos == -1 ? "Not found\n" : "Found at %d\n", pos);
                break;
            case 9:
                printf("Length = %d\n", length(head));
                break;
            case 10:
                head = reverse(head);
                break;
            case 11:
                sortList(head);
                break;
            case 12:
                printf("Middle = %d\n", findMiddle(head));
                break;
            case 13:
                scanf("%d", &pos);
                printf("Nth from end = %d\n", nthFromEnd(head, pos));
                break;
            case 14:
                printf(detectLoop(head) ? "Loop detected\n" : "No loop\n");
                break;
            case 15:
                removeDuplicates(head);
                break;
        }

    } while (choice != 0);

    return 0;
}
