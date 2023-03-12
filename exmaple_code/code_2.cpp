#include<stdio.h>

class ex1 {
	int var1;
	int var2;
	char var3;
public:
	int get_var1();
};

class ex2 {
	int var1;
public:
	virtual int get_sum(int x, int y);
	virtual void reset_value();
};

int ex1::get_var1() {
	return var1;
}

int ex2::get_sum(int x,int y) {
	return x+y;
}

void ex2::reset_value() {
	var1 = 1234;
}

void test() {
	printf("test\n");
}

int main() {
	ex2* pex2 = new ex2();
	test();
	return 0;
}
