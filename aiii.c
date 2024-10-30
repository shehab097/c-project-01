#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "./color.h"

#define TOTAL_SUBJCT 5 //number of subject
#define MAX_STUDENTS 100 // maximum number of accepted student
int student_count = 0;

//! ============================= DATA STRUCTURE ============================= //

typedef struct student_data {
    // basic info - personal info
    char    name[50];
    char    id[10];
    char    date_of_birth[10]; //dd:mm:yy
    int     total_marks;
    float   total_gpa;


    //subject info
    int     marks[TOTAL_SUBJCT];    //all marks of each student
    float   gpa[TOTAL_SUBJCT];      //all gpa of each student
    char    grade[TOTAL_SUBJCT][3]; //All grade list of each student
}student;




//! ============================= FUNCTION DEFINE ============================= //

void display_selectMenu_content();  //display select menu texts  or contents

void    inputData(student students[], int n);
void    printData(student students[], int n);
float   calculateGPA(int); //gpa calculate
char* calculateGrade(int score);   //Grade calculate
void closePrompt(); //close prompt

char subject_name[TOTAL_SUBJCT][10] = { "Bangla","English","Math","ICT", "Science" };


//! ============================= MAIN FUNCTION ============================= //
int main() {
    system("cls");
    student students[MAX_STUDENTS];

    while (1) {
        display_selectMenu_content();   //display select menu texts  or contents

        int select_menu;
        scanf("%d", &select_menu);

        switch (select_menu) {
        case 1:
            inputData(students, student_count);
            closePrompt();
            break;

        case 2:
            if (student_count > 0) {
                printData(students, student_count);
            }
            else {
                printf("No student data available to display.\n");
            }
            closePrompt();
            break;

        case 0:
            printf("Exiting the program.\n");
            closePrompt();
            return 0; // Exit the program

        default:
            printf("Invalid choice. Please select a valid option.\n");
            closePrompt();
            break;
        }
    }



    return 0;
}


//! ============================= FUNCTION ============================= //
//display select menu texts  or contents
void display_selectMenu_content() {

    printf("%s", RED);
    printf("\n\n");

    printf("GRADE SHEET MAKE AND PRINT");
    printf("\n=================================================\n\n");

    printf("\t1.\tEnter Student Data\n");
    printf("\t2.\tPrint Student Data\n");
    printf("\t0.\tExit\n");

    printf("\n");
    printf("%s", YELLOW);
    printf("Enter your choice: ");
    printf("%s", RESET);
}



//input data
void inputData(student students[], int n) {
    printf("\n\n%s>> INPUT\n", RED);
    printf("=================================================\n\n%s", RESET);

    int new_students;
    printf("  *  Enter the number of students to input (max %d): ", MAX_STUDENTS - n);
    scanf("%d", &new_students);
    getchar(); // Clear newline left by scanf

    if (new_students + n > MAX_STUDENTS) {
        printf("%s\n  !  Number of students exceeds the maximum limit of %d.\n%s", RED_BG, MAX_STUDENTS, RESET);
        return;
    }

    for (int i = n; i < n + new_students; i++) {
        printf("%s", BLUE);
        printf("\n*\tInput student %d Data:\n", i + 1);

        printf("%s", YELLOW);
        printf("\n\t1. Enter Name\t: ");
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0; // Remove newline

        printf("\n\t2. Enter ID\t: ");
        scanf("%s", students[i].id);
        getchar(); // Clear newline left by scanf

        printf("\n\t3. Date of birth (dd/mm/yyyy): ");
        scanf("%s", students[i].date_of_birth);
        getchar(); // Clear newline left by scanf

        //subjectwise marks input
        printf("%s", BLUE);
        printf("\n\t4. Enter subjectwise marks: \n");
        printf("%s", YELLOW);

        //totall marks
        int total_marks = 0;
        float total_gpa = 0.0;
        int fail = 0;



        for (int j = 0;j < TOTAL_SUBJCT;j++) {

            //input marks
            printf("\n\t%s\t :: ", subject_name[j]);
            scanf("%d", &students[i].marks[j]);


            // update gpa 
            students[i].gpa[j] = calculateGPA(students[i].marks[j]);


            //update grade point
            char* grade = calculateGrade(students[i].marks[j]);
            strcpy(students[i].grade[j], grade);


            total_marks += students[i].marks[j];
            total_gpa += students[i].gpa[j];
            if (students[i].gpa[j] == 0) fail++;

            students[i].total_marks = total_marks;
            students[i].total_gpa = total_gpa / TOTAL_SUBJCT;
        }
        if (fail) {
            students[i].total_gpa = 0.0;
        }

        getchar();
        printf("%s", RESET);
        printf("\n\n\n");
    }

    student_count += new_students; // Update the total student count
    printf("Data input completed.\n");

}





// Printing data

void printData(student students[], int n) {
    printf("\n\n%s>> STUDENT DATA\n", RED);
    printf("=================================================\n\n%s", RESET);

    for (int i = 0; i < n; i++) {
        printf("%s", YELLOW);

        printf("%s", BLUE_BG);
        printf("Student %d Data:", i + 1);
        printf("%s", RESET);
        printf("\n\n");

        printf("1. Name\t: %s\n", students[i].name);
        printf("2. ID\t: %s\n", students[i].id);
        printf("3. Date of Birth: %s\n", students[i].date_of_birth);

        // Display marks, GPA, and grades if available

        printf("%s", BLUE);
        printf("\nMARKS: \n");
        printf("%s", BLUE);

        printf("%-10s %-10s %-10s %-10s\n", "Subject", "Marks", "GPA", "Grade");  // Column headers with fixed widths

        printf("%s", YELLOW);
        for (int j = 0; j < TOTAL_SUBJCT; j++) {
            printf("%-10s %-10d %-10.2f %-10s\n", subject_name[j], students[i].marks[j], students[i].gpa[j], students[i].grade[j]);
        }

        printf("\n");
        printf("\nTotal Marks\t: %d", students[i].total_marks);
        printf("\nGPA\t: %.2f", students[i].total_gpa);


        printf("%s", RESET);
        printf("\n\n");
    }
}

// alculate grade point GPA
float calculateGPA(int score) {
    if (score <= 100 && score >= 0) {
        if (score >= 80 && score <= 100) {
            return 5.0;
        }
        else if (score >= 70 && score < 80) {
            return 4.0;
        }
        else if (score >= 60 && score < 70) {
            return 3.5;
        }
        else if (score >= 50 && score < 60) {
            return 3.0;
        }
        else if (score >= 40 && score < 50) {
            return 2.0;
        }
        else if (score >= 33 && score < 40) {
            return 1.0;
        }
        else {
            return 0.0;
        }
    }
    else {
        return -1.0;
    }
}

// 
char* calculateGrade(int score) {
    if (score >= 80 && score <= 100) {
        return "A+";
    }
    else if (score >= 70 && score < 80) {
        return "A";
    }
    else if (score >= 60 && score < 70) {
        return "A-";
    }
    else if (score >= 50 && score < 60) {
        return "B";
    }
    else if (score >= 40 && score < 50) {
        return "C";
    }
    else if (score >= 33 && score < 40) {
        return "D";
    }
    else {
        return "F";
    }
}

// closePrompt
void closePrompt() {
    printf("\nPress any key to close\n\n");
    getch();

    int i = 3;
    while (i--) {
        // sleep(1);
        printf("%d.. ", i);
    }
    // sleep(2);
    system("cls");
}

