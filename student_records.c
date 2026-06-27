#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int age;
    char gender[10];
    char course[30];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n=====================================\n");
        printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }
}

void addStudent() {
    FILE *fp = fopen("student.dat", "ab");
    struct Student s;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Gender: ");
    scanf("%s", s.gender);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Record Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("student.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n============================================================\n");
    printf("Roll\tName\t\tAge\tGender\tCourse\t\tMarks\n");
    printf("============================================================\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%-15s%d\t%-8s%-15s%.2f\n",
               s.roll, s.name, s.age, s.gender, s.course, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("student.dat", "rb");
    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found\n");
            printf("-------------------------\n");
            printf("Roll   : %d\n", s.roll);
            printf("Name   : %s\n", s.name);
            printf("Age    : %d\n", s.age);
            printf("Gender : %s\n", s.gender);
            printf("Course : %s\n", s.course);
            printf("Marks  : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("student.dat", "rb+");
    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Gender: ");
            scanf("%s", s.gender);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("\nRecord Updated Successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("student.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}