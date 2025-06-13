#include<bits/stdc++.h>
using namespace std;

class Faculty {
    public:
        int id;
        string name;
        int age;
        float salary;

        // Constructor to initialize the class
        Faculty(int id, string name, int age, float salary) 
            : id(id), name(name), age(age), salary(salary) {}
};
// Structure definition
typedef struct Student {
    int id;
    string name;
    int age;
    float gpa;
    // Constructor to initialize the structure
    // method 1: Using member initializer list : initializing members directly, initializer list means to say that we are initializing the members of the class directly in the constructor's member initializer list.
    // Student(int id, string name, int age, float gpa) 
    //     : id(id), name(name), age(age), gpa(gpa) {}

    // method 2: Using assignment in the constructor body
    Student(int id, string name, int age, float gpa) 
    {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }

} Std;

int main() {
    Std student1 = Std(1, "John Doe", 20, 3.5);

    // student1.id = 1;
    cout << student1.name << endl;
}
