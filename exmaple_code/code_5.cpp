#include <iostream>
#include <typeinfo>

using namespace std;

class Animal {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "The dog says woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "The cat says meow!" << endl;
    }
};

int main() {
    Animal* animalPtr;
    Dog dog;
    Cat cat;

    animalPtr = &dog;
    cout << "The type of animalPtr is: " << typeid(*animalPtr).name() << endl;

    animalPtr = &cat;
    cout << "The type of animalPtr is: " << typeid(*animalPtr).name() << endl;

    return 0;
}
