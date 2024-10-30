typedef struct student_data {
    // basic info - personal info
    char    name[50];
    char    id[10];
    // float   gpa;
    // char    grade[5]; //A+ ,A,A-,B,C,D,F
    char    date_of_birth[10]; //dd:mm:yy

    //subject info
    int     marks[TOTAL_SUBJCT];    //all marks of each student
    float   gpa[TOTAL_SUBJCT];      //all gpa of each student
    char    grade[TOTAL_SUBJCT][3]; //All grade list of each student
}student;