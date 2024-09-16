'''                                                                            Q3: Write a Python script that uses the math library to perform the following c
alculations:                                                                   ''' 

'''                                                                              
1. Calculate the Area of a Circle:                                              
                                     
A. Write a function named circle_area(radius) that takes the radius of a circle as input and returns the area of the circle. Use the formula area = math.pi * radius**2.
'''
'''
import math

def circle_area(radius):

 area = math.pi * radius**2
 return area
radius = float(input("Enter the radius of the circle: "))
area = circle_area(radius)
print(f"The area of the circle with radius {radius} is {area:.2f}")
'''


'''
2. Calculate the Volume of a Sphere:

Write a function named sphere_volume(radius) that takes the radius of a sphere as input and returns the volume of the sphere. Use the formula volume = (4/3) * math.pi * radius**3.

import math
def sphere_volume(radius):
  volume = (4/3) * math.pi * radius**3
  return volume
radius = float(input("Enter the radius of the sphere: "))
volume = sphere_volume(radius)
print(f"The volume of the sphere with radius {radius} is {volume:.2f}")
'''
'''
3. Main Script:
A. Prompt the user to enter the radius of a circle and a sphere.
B. Use the circle_area and sphere_volume functions to calculate the area and volume, respectively.
C. Print the results with appropriate labels.

Ensure that the script correctly performs these calculations and handles user input.
'''
'''
import math
def circle_area(radius):
    return math.pi * radius ** 2
def sphere_volume(radius):
    return (4/3) * math.pi * radius ** 3
def main():
    circle_radius =float(input("Enter the radius of the circle: "))
    sphere_radius = float(input("Enter the radius of the sphere"))
    circle_area_result = circle_area(circle_radius)
    sphere_volume_result = sphere_volume(sphere_radius)
    print(f"\nThe area of the circle with radius")
    print(f"The volume of the sphere with radius")
    main()
'''
import math
def circle_area(radius):
    return math.pi * radius ** 2
def sphere_volume(radius):
    return (4/3) * math.pi * radius ** 3
def main():
    circle_radius = float(input("Enter the radius of the circle: ")) 
    sphere_radius = float(input("Enter the radius of the sphere: ")) 
    circle_area_result = circle_area(circle_radius)
    sphere_volume_result = sphere_volume(sphere_radius)
    print(f"\nThe area of the circle with radius {circle_radius} is: {circle_area_result:.2f}")
    print(f"The volume of the sphere with radius {sphere_radius} is: {sphere_volume_result:.2f}")

if __name__ == "__main__":
    main()
