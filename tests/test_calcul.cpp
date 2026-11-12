#include "..\mp2-lab3-stack\calculator.h"
#include "gtest.h"

TEST(Calculator, simple_addition) {
    Calculator calc;
    calc.set_infix("2+3");
    calc.to_postfix();

    // Если результат не 5.0, этот ASSERT покажет нам, что именно попало в постфикс
    ASSERT_EQ(calc.get_postfix(), "2 3 +");
}