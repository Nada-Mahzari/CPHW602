'''                                                                             
Q2: Write a Python script that performs the following task:

Write a program that prompts the user to input two integers and outputs the largest.                                                                           
'''

# Prompt the user to input the first integer
first_integer = int(input("Enter the first integer: "))

# Prompt the user to input the second integer
second_integer = int(input("Enter the second integer: "))

# Determine and output the largest integer
if first_integer > second_integer:
    print("The largest integer is:", first_integer)
elif second_integer > first_integer:
    print("The largest integer is:", second_integer)
else:
    print("Both integers are equal.")
