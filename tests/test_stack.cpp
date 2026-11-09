
#include "Stack.h"
#include "gtest.h"

TEST(Stack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(Stack<int> bf(3));
}

TEST(Stack, canot_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(Stack<int> bf(-3));
}

TEST(Stack, cannot_create_stack_of_zero_length) {
    ASSERT_ANY_THROW(Stack<int> bf(0));
}

TEST(Stack, can_create_copied_stack)
{
    Stack<int> bf(3);
    ASSERT_NO_THROW(Stack<int> bf1(bf));
}

TEST(Stack, can_add_element_to_stack) {
    Stack<int> bf(3);
    ASSERT_NO_THROW(bf.push(1));
}

TEST(Stack, cannot_push_to_full_stack)
{
    Stack<int> bf(3);
    bf.push(1);
    bf.push(2);
    bf.push(3);
    ASSERT_ANY_THROW(bf.push(4));
}

TEST(Stack, can_get_element_from_stack)
{
    Stack<int> bf(3);
    bf.push(1);
    ASSERT_EQ(bf.pop(), 1);
}

TEST(Stack, can_extract_from_empty_stack)
{
    Stack<int> bf(3);
    ASSERT_ANY_THROW(bf.pop());
}

TEST(Stack, cannot_get_top_from_empty_stack) {
    Stack<int> bf(3);
    ASSERT_ANY_THROW(bf.top());
}

TEST(Stack, can_check_that_stack_is_empty) {
    Stack<int> bf(3);
    ASSERT_TRUE(bf.IsEmpty());
}

TEST(Stack, can_check_that_stack_is_not_empty) {
    Stack<int> bf(3);
    bf.push(10);
    ASSERT_FALSE(bf.IsEmpty());
}

TEST(Stack, can_check_that_stack_is_full) {
    Stack<int> bf(3);
    bf.push(1); bf.push(2); bf.push(3);
    ASSERT_TRUE(bf.IsFull());
}

TEST(Stack, can_assign_one_stack_to_another)
{
    Stack<int> bf(3);
    Stack<int> bf1(3);
    bf.push(1);
    bf.push(2);
    bf1 = bf;
    ASSERT_EQ(bf1.pop(), 2);
    ASSERT_EQ(bf1.pop(), 1);
}

TEST(Stack, can_compare_stack_true) {
    Stack<int> bf(3);
    bf.push(1); bf.push(2); bf.push(3);
    Stack<int> bf1(3);
    bf1.push(1); bf1.push(2); bf1.push(3);

    ASSERT_TRUE(bf1 == bf);
}

TEST(Stack, can_compare_stack_false) {
    Stack<int> bf(3);
    bf.push(1); bf.push(2);
    Stack<int> bf1(3);
    bf1.push(1); bf1.push(3);
    ASSERT_FALSE(bf1 == bf);
    ASSERT_TRUE(bf1 != bf);
}

TEST(Stack, clear_makes_stack_empty) {
    Stack<int> bf(3);
    bf.push(1);
    bf.push(2);
    bf.Clear();
    bf.Clear();
    ASSERT_TRUE(bf.IsEmpty());
    ASSERT_ANY_THROW(bf.pop());
}

TEST(Stack, self_assignment_is_safe) {
    Stack<int> bf(3);
    bf.push(10);
    bf = bf;
    ASSERT_EQ(bf.pop(), 10);
}

