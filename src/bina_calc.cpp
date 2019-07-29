#include "bina_calc.h"

#include <bitset>
#include <iostream>
#include "float.h"


int lowbit(int x)
{ 
	return x&(-x);
}

//只对从最高位的1到最低位的所有二进制进行翻转
uint32 reverseBit(uint32 x)
{
	uint32 res = 0;
	while (x > 0) {
		res = (res << 1) | (x&1);
		x >>= 1;
	}	
	return res;
}

//判断一个数是否是2的指数 是则返回1 不是则返回0
uint32 judgePow2(uint32 x)
{
	return !(x&(x-1));
}

//这个没啥意义, 了解下就好，直接加好了
//一般加减运算速度是相当快的用不着去刻意用位运算
//除法 取模最慢 乘法也慢
int add(int a, int b)
{
	return (a&b)+(a|b);
}

void minusOne(int x)
{
    using std::cout;
    using std::endl;
	if (~x) cout << "我不是-1" << endl;
	else cout << "我是-1" << endl;
}

//swap 实现两个数的交换(C语言课程里的？)
void swap(int &a, int &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

//写个二进制枚举吧 枚举一个集合内所有的非空子集
//思路就是将集合中的每个数对应位置的下标一一映射到了每个bit位上
//比如如果有一个子集只有{2, 3}，那么它对应的十进制数就是3 因为(011)_2
//{1, 2}==>(110)_2==>6
void binary_Enumerate()
{
    using namespace std;
	int a[] = {1, 2, 3}; //这个应该有(1),(2),(3),(1.2),(1.3),(2.3),(1.2.3)
	int len = 3, sz = 1 << len;
	for (int i = 1; i < sz; ++i){
		for (int j = 0; j < len; ++j){
			if ((1 << j) & i){
				cout << a[j] << " ";
			}
		}
		cout << endl;
	}
}

//这里还有一个比较牛逼的演算法进行的交换
/*
功能: 比如0000 0000 0000 0001  那么结果就是 1000 0000 0000 0000
再比如 0000 0000 0000 0110 那么结果就是 0110 0000 0000 0000
算法原理:
举个栗子 比如要实现 1 2 3 4 5 6 7 8 这几个数的翻转
两个一组: (2 1) | (4 3) | (6 5) | (8 7)
四个一组: (4 3) (2 1)  | (8 7) | (6 5)
八个一组: (8 7) (6 5) (4 3) (2 1)
Finish!
这样就完成了翻转

下面二进制的实现也是这个原理
十六进制是4个bit为一个位 所以对于下面的数我们应该这么看
0x55555555 ==> (0101)(0101)(0101)(0101) 后面的类似，我就举第一个流程的做法
x & 0x55555555 就是看两个一组的时候第二位是啥, 然后左移一位就对应上面说的(2 1)的翻转
同理 x先右移一位 然后就可以看x每一组的第一位是并且结果已经在第二位了 
| 一下就可以做到两个一组组内交换了

用同样的思路也可以完成__builtin_popcount也就是二进制bit 1计数的功能
 */
uint16 reverse16(uint16 x)
{
	x = (x & 0x55555555) << 1 | (x >> 1) & 0x55555555;
	x = (x & 0x33333333) << 2 | (x >> 2) & 0x33333333;
	x = (x & 0x0f0f0f0f) << 4 | (x >> 4) & 0x0f0f0f0f;
	x = (x & 0x00ff00ff) << 8 | (x >> 8) & 0x00ff00ff;
	x = (x & 0x0000ffff) << 16 | (x >> 16) & 0x0000ffff;

    return x;
}

//求解n*pow(2, x)
long long pow2(long long n, int x)
{
	return n << x;
}

long long pow2(int x)
{
	return 1LL << x; //注意1LL 不然溢出会返回0
}

//n除以一个pow(2, x)
int divide2(int n, int x)
{
	return n >> x;
}

//判断正整数x是否为奇数
int isOdd(int x)
{
	return x & 1;
}

//m对2的幂取余
//n为2的次方
//比如mod2(9, 8) = 1
int mod2(int m, int n)
{
	return m & (n-1);
}

int getAverage(int x, int y)
{
	return (x + y) >> 1;
}

/*
if (x == a) x = b;
if (x == b) x = a;
<==>
x = a^b^x;
 */

int triInequation(int x, int a, int b)
{
	return a^b^x; 
}

#include <stdint.h>
//判断一个数是不是2的次幂
bool isPowOfTwo(int num)
{
	if (num <= 0) return 0;
	return !(num&(num - 1));
}
//判断一个数是不是4的次幂
bool isPowOfFour(int num)
{
	if (num <= 0) return 0;
	if (num & (num - 1)) return 0;
	if (num & 0x55555555) return 1;
	return 0;
}

//位运算加法
int add_BitWay(int a, int b)
{
    while (b) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

//__builtin_popcount 二进制1计数的功能
uint32_t _builtin_popcount(uint32_t n)
{
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
	return n;
}
//二进制翻转
uint32_t reverseBits(uint32_t n)
{
	n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
	n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
	n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
	n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
	n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
	return n;
}

//将第index个二进制位bit进行 异或
uint32_t bit_change(uint32_t num, int index)
{
	return num ^= (1 << index);
}
//将第index个二进制位bit设置为 0
uint32_t bit_clr(uint32_t num, int index)
{
	return num &= ~(1 << index);
}

//从低位到高位第一个bit出现1的下标
uint64_t u64_ffs(uint64_t v)
{
	int i = 0;
	if ((v & 0xFFFFFFFFull) == 0) {
		v >>= 32;
		i += 32;
	}
	if ((v & 0xFFFFull) == 0) {
		v >>= 16;
		i += 16;
	}
	if ((v & 0xFFull) == 0) {
		v >>= 8;
		i += 8;
	}
	if ((v & 0xFull) == 0) {
		v >>= 4;
		i += 4;
	}
	if ((v & 0x3ull) == 0) {
		v >>= 2;
		i += 2;
	}
	if ((v & 0x1ull) == 0) {
		v >>= 1;
		i += 1;
	}
	return i;
}
//如何求解double
//DBL_MAX所在头文件为<float.h> 之后的是根据double的存储原理进行位运算操作求解
void calc_double()
{
    using namespace std;
    double double_max = DBL_MAX;
    union{
        double a;
        long long b;
    }data;
    data.a = double_max;
    bitset<sizeof(double)*8>bits(data.b);
    cout << bits << endl;

    double a = 0; 
    uint64_t i = *(uint64_t *)&a;
    i = (~0ULL)>>1;
    i ^= (1ULL << 52);
    double ans = *(double*)&i;
    cout << ans << endl;


}
