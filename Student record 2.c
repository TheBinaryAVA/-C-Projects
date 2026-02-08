#include<stdio.h>
#include<string.h>
struct Address{
    int pin;
    char city[20];

};
struct Student{
    int id;
    char name[20];
    float marks;
    struct Address addr;
};
void addstudent(struct Student *s,int *n){
    pritnf("Enter student id,name,marks,pin and city:\n");
    scanf("%d %s %f %d %s",&s[*n].roll,&s[*n].name,&s[*n].marks,&s[*n].addr.pin,s[*n].addr.city);
    (*n)++;
}
void displaystudents(struct Student *s,int n){
    for(int i=0;i<n;i++){
        printf("Student %d:\n",i+1);
        printf("ID: %d\n",s[i].id);
        printf("Name: %s\n",s[i].name);
        printf("Marks: %.2f\n",s[i].marks);
        printf("Address: %d, %s\n",s[i].addr.pin,s[i].addr.city);
    }
}
void searchstudent(struct Student *s,int n,int id){
    for(int i=0;i<n;i++){
        if(s[i].id==id){
            printf("Student found:\n");
            printf("ID: %d\n",s[i].id);
            printf("Name: %s\n",s[i].name);
            printf("Marks: %.2f\n",s[i].marks);
            printf("Address: %d, %s\n",s[i].addr.pin,s[i].addr.city);
            return;
        }
    }
    printf("Student not found.\n");
}
void updateMarks(struct Student *ptr, int n) {
    int roll;
    printf("\nEnter roll to update marks: ");
    scanf("%d", &roll);

    for (int i = 0; i < n; i++) {
        if ((ptr + i)->roll == roll) {
            printf("Enter new marks: ");
            scanf("%f", &(ptr + i)->marks);
            printf("Marks updated!\n");
            return;
        }
    }
    printf("\nStudent not found.\n");
}

void backupRecord(struct Student *ptr) {
    struct Student backup;
    backup = *ptr;   // ⭐ AGGREGATE OPERATION
    printf("\nFirst student backed up successfully!");
}

int main() {
    struct Student s[50];     // array of structures
    struct Student *ptr = s; // pointer to structure
    int n = 0, choice;

    while (1) {
        printf("\n\n--- STUDENT MANAGEMENT SYSTEM ---");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Marks");
        printf("\n5. Backup First Record");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(ptr, &n); break;
            case 2: displayStudents(ptr, n); break;
            case 3: searchStudent(ptr, n); break;
            case 4: updateMarks(ptr, n); break;
            case 5: backupRecord(ptr); break;
            case 6: return 0;
            default: printf("\nInvalid choice!");
        }
    }
}