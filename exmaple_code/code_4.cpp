#include<stdio.h>

class ex1 {
	int var1;
	int var2;
	char var3;
public:
	int get_var1();
};

int ex1::get_var1() {
	return var1;
}

void test() {
	printf("test\n");
}

void local_declare_object() {
	test();
	ex1 instance_ex1;
}

int main() {
	local_declare_object();
	return 0;
}
