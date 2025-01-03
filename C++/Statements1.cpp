
/*
Write a Python script that performs the following tasks:
The marks obtained by a student in 3 different subjects are input by the user. Your
program should calculate the average of subjects and display the grade. The student gets a
grade as per the following rules:
Average Grade
90-100 A
80-89 B
70-79 C
60-69 D
0-59 F
*/


#include <iostream>
using namespace std;

int Statements1() {

    float mark1, mark2, mark3, average;
    char grade;


    cout << "Enter the marks for subject 1: ";
    cin >> mark1;
    cout << "Enter the marks for subject 2: ";
    cin >> mark2;
    cout << "Enter the marks for subject 3: ";
    cin >> mark3;


    average = (mark1 + mark2 + mark3) / 3;


    if (average >= 90 && average <= 100) {
        grade = 'A';
    } else if (average >= 80 && average < 90) {
        grade = 'B';
    } else if (average >= 70 && average < 80) {
        grade = 'C';
    } else if (average >= 60 && average < 70) {
        grade = 'D';
    } else if (average >= 0 && average < 60) {
        grade = 'F';
    } else {
        cout << "Invalid marks entered. Please ensure marks are within 0-100." << endl;
        return 1;
    }

   
    cout << "The average marks are: " << average << endl;
    cout << "The grade is: " << grade << endl;

    return 0;
}

int main() {
    return Statements1();
}
