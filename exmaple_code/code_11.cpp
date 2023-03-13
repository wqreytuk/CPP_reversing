#include <iostream>
#include <typeinfo>

using namespace std;

class g {
public:
    virtual void makegSound() {
        cout << "The dog says woof!" << endl;
    }
};

void test() {
    printf("test\n");
}

int main() {
    g* pg = new g();
    pg->makegSound();
    test();

    return 0;
}
