#include "unit_test.h"
#include "bina_clac_test.hpp"



int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc == 2 ? argv[1] : '\0');
}