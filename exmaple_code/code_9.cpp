#include <iostream>
#include <typeinfo>

using namespace std;

class A {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};

class B : public A {
public:
    void makeSound() override {
        cout << "The dog says woof!" << endl;
    }
};

class C : public B {
public:
    void makeSound() override {
        cout << "The cat says meow!" << endl;
    }
};

int main() {
    A* animalPtr;
    B dog;
    C cat;

    animalPtr = &dog;
    cout << "The type of animalPtr is: " << typeid(*animalPtr).name() << endl;

    animalPtr = &cat;
    cout << "The type of animalPtr is: " << typeid(*animalPtr).name() << endl;

    return 0;
}
