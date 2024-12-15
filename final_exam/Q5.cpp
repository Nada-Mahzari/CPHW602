/*
  Question-5 (S(CLO 2.4))-10points:
Convert the following Python two codes into an equivalent C++ program that performs the same operations.


Question-5a: 

n = [1,2,3,4,5,6,7,8]
sum_even=0
sum_odd=0
count_even=0
count_odd=0
for i in n:
    if i % 2 ==0:
       sum_even += i
       count_even +=1
    else:
        sum_odd += i
        count_odd += 1

print("the total number of even:",sum_even)
print("how many even number:",count_even)
print("the total number of odd:",sum_odd)
print("how many odd number:",count_odd)
*/
/*
void Q5(){
   
    vector<int> n = {1, 2, 3, 4, 5, 6, 7, 8};

   
    int sum_even = 0, sum_odd = 0;
    int count_even = 0, count_odd = 0;

   
    for (int i : n) {
        if (i % 2 == 0) {
            sum_even += i;
            count_even++;
        } else {
            sum_odd += i;
            count_odd++;
        }
    }

    cout << "Total sum of even numbers: " << sum_even << endl;
    cout << "Count of even numbers: " << count_even << endl;
    cout << "Total sum of odd numbers: " << sum_odd << endl;
    cout << "Count of odd numbers: " << count_odd << endl;

    
}
*/


/*
Question-5b: 

def calculate_energy():
    mass = 1.0  # in kilograms
    speed_of_light = 299792458  # in meters per second

    energy = mass * speed_of_light ** 2
    print(f"The energy equivalent of {mass} kg is {energy} joules.")

calculate_energy()
*/

  
void Q5() {
   
    double mass = 1.0;
    double speed_of_light = 299792458;

   
    double energy = mass * pow(speed_of_light, 2);

   
    std::cout << "The energy equivalent of " << mass << " kg is " 
              << energy << " joules." << std::endl;
}


