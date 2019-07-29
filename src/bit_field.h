#include <iostream>
/*
位域结构体 为了节省存储 在分配结构体内存的时候从以字节为单位分配
而不是数据类型
*/
//https://blog.csdn.net/yihongxiaoxiang/article/details/50327587
/*
rule:
只有同种类型的才可以使用位域结构体
当一个字节剩下的bit不够供下一个变量使用时, 就新用一个字节
如果位域的位域长度为0表示是个空域，同时下一个域应当从下一个字节单元开始存放。

经过下面这个例子可以测试出, 位域的变量有没有符号位和数据类型有关

*/
struct Bit_Struct {
	int a : 16;
	int b : 16;
	unsigned int c : 16;
	unsigned int d : 8;
}test;

int bit_field() {
    using namespace std;
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	test.a = (1 << 15)-1;
	test.b = (1 << 15);
	test.c = (1 << 16)-1;
	test.d = (1 << 16);
	cout << test.a << endl;
	cout << test.b << endl;
	cout << test.c << endl;
	cout << test.d << endl;
	return 0;
}