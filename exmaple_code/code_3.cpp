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

class ex3 :public ex2 {
	int var1;
public:
	int get_value();
};

int ex3::get_value() {
	return var1;
}

class ex4 {
	int var1;
	int var2;
public:
	virtual int ex4_func1();
	virtual void ex4_func2();
};

int ex4::ex4_func1() {
	return var1;
}

void ex4::ex4_func2() {
	printf("1234");
}

class ex5 :public ex4, ex2 {
	int var1;
public:
	void ex5_func1();
	virtual void ex5_func2();
};

void ex5::ex5_func1() {
	printf("1234");
}

void ex5::ex5_func2() {
	printf("7890");
}

void test() {
	printf("test\n");
}

class global_object {
	int var1;
public:
	global_object(int a) { var1 = a; test(); }
};

global_object go(123);
int main() {
	test();
	return 0;
}
