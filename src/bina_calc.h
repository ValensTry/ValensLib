#ifndef _BINARY_CALCULATE_H_
#define _BINARY_CALCULATE_H_
#include <stdint.h>
typedef unsigned long uint32;
typedef unsigned short uint16;

int lowbit(int x);

uint32 reverseBit(uint32 x);

uint32 judgePow2(uint32 x);

int add(int a, int b);

void minusOne(int x);

void swap(int& a, int& b);

void binary_Enumerate();

uint16 reverse16(uint16 x);

long long pow2(long long n, int x);

long long pow2(int x);

//n除以一个pow(2, x)
int divide2(int n, int x);

//判断正整数x是否为奇数
int isOdd(int x);

int mod2(int m, int n);

int getAverage(int x, int y);

int triInequation(int x, int a, int b);

bool isPowOfTwo(int num);

bool isPowOfFour(int num);

int add_BitWay(int a, int b);

uint32_t _builtin_popcount(uint32_t n);

uint32_t reverseBits(uint32_t n);

uint32_t bit_change(uint32_t num, int index);

uint32_t bit_clr(uint32_t num, int index);

uint64_t u64_ffs(uint64_t v);

void calc_double();

#endif  //_BINARY_CALCULATE_H_