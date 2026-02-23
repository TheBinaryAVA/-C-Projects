#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float value;
} Record;

/* -------- TEXT FILE WRITE USING fprintf -------- */
void writeFormatted() {
    FILE *fp = fopen("data.txt", "w");
    int id;
    char name[50];
    float value;

    printf("Enter id name value: ");
    scanf("%d %s %f", &id, name, &value);

    fprintf(fp, "%d %s %.2f\n", id, name, value);
    fclose(fp);

    printf("Written using fprintf.\n");
}

/* -------- TEXT FILE WRITE USING fputs -------- */
void writeString() {
    FILE *fp = fopen("data.txt", "a");
    char line[200];
    getchar();
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    fputs(line, fp);
    fclose(fp);

    printf("Written using fputs.\n");
}

/* -------- WRITE CHARACTER -------- */
void writeChar() {
    FILE *fp = fopen("data.txt", "a");
    char ch;
    printf("Enter character: ");
    scanf(" %c", &ch);

    fputc(ch, fp);
    fputc('\n', fp);

    fclose(fp);
    printf("Character written.\n");
}

/* -------- READ USING fscanf -------- */
void readFormatted() {
    FILE *fp = fopen("data.txt", "r");
    int id;
    char name[50];
    float value;

    while(fscanf(fp, "%d %s %f", &id, name, &value) != EOF) {
        printf("%d %s %.2f\n", id, name, value);
    }

    fclose(fp);
}

/* -------- READ USING fgets -------- */
void readLines() {
    FILE *fp = fopen("data.txt", "r");
    char line[200];

    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

/* -------- READ USING fgetc -------- */
void readCharByChar() {
    FILE *fp = fopen("data.txt", "r");
    char ch;

    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }

    fclose(fp);
}

/* -------- BINARY WRITE -------- */
void writeBinary() {
    FILE *fp = fopen("data.dat", "wb");
    Record r;

    printf("Enter id name value: ");
    scanf("%d %s %f", &r.id, r.name, &r.value);

    fwrite(&r, sizeof(Record), 1, fp);
    fclose(fp);

    printf("Binary record written.\n");
}

/* -------- BINARY READ -------- */
void readBinary() {
    FILE *fp = fopen("data.dat", "rb");
    Record r;

    while(fread(&r, sizeof(Record), 1, fp)) {
        printf("%d %s %.2f\n", r.id, r.name, r.value);
    }

    fclose(fp);
}

/* -------- RANDOM ACCESS -------- */
void randomAccess() {
    FILE *fp = fopen("data.dat", "rb");
    int index;
    Record r;

    printf("Enter record index (starting from 0): ");
    scanf("%d", &index);

    fseek(fp, index * sizeof(Record), SEEK_SET);
    fread(&r, sizeof(Record), 1, fp);

    printf("Record: %d %s %.2f\n", r.id, r.name, r.value);

    fclose(fp);
}

/* -------- FILE SIZE -------- */
void fileSize() {
    FILE *fp = fopen("data.txt", "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    printf("File size: %ld bytes\n", size);
    fclose(fp);
}

/* -------- REVERSE DISPLAY -------- */
void reverseFile() {
    FILE *fp = fopen("data.txt", "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    for(long i = size - 1; i >= 0; i--) {
        fseek(fp, i, SEEK_SET);
        printf("%c", fgetc(fp));
    }

    fclose(fp);
}

/* -------- COPY FILE -------- */
void copyFile() {
    FILE *src = fopen("data.txt", "r");
    FILE *dest = fopen("copy.txt", "w");
    char ch;

    while((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
}

/* -------- MAIN -------- */
int main() {
    int choice;

    while(1) {
        printf("\n==== FILE MANAGEMENT SYSTEM ====\n");
        printf("1. Write (fprintf)\n");
        printf("2. Write (fputs)\n");
        printf("3. Write (fputc)\n");
        printf("4. Read (fscanf)\n");
        printf("5. Read (fgets)\n");
        printf("6. Read (fgetc)\n");
        printf("7. Binary Write\n");
        printf("8. Binary Read\n");
        printf("9. Random Access\n");
        printf("10. File Size\n");
        printf("11. Reverse File\n");
        printf("12. Copy File\n");
        printf("13. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: writeFormatted(); break;
            case 2: writeString(); break;
            case 3: writeChar(); break;
            case 4: readFormatted(); break;
            case 5: readLines(); break;
            case 6: readCharByChar(); break;
            case 7: writeBinary(); break;
            case 8: readBinary(); break;
            case 9: randomAccess(); break;
            case 10: fileSize(); break;
            case 11: reverseFile(); break;
            case 12: copyFile(); break;
            case 13: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
