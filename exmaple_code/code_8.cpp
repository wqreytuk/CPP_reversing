#include <iostream>
#include <typeinfo>

using namespace std;

class a {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};

class b {
public:
    virtual void makeSound() {
        cout << "The animal makes a sound." << endl;
    }
};

class g : public a, public b {
public:
    virtual  void makegSound() {
        cout << "The dog says woof!" << endl;
    }
};

void test() {
    printf("test\n");
}

int main() {
    g instance_g;
    test();

    return 0;
}
