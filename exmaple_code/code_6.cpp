#include <iostream>
#include <typeinfo>

using namespace std;

class a {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};
class e {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};

class g : public virtual a, public virtual e {
public:
    virtual  void makegSound() {
        cout << "The dog says woof!" << endl;
    }
};

int main() {
    a* aptr;
    e* eptr;
    g instance_g;

    aptr = &instance_g;
    cout << "The type of animalPtr is: " << typeid(*aptr).name() << endl;

    eptr = &instance_g;
    cout << "The type of animalPtr is: " << typeid(*eptr).name() << endl;

    return 0;
}
