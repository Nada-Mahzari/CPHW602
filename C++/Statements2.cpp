/*
Q2: Write a Python script that performs the following task:

Write a program that prompts the user to input two integers and outputs the largest.
*/

void Statements2(){
  int num1, num2;
  cout << "Enter the first integer: ";
  cin >> num1;
  cout << "Enter the second integer: ";
  cin >> num2;
  int largest = max(num1, num2);
      cout << "The largest number is: " << largest << endl;
}
