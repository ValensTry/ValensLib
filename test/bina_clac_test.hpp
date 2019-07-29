#include "..\src\bina_calc.h"
#include "unit_test.h"

TEST(LowBit)
{
    int odd = 333;
    int even = 4444;

    ASSERT_EQ(lowbit(odd), 1);
    ASSERT_EQ(lowbit(even), 0);
}

TEST(ReverseBit)
{
    uint32 a = 6;
    uint32 b = 8;

    ASSERT_EQ(reverseBit(a), uint32(3));
    ASSERT_EQ(reverseBit(b), uint32(1));
}

TEST(JudgePow2)
{
    //����8 16 �ͷ���1  1 3 6ɶ�ľͷ���0
    uint32 a = 8;
    uint32 b = 16;
    uint32 c = 1;
    uint32 d = 6;

    ASSERT_EQ(judgePow2(a), uint32(1));
    ASSERT_EQ(judgePow2(b), uint32(0));
}