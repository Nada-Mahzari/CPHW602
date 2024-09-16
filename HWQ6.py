'''
Write a Python script that defines and uses the following functions:         
1. is_even(n): A function that takes an integer n and returns True if the number is even, and False otherwise.
'''
'''
def is_even(n):
    return n % 2 == 0
number = int(input("Enter an integer: "))
if is_even(number):
    print(f"The number {number} is even.")
else:
    print(f"The number {number} is odd.")
'''
'''
2. main(): A function that prompts the user to enter an integer and then:      
A. Checks if the number is even using is_even(n) and prints "The number is even." if the function returns True.                                               B. If the function returns False, print "The number is odd."                   Call the main() function to run the script.
'''
def is_even(n):
    return n % 2 == 0

def main():

    number = int(input("Enter an integer: "))
    
    
    if is_even(number):
        print(f"The number {number} is even.")
    else:
        print(f"The number {number} is odd.")
main()

