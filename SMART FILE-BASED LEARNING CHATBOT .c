#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_Q 200
#define MAX_A 300

typedef struct {
    char question[MAX_Q];
    char answer[MAX_A];
} Knowledge;

/* ---------------- Utility Functions ---------------- */

void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

/* ---------------- Save to Text File ---------------- */

void saveToText(Knowledge k) {
    FILE *fp = fopen("knowledge.txt", "a");
    if(fp == NULL) return;

    fprintf(fp, "%s|%s\n", k.question, k.answer);
    fclose(fp);
}

/* ---------------- Save to Binary File ---------------- */

void saveToBinary(Knowledge k) {
    FILE *fp = fopen("knowledge.dat", "ab");
    if(fp == NULL) return;

    fwrite(&k, sizeof(Knowledge), 1, fp);
    fclose(fp);
}

/* ---------------- Search in Text File ---------------- */

int searchAnswer(char *userQuestion, char *foundAnswer) {
    FILE *fp = fopen("knowledge.txt", "r");
    if(fp == NULL) return 0;

    char line[600];
    char q[MAX_Q], a[MAX_A];

    char tempUser[MAX_Q];
    strcpy(tempUser, userQuestion);
    toLowerCase(tempUser);

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^\n]", q, a);

        char tempQ[MAX_Q];
        strcpy(tempQ, q);
        toLowerCase(tempQ);

        if(strcmp(tempQ, tempUser) == 0) {
            strcpy(foundAnswer, a);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ---------------- Log Conversation ---------------- */

void logConversation(char *user, char *bot) {
    FILE *fp = fopen("history.txt", "a");
    if(fp == NULL) return;

    fputs("User: ", fp);
    fputs(user, fp);
    fputc('\n', fp);

    fputs("Bot: ", fp);
    fputs(bot, fp);
    fputc('\n', fp);

    fclose(fp);
}

/* ---------------- Reverse History Viewer ---------------- */

void showHistoryReverse() {
    FILE *fp = fopen("history.txt", "r");
    if(fp == NULL) {
        printf("No history available.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    printf("\n--- Conversation History (Reverse) ---\n");

    for(long i = size - 1; i >= 0; i--) {
        fseek(fp, i, SEEK_SET);
        char ch = fgetc(fp);
        printf("%c", ch);
    }

    printf("\n");
    fclose(fp);
}

/* ---------------- Show Knowledge Stats ---------------- */

void showKnowledgeStats() {
    FILE *fp = fopen("knowledge.dat", "rb");
    if(fp == NULL) {
        printf("No knowledge stored yet.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    int count = size / sizeof(Knowledge);

    printf("\nTotal Knowledge Entries: %d\n", count);

    Knowledge k;
    int index = 0;

    while(fread(&k, sizeof(Knowledge), 1, fp)) {
        printf("%d. %s\n", ++index, k.question);
    }

    fclose(fp);
}

/* ---------------- Main Chatbot ---------------- */

int main() {
    int choice;
    char userInput[MAX_Q];
    char botResponse[MAX_A];

    while(1) {
        printf("\n==== SMART FILE CHATBOT ====\n");
        printf("1. Ask Question\n");
        printf("2. Show Knowledge Stats\n");
        printf("3. View Conversation History (Reverse)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if(choice == 1) {

            printf("You: ");
            fgets(userInput, sizeof(userInput), stdin);
            removeNewline(userInput);

            if(searchAnswer(userInput, botResponse)) {
                printf("Bot: %s\n", botResponse);
            } else {
                printf("Bot: I don't know. Teach me!\n");
                printf("Enter answer: ");
                fgets(botResponse, sizeof(botResponse), stdin);
                removeNewline(botResponse);

                Knowledge k;
                strcpy(k.question, userInput);
                strcpy(k.answer, botResponse);

                saveToText(k);
                saveToBinary(k);

                printf("Bot: Thanks! I've learned something new.\n");
            }

            logConversation(userInput, botResponse);
        }

        else if(choice == 2) {
            showKnowledgeStats();
        }

        else if(choice == 3) {
            showHistoryReverse();
        }

        else if(choice == 4) {
            printf("Goodbye!\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
