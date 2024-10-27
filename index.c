#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "./color.h"

#define TOTAL_SUBJCT 5 //number of subject
#define MAX_STUDENTS 100 // maximum number of accepted student


//! ============================= DATA STRUCTURE ============================= //


//subject info
typedef struct subject_data {
    ////  "Bangla","English","Math","ICT", "Science" };
    int     marks[TOTAL_SUBJCT];    //all marks of each student
    float   gpa[TOTAL_SUBJCT];      //all gpa of each student
    char    grade[TOTAL_SUBJCT][3]; //All grade list of each student
}subject_data;



// basic info - personal info
typedef struct student_data {
    char    name[50];
    char    id[10];
    float   gpa;
    char    grade[5]; //A+ ,A,A-,B,C,D,F
    char    date_of_birth[10]; //dd:mm:yy
    subject_data subjects; //linked with //* subject_data
}student;



// subject name

char subject_name[TOTAL_SUBJCT][10] = { "Bangla","English","Math","ICT", "Science" };




//! ============================= FUNCTION DEFINE ============================= //

void display_selectMenu_content();  //display select menu texts  or contents

int     inputData(student students[], int n);
void    printData(student students[], int n);




//! ============================= MAIN FUNCTION ============================= //


int main(void) {

    student students[MAX_STUDENTS]; // Array to store students
    int student_count = 0;



    while (1) {
        display_selectMenu_content();   //display select menu texts  or contents

        int select_menu;
        scanf("%d", &select_menu);

        switch (select_menu) {
        case 1:
            student_count = inputData(students, student_count);
            break;

        case 2:
            if (student_count > 0) {
                printData(students, student_count); // Print data if students are present
            }
            else {
                printf("No student data available to display.\n");
            }
            break;

        case 3:
            printf("Exiting the program.\n");
            return 0; // Exit the program

        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    }



    return 0;
}





//! ============================= FUNCTION ============================= //

//TODO: select menu

//* display_selectMenu_content();  //display select menu texts  or contents

void display_selectMenu_content() {

    printf("%s", RED);
    printf("\n\n");

    printf("GRADE SHEET MAKE AND PRINT");
    printf("\n=================================================\n\n");

    printf("\t1.\tEnter Student Data\n");
    printf("\t2.\tPrint Student Data\n");
    printf("\t3.\tExit\n");

    printf("\n");
    printf("%s", YELLOW);
    printf("Enter your choice: ");
    printf("%s", RESET);
}




//TODO:: Taking input student data

int inputData(student students[], int n) {

    //current page
    printf("\n\n%s", RED);
    printf(">> INPUT");
    printf("\n=================================================\n\n");
    printf("%s", RESET);


    int N;
    printf("  *  Enter the number of students to input (max %d): ", MAX_STUDENTS - n);
    scanf("%d", &N);

    // Check if number of students exceeds the maximum limit
    if (N > MAX_STUDENTS - n) {
        printf("%s", RED_BG);
        printf("\n  !  Number of students exceeds the maximum limit of %d.", MAX_STUDENTS);
        printf("%s\n\n", RESET);

        main(); //go back to main
    }

    // Data entry for each student
    for (int i = 0; i < N; i++) {

        printf("%s\n", BLUE); //!text color

        printf("\n\tStudent %d", n + i + 1);
        printf("\n\t-----------------------------------------\n");


        printf("%s", YELLOW); //!text color

        //input promts
        printf("\n");
        printf("\t1. Enter name\t:\t");
        getchar();
        fgets(students[n + i].name, sizeof(students[n + i].name), stdin);
        students[n + i].name[strcspn(students[n + i].name, "\n")] = '\0'; // Remove newline

        printf("\t2. Enter ID\t:\t");
        scanf("%s", students[n + i].id);

        printf("\t3. Enter date of birth (dd:mm:yy): ");
        scanf("%s", students[n + i].date_of_birth);


        //subjects details
        printf("\n");
        printf("%s", BLUE); //!text color
        printf("\t4. Markes\n");

        printf("%s", YELLOW); //!text color
        for (int j = 0; j < TOTAL_SUBJCT; j++) {
            printf("\t%s\t:\t", subject_name[j]);
            scanf("%d", &students[n + i].subjects.marks[j]);

            // GPA and grade can be calculated here if desired
            // students[n + i].subjects.gpa[j] = calculateGPA(students[n + i].subjects.marks[j]);
            // strcpy(students[n + i].subjects.grade[j], calculateGrade(students[n + i].subjects.gpa[j]));
        }
        printf("%s", RESET); //!color reset

        // Calculate overall GPA and grade if desired
    }
    printf("%s", RESET); //!color reset
    return n + N;
    // main();
}



// Printing or outputing student data
void printData(student students[], int n) {

    //current page
    printf("\n\n%s", RED);
    printf(">> Output");
    printf("\n=================================================\n\n");
    printf("%s", RESET);


    for (int i = 0; i < n; i++) {
        printf("Name: %s\n", students[i].name);
        printf("ID: %s\n", students[i].id);
        printf("Date of Birth: %s\n", students[i].date_of_birth);

        printf("Marks:\n");
        for (int j = 0; j < TOTAL_SUBJCT; j++) {
            printf("  %s: %d\n", subject_name[j], students[i].subjects.marks[j]);
        }
        printf("\n");
    }
}