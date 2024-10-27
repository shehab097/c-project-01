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
}student