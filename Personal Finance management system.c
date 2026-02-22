#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "finance.dat"
#define CSV_FILE "report.csv"
#define BUDGET_FILE "budget.dat"

struct Transaction {
    int id;
    char type[10];
    char category[20];
    float amount;
    char date[15];
};

int getNextID() {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Transaction t;
    int id = 1;

    if (fp == NULL) return 1;

    while (fread(&t, sizeof(t), 1, fp))
        id = t.id + 1;

    fclose(fp);
    return id;
}

void setBudget() {
    float budget;
    FILE *fp = fopen(BUDGET_FILE, "wb");
    printf("Enter Monthly Budget: ");
    scanf("%f", &budget);
    fwrite(&budget, sizeof(float), 1, fp);
    fclose(fp);
    printf("Budget Set Successfully!\n\n");
}

float getBudget() {
    FILE *fp = fopen(BUDGET_FILE, "rb");
    float budget = 0;
    if (fp == NULL) return 0;
    fread(&budget, sizeof(float), 1, fp);
    fclose(fp);
    return budget;
}

float calculateMonthlyExpense(char month[]) {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Transaction t;
    float expense = 0;

    if (fp == NULL) return 0;

    while (fread(&t, sizeof(t), 1, fp)) {
        if (strcmp(t.type, "Expense") == 0 && strncmp(t.date + 3, month, 2) == 0)
            expense += t.amount;
    }

    fclose(fp);
    return expense;
}

void checkBudgetWarning(char date[]) {
    char month[3];
    strncpy(month, date + 3, 2);
    month[2] = '\0';

    float budget = getBudget();
    if (budget == 0) return;

    float expense = calculateMonthlyExpense(month);

    if (expense > budget)
        printf("Warning: Monthly budget exceeded!\n\n");
}

void addTransaction(char type[]) {
    FILE *fp = fopen(FILE_NAME, "ab");
    struct Transaction t;

    t.id = getNextID();
    strcpy(t.type, type);

    printf("Enter category: ");
    scanf("%s", t.category);

    printf("Enter amount: ");
    scanf("%f", &t.amount);

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", t.date);

    fwrite(&t, sizeof(t), 1, fp);
    fclose(fp);

    if (strcmp(type, "Expense") == 0)
        checkBudgetWarning(t.date);

    printf("Transaction Added Successfully!\n\n");
}

void viewTransactions() {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Transaction t;

    if (fp == NULL) {
        printf("No transactions found.\n\n");
        return;
    }

    printf("\nID | Type | Category | Amount | Date\n");
    printf("-------------------------------------------\n");

    while (fread(&t, sizeof(t), 1, fp)) {
        printf("%d | %s | %s | %.2f | %s\n",
               t.id, t.type, t.category, t.amount, t.date);
    }

    fclose(fp);
    printf("\n");
}

void calculateBalance() {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Transaction t;
    float income = 0, expense = 0;

    if (fp == NULL) {
        printf("No data available.\n\n");
        return;
    }

    while (fread(&t, sizeof(t), 1, fp)) {
        if (strcmp(t.type, "Income") == 0)
            income += t.amount;
        else
            expense += t.amount;
    }

    fclose(fp);

    printf("\nTotal Income: %.2f\n", income);
    printf("Total Expense: %.2f\n", expense);
    printf("Current Balance: %.2f\n\n", income - expense);
}

void monthlyReport() {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Transaction t;
    char month[3];
    float income = 0, expense = 0;

    if (fp == NULL) {
        printf("No data available.\n\n");
        return;
    }

    printf("Enter month (MM): ");
    scanf("%s", month);

    while (fread(&t, sizeof(t), 1, fp)) {
        if (strncmp(t.date + 3, month, 2) == 0) {
            if (strcmp(t.type, "Income") == 0)
                income += t.amount;
            else
                expense += t.amount;
        }
    }

    fclose(fp);

    printf("\nMonthly Income: %.2f\n", income);
    printf("Monthly Expense: %.2f\n", expense);
    printf("Monthly Balance: %.2f\n\n", income - expense);
}

void exportCSV() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *csv = fopen(CSV_FILE, "w");
    struct Transaction t;

    if (fp == NULL) {
        printf("No data to export.\n\n");
        return;
    }

    fprintf(csv, "ID,Type,Category,Amount,Date\n");

    while (fread(&t, sizeof(t), 1, fp)) {
        fprintf(csv, "%d,%s,%s,%.2f,%s\n",
                t.id, t.type, t.category, t.amount, t.date);
    }

    fclose(fp);
    fclose(csv);

    printf("Data exported to report.csv successfully!\n\n");
}

int main() {
    int choice;

    while (1) {
        printf("===== Personal Finance Manager =====\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View Transactions\n");
        printf("4. View Balance\n");
        printf("5. Monthly Report\n");
        printf("6. Set Monthly Budget\n");
        printf("7. Export CSV\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction("Income");
                break;
            case 2:
                addTransaction("Expense");
                break;
            case 3:
                viewTransactions();
                break;
            case 4:
                calculateBalance();
                break;
            case 5:
                monthlyReport();
                break;
            case 6:
                setBudget();
                break;
            case 7:
                exportCSV();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n\n");
        }
    }

    return 0;
}
