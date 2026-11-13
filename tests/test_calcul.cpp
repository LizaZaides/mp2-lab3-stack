#include "..\mp2-lab3-stack\calculator.h"
#include "gtest.h"

TEST(Calculator, can_add_numbers) {
    Calculator calc;
    calc.set_infix("2 + 3");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 5.0);
}

TEST(Calculator, can_sub_numbers) {
    Calculator calc;
    calc.set_infix("5- 3");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 2.0);
}

TEST(Calculator, can_mult_numbers) {
    Calculator calc;
    calc.set_infix("2 * 3");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 6.0);
}

TEST(Calculator, can_div_numbers) {
    Calculator calc;
    calc.set_infix("6 / 3");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 2.0);
}

TEST(Calculator, can_use_power) {
    Calculator calc;
    calc.set_infix("2 ^ 3");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 8.0);
}


//œ–»Œ–»“≈“€

TEST(CalculatorTest, multiply_has_higher_priority_than_add) {
    Calculator calc;
    calc.set_infix("2 + 3 * 4");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 14.0);
}

TEST(CalculatorTest, brackets_change_priority) {
    Calculator calc;
    calc.set_infix("(2 + 3) * 4");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 20.0);
}

TEST(CalculatorTest, works_left_to_right_for_subtraction) {
    Calculator calc;
    calc.set_infix("10 - 3 - 2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 5.0);
}

TEST(CalculatorTest, works_left_to_right_for_division) {
    Calculator calc;
    calc.set_infix("16 / 4 / 2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 2.0);
}

TEST(CalculatorTest, complex_priority_and_brackets) {
    Calculator calc;
    calc.set_infix("2 + 3 * (4 - 1)");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 11.0);
}


TEST(CalculatorTest, priority_with_nested_brackets_1) {
    Calculator calc;
    calc.set_infix("(2+3*4)/(6-2*2)");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 7.0);
}

TEST(CalculatorTest, priority_with_power1) {
    Calculator calc;
    calc.set_infix("(2+3*4^2)");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 50.0);
}

TEST(CalculatorTest, priority_with_power2) {
    Calculator calc;
    calc.set_infix("(2+3)*4^2-5");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 75.0);
}

TEST(CalculatorTest, power_has_higher_priority_than_multiply) {
    Calculator calc;
    calc.set_infix("2*3^2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 18.0);
}

TEST(CalculatorTest, right_associativity_of_power) {
    Calculator calc;
    calc.set_infix("2^3^2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 64.0);
}

TEST(CalculatorTest, multiple_brackets_and_operations) {
    Calculator calc;
    calc.set_infix("((10-2)*3)/(4+2)+5^2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 29.0);
}


//¬≈Ÿ≈—“¬≈ÕÕ€≈

TEST(CalculatorTest, can_work_with_double) {
    Calculator calc;
    calc.set_infix("1.5 + 2.5");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 4.0);
}

TEST(CalculatorTest, can_work_with_dot_at_start) {
    Calculator calc;
    calc.set_infix(".5 + .5");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 1.0);
}

TEST(CalculatorTest, double_subtraction_can_give_negative) {
    Calculator calc;
    calc.set_infix("1.2 - 2.5");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), -1.3);
}

TEST(CalculatorTest, double_dot_in_number_throws) {
    Calculator calc;
    calc.set_infix("1.2.3 + 1");
    ASSERT_ANY_THROW(calc.CalcPostfix());
}


//œŒ—“‘» —Õ¿ﬂ —“–Œ ¿

TEST(CalculatorTest, postfix_string_simple) {
    Calculator calc;
    calc.set_infix("2 + 3");
    calc.to_postfix();
    ASSERT_EQ(calc.get_postfix(), "2 3 +");
}

TEST(CalculatorTest, postfix_string_with_priority) {
    Calculator calc;
    calc.set_infix("2 + 3 * 4");
    calc.to_postfix();
    ASSERT_EQ(calc.get_postfix(), "2 3 4 * +");
}

TEST(CalculatorTest, postfix_string_with_brackets) {
    Calculator calc;
    calc.set_infix("(2 + 3) * 4");
    calc.to_postfix();
    ASSERT_EQ(calc.get_postfix(), "2 3 + 4 *");
}


//œ–Œ¬≈– ¿ — Œ¡Œ 
TEST(CalculatorTest, extra_close_bracket_throws) {
    Calculator calc;
    calc.set_infix("2 + 3)");
    ASSERT_ANY_THROW(calc.to_postfix());
}

TEST(CalculatorTest, unclosed_open_bracket_throws) {
    Calculator calc;
    calc.set_infix("(2 + 3");
    ASSERT_ANY_THROW(calc.to_postfix());
}

TEST(CalculatorTest, double_open_bracket_throws) {
    Calculator calc;
    calc.set_infix("((2 + 3) * 4");
    ASSERT_ANY_THROW(calc.to_postfix());
}

TEST(CalculatorTest, empty_expression_throws) {
    Calculator calc;
    calc.set_infix("");
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, extra_close_bracket_in_middle_throws) {
    Calculator calc;
    calc.set_infix("2 + 3) * 4");
    ASSERT_ANY_THROW(calc.to_postfix());
}


TEST(CalculatorTest, division_by_zero_throws) {
    Calculator calc;
    calc.set_infix("5 / 0");
    calc.to_postfix();
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, not_enough_operands_throws) {
    Calculator calc;
    calc.set_infix("2 +");
    calc.to_postfix();
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, operator_without_left_operand_throws) {
    Calculator calc;
    calc.set_infix("* 2 + 3");
    calc.to_postfix();
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, two_operators_in_a_row_throws) {
    Calculator calc;
    calc.set_infix("2 + * 3");
    calc.to_postfix();
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, only_operators_throws) {
    Calculator calc;
    calc.set_infix("+*");
    calc.to_postfix();
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(CalculatorTest, big_complex_expression) {
    Calculator calc;
    calc.set_infix("2 + (3 * (4 - 1)) ^ 2 / 9");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 11.0);
}

TEST(CalculatorTest, single_number) {
    Calculator calc;
    calc.set_infix("42");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 42.0);
}

TEST(CalculatorTest, single_number_in_brackets) {
    Calculator calc;
    calc.set_infix("(42)");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 42.0);
}

TEST(CalculatorTest, negative_result_from_subtraction) {
    Calculator calc;
    calc.set_infix("5 - 10");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), -5.0);
}

TEST(CalculatorTest, very_long_expression) {
    Calculator calc;
    calc.set_infix("(1 + 2 * 3) * (4 - 5 / 2) + 6^2");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 46.5);
}

TEST(CalculatorTest, can_handle_big_numbers) {
    Calculator calc;
    calc.set_infix("1000000 * 1000000");
    calc.to_postfix();
    ASSERT_EQ(calc.CalcPostfix(), 1000000000000.0);
}