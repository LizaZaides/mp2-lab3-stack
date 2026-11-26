#include "..\mp2-lab3-stack\calculator.h"
#include "gtest.h"
TEST(Calc_1, can_add_numbers) {
    Calculator calc;
    calc.set_infix("2 + 3");
    ASSERT_EQ(calc.Calc(), 5.0);
}

TEST(Calc_1, can_sub_numbers) {
    Calculator calc;
    calc.set_infix("5- 3");
    ASSERT_EQ(calc.Calc(), 2.0);
}

TEST(Calc_1, can_mult_numbers) {
    Calculator calc;
    calc.set_infix("2 * 3");
    ASSERT_EQ(calc.Calc(), 6.0);
}

TEST(Calc_1, can_div_numbers) {
    Calculator calc;
    calc.set_infix("6 / 3");
    ASSERT_EQ(calc.Calc(), 2.0);
}

TEST(Calc_1, can_use_power) {
    Calculator calc;
    calc.set_infix("2 ^ 3");
    ASSERT_EQ(calc.Calc(), 8.0);
}

//œ–»Œ–»“≈“€

TEST(Calc_1, multiply_has_higher_priority_than_add) {
    Calculator calc;
    calc.set_infix("2 + 3 * 4");
    ASSERT_EQ(calc.Calc(), 14.0);
}

TEST(Calc_1, brackets_change_priority) {
    Calculator calc;
    calc.set_infix("(2 + 3) * 4");
    ASSERT_EQ(calc.Calc(), 20.0);
}

TEST(Calc_1, works_left_to_right_for_subtraction) {
    Calculator calc;
    calc.set_infix("10 - 3 - 2");
    ASSERT_EQ(calc.Calc(), 5.0);
}

TEST(Calc_1, works_left_to_right_for_division) {
    Calculator calc;
    calc.set_infix("16 / 4 / 2");
    ASSERT_EQ(calc.Calc(), 2.0);
}

TEST(Calc_1, complex_priority_and_brackets) {
    Calculator calc;
    calc.set_infix("2 + 3 * (4 - 1)");
    ASSERT_EQ(calc.Calc(), 11.0);
}


TEST(Calc_1, priority_with_nested_brackets_1) {
    Calculator calc;
    calc.set_infix("(2+3*4)/(6-2*2)");
    ASSERT_EQ(calc.Calc(), 7.0);
}

TEST(Calc_1, priority_with_power1) {
    Calculator calc;
    calc.set_infix("(2+3*4^2)");
    ASSERT_EQ(calc.Calc(), 50.0);
}

TEST(Calc_1, priority_with_power2) {
    Calculator calc;
    calc.set_infix("(2+3)*4^2-5");
    ASSERT_EQ(calc.Calc(), 75.0);
}

TEST(Calc_1, power_has_higher_priority_than_multiply) {
    Calculator calc;
    calc.set_infix("2*3^2");
    ASSERT_EQ(calc.Calc(), 18.0);
}

TEST(Calc_1, right_associativity_of_power) {
    Calculator calc;
    calc.set_infix("2^3^2");
    ASSERT_EQ(calc.Calc(), 64.0);
}

TEST(Calc_1, multiple_brackets_and_operations) {
    Calculator calc;
    calc.set_infix("((10-2)*3)/(4+2)+5^2");
    ASSERT_EQ(calc.Calc(), 29.0);
}


//¬≈Ÿ≈—“¬≈ÕÕ€≈

TEST(Calc_1, can_work_with_double) {
    Calculator calc;
    calc.set_infix("1.5 + 2.5");
    ASSERT_EQ(calc.Calc(), 4.0);
}

TEST(Calc_1, can_work_with_dot_at_start) {
    Calculator calc;
    calc.set_infix(".5 + .5");
    ASSERT_EQ(calc.Calc(), 1.0);
}

TEST(Calc_1, double_subtraction_can_give_negative) {
    Calculator calc;
    calc.set_infix("1.2 - 2.5");
    ASSERT_EQ(calc.Calc(), -1.3);
}

// œ–Œ¬≈– ¿ — Œ¡Œ 
TEST(Calc_1, extra_close_bracket_throws) {
    Calculator calc;
    calc.set_infix("2 + 3)");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, unclosed_open_bracket_throws) {
    Calculator calc;
    calc.set_infix("(2 + 3");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, double_open_bracket_throws) {
    Calculator calc;
    calc.set_infix("((2 + 3) * 4");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, empty_expression_throws) {
    Calculator calc;
    calc.set_infix("");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, extra_close_bracket_in_middle_throws) {
    Calculator calc;
    calc.set_infix("2 + 3) * 4");
    ASSERT_ANY_THROW(calc.Calc());
}


TEST(Calc_1, division_by_zero_throws) {
    Calculator calc;
    calc.set_infix("5 / 0");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, not_enough_operands_throws) {
    Calculator calc;
    calc.set_infix("2 +");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, operator_without_left_operand_throws) {
    Calculator calc;
    calc.set_infix("* 2 + 3");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, two_operators_in_a_row_throws) {
    Calculator calc;
    calc.set_infix("2 + * 3");
    ASSERT_ANY_THROW(calc.Calc());
}


TEST(Calc_1, only_operators_throws) {
    Calculator calc;
    calc.set_infix("+*");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(Calc_1, big_complex_expression) {
    Calculator calc;
    calc.set_infix("2 + (3 * (4 - 1)) ^ 2 / 9");
    ASSERT_EQ(calc.Calc(), 11.0);
}

TEST(Calc_1, big_complex_expression1) {
    Calculator calc;
    calc.set_infix("(((3+2)/5)-2)^2");
    ASSERT_EQ(calc.Calc(), 1.0);
}

TEST(Calc_1, single_number) {
    Calculator calc;
    calc.set_infix("42");
    ASSERT_EQ(calc.Calc(), 42.0);
}

TEST(Calc_1, single_number_in_brackets) {
    Calculator calc;
    calc.set_infix("(42)");
    ASSERT_EQ(calc.Calc(), 42.0);
}

TEST(Calc_1, negative_result_from_subtraction) {
    Calculator calc;
    calc.set_infix("5 - 10");
    ASSERT_EQ(calc.Calc(), -5.0);
}

TEST(Calc_1, very_long_expression) {
    Calculator calc;
    calc.set_infix("(1 + 2 * 3) * (4 - 5 / 2) + 6^2");
    ASSERT_EQ(calc.Calc(), 46.5);
}

TEST(Calc_1, can_handle_big_numbers) {
    Calculator calc;
    calc.set_infix("1000000 * 1000000");
    ASSERT_EQ(calc.Calc(), 1000000000000.0);
}


//‘”Õ ÷»»

TEST(Calc_1, can_use_sin) {
    Calculator calc;
    calc.set_infix("sin(0)");
    ASSERT_NEAR(calc.Calc(), 0.0, 0.001);
}
TEST(Calc_1, can_use_cos) {
    Calculator calc;
    calc.set_infix("cos(0)");
    ASSERT_NEAR(calc.Calc(), 1.0, 0.001);
}
TEST(Calc_1, can_use_exp) {
    Calculator calc;
    calc.set_infix("exp(0)");
    ASSERT_NEAR(calc.Calc(), 1.0, 0.001);
}
TEST(Calc_1, can_use_ln) {
    Calculator calc;
    calc.set_infix("ln(1)");
    ASSERT_NEAR(calc.Calc(), 0.0, 0.001);
}
TEST(Calc_1, can_use_constants) {
    Calculator calc;
    calc.set_infix("ln(exp(2))");
    ASSERT_NEAR(calc.Calc(), 2.0, 0.001);
}

TEST(Calc_Functions, can_use_funcs_with_pi_value) {
    Calculator calc;
    calc.set_infix("sin(3.14159)");
    ASSERT_NEAR(calc.Calc(), 0.0, 0.001);
}

TEST(Calc_1, can_apply_sin_to_expression) {
    Calculator calc;
    calc.set_infix("sin(2 + 3 * 4)");
    ASSERT_NEAR(calc.Calc(), sin(14.0), 0.001);
}

//‘”Õ ÷»» œ–»Œ–»“≈“€

TEST(Calc_1, function_has_higher_priority_than_add) {
    Calculator calc;
    calc.set_infix("2 + sin(0)");
    ASSERT_NEAR(calc.Calc(), 2.0, 0.001);
}

TEST(Calc_1, function_has_higher_priority_than_multiply) {
    Calculator calc;
    calc.set_infix("2 * cos(0)");
    ASSERT_NEAR(calc.Calc(), 2.0, 0.001);
}

TEST(Calc_1, function_and_brackets_priority) {
    Calculator calc;
    calc.set_infix("sin(0) * (2 + 3)");
    ASSERT_NEAR(calc.Calc(), 0.0, 0.001);
}

TEST(Calc_1, math_expression_with_functions) {
    Calculator calc;
    calc.set_infix("cos(0) + 2^3 / sin(3.14159/2)");
    ASSERT_NEAR(calc.Calc(), 9.0, 0.001);
}

//‘”Õ ÷»» ¬ÀŒ∆≈ÕÕ€≈

TEST(Calc_1, nested_functions_simple) {
    Calculator calc;
    calc.set_infix("cos(sin(0))"); 
    ASSERT_NEAR(calc.Calc(), 1.0, 0.001);
}

TEST(Calc_1, nested_functions_with_expression) {
    Calculator calc;
    calc.set_infix("ln(exp(sin(0) + cos(0)))");
    ASSERT_NEAR(calc.Calc(), 1.0, 0.001);
}

TEST(Calc_1, deeply_nested_functions) {
    Calculator calc;
    calc.set_infix("sin(cos(sin(0)))");
    ASSERT_NEAR(calc.Calc(), sin(1.0), 0.001);
}