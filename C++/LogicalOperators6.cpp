/*
Write a Python script that defines and uses the following functions:

1. is_even(n): A function that takes an integer n and returns True if the number is even, and False otherwise.

2. main(): A function that prompts the user to enter an integer and then:

A. Checks if the number is even using is_even(n) and prints "The number is even." if the function returns True.
B. If the function returns False, print "The number is odd."

Call the main() function to run the script.
*/


void LogicalOperators6(){

  int num;
  cout << "Enter an integer: ";
    cin >> num;

  int numb = num % 2;
  if (num >0 && numb == 0){
    std::cout<< "The number is positive and even "<< num <<std::endl; 
  } else {
    std::cout<< "The number is positive and odd "<< num <<std::endl;
  }

}
