#include <iostream>
#include <typeinfo>

using namespace std;

class A {
    int a;
    int b;
    int c;
public:
    A(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

void test() {
    printf("test");
}

int main() {
    A a(1, 2, 3);
    test();
    return 0;
}
