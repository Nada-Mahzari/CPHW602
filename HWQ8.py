'''
Write a Python script that performs the following tasks:                        
                                                                                
1. Read Data:                                                                
Write a function named read_from_file(filename) that takes a filename as input 
and reads the contents of the file. The function should return a list of strin
s, where each string represents a line from the file.                          '''
'''
def read_from_file(filename):
    with open(filename, 'r') as file:  
        lines = file.readlines() 
        return [line.strip() for line in lines]  
fruits = read_from_file('fruits.txt')
print(fruits)
''' 
'''
2. Main Script:                                                                A. Use the read_from_file("fruits.txt") function to read the contents of a file named "fruits.txt", which contains a list of fruits, each on a new line.      B. Print each fruit to the console.                                            Make sure the script correctly reads and prints the contents of the "fruits.txt" file.
'''

def read_from_file(filename):
    with open(filename, 'r') as file:  
        lines = file.readlines()  
        return [line.strip() for line in lines]  


def main():
    # A.
    fruits = read_from_file("fruits.txt")

    # B.
    print("Fruits in the file:")
    for fruit in fruits:
        print(fruit)


if __name__ == "__main__":
    main()

