/*
==========================================================
 Mini In-Memory File System in C
 Pointer-Based Tree Implementation
 Author: Your Name
==========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= Node Structure ================= */

typedef struct Node {
    char name[50];
    int isFile;
    char *content;

    struct Node *parent;
    struct Node *child;
    struct Node *sibling;
} Node;

/* ================= Function Prototypes ================= */

Node* createNode(const char *name, int isFile, Node *parent);
void addChild(Node *parent, Node *child);
Node* findChild(Node *parent, const char *name);
void list(Node *current);
void printTree(Node *node, int depth);
void writeFile(Node *file);
void deleteNode(Node *node);
void removeChild(Node *parent, const char *name);

/* ================= Node Creation ================= */

Node* createNode(const char *name, int isFile, Node *parent) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strcpy(newNode->name, name);
    newNode->isFile = isFile;
    newNode->content = NULL;
    newNode->parent = parent;
    newNode->child = NULL;
    newNode->sibling = NULL;

    return newNode;
}

/* ================= Add Child ================= */

void addChild(Node *parent, Node *child) {
    if (!parent->child) {
        parent->child = child;
    } else {
        Node *temp = parent->child;
        while (temp->sibling)
            temp = temp->sibling;
        temp->sibling = child;
    }
}

/* ================= Find Child ================= */

Node* findChild(Node *parent, const char *name) {
    Node *temp = parent->child;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }
    return NULL;
}

/* ================= List Directory ================= */

void list(Node *current) {
    Node *temp = current->child;
    while (temp) {
        printf("%s%s\n", temp->name, temp->isFile ? "" : "/");
        temp = temp->sibling;
    }
}

/* ================= Tree View (Recursive) ================= */

void printTree(Node *node, int depth) {
    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%s%s\n", node->name, node->isFile ? "" : "/");

    Node *child = node->child;
    while (child) {
        printTree(child, depth + 1);
        child = child->sibling;
    }
}

/* ================= Write File ================= */

void writeFile(Node *file) {
    if (!file || !file->isFile) {
        printf("Not a valid file\n");
        return;
    }

    char buffer[256];

    printf("Enter file content: ");
    getchar(); // clear newline
    fgets(buffer, sizeof(buffer), stdin);

    if (file->content)
        free(file->content);

    file->content = (char*)malloc(strlen(buffer) + 1);
    strcpy(file->content, buffer);
}

/* ================= Remove Child ================= */

void removeChild(Node *parent, const char *name) {
    Node *prev = NULL;
    Node *curr = parent->child;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {

            if (prev)
                prev->sibling = curr->sibling;
            else
                parent->child = curr->sibling;

            deleteNode(curr);
            return;
        }
        prev = curr;
        curr = curr->sibling;
    }

    printf("File/Directory not found\n");
}

/* ================= Recursive Delete ================= */

void deleteNode(Node *node) {
    if (!node) return;

    Node *child = node->child;
    while (child) {
        Node *next = child->sibling;
        deleteNode(child);
        child = next;
    }

    if (node->content)
        free(node->content);

    free(node);
}

/* ================= Function Pointer Command System ================= */

typedef void (*CommandHandler)(Node **current, Node *root);

void cmd_ls(Node **current, Node *root) { list(*current); }
void cmd_tree(Node **current, Node *root) { printTree(root, 0); }

void cmd_mkdir(Node **current, Node *root) {
    char name[50];
    scanf("%s", name);
    addChild(*current, createNode(name, 0, *current));
}

void cmd_touch(Node **current, Node *root) {
    char name[50];
    scanf("%s", name);
    addChild(*current, createNode(name, 1, *current));
}

void cmd_cd(Node **current, Node *root) {
    char name[50];
    scanf("%s", name);

    if (strcmp(name, "..") == 0) {
        if ((*current)->parent)
            *current = (*current)->parent;
        return;
    }

    Node *next = findChild(*current, name);
    if (next && !next->isFile)
        *current = next;
    else
        printf("Directory not found\n");
}

void cmd_write(Node **current, Node *root) {
    char name[50];
    scanf("%s", name);

    Node *file = findChild(*current, name);
    if (file)
        writeFile(file);
    else
        printf("File not found\n");
}

void cmd_rm(Node **current, Node *root) {
    char name[50];
    scanf("%s", name);
    removeChild(*current, name);
}

/* ================= Main ================= */

int main() {

    Node *root = createNode("root", 0, NULL);
    Node *current = root;

    char command[50];

    printf("Mini In-Memory File System\n");
    printf("Commands: mkdir, touch, ls, cd, tree, write, rm, exit\n");

    while (1) {
        printf(">> ");
        scanf("%s", command);

        if (strcmp(command, "exit") == 0)
            break;

        /* Command Dispatch Table */
        if (strcmp(command, "ls") == 0) cmd_ls(&current, root);
        else if (strcmp(command, "tree") == 0) cmd_tree(&current, root);
        else if (strcmp(command, "mkdir") == 0) cmd_mkdir(&current, root);
        else if (strcmp(command, "touch") == 0) cmd_touch(&current, root);
        else if (strcmp(command, "cd") == 0) cmd_cd(&current, root);
        else if (strcmp(command, "write") == 0) cmd_write(&current, root);
        else if (strcmp(command, "rm") == 0) cmd_rm(&current, root);
        else printf("Unknown command\n");
    }

    deleteNode(root);
    return 0;
}
