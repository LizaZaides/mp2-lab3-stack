#include "..\mp2-lab3-stack\Stack.h"

#include "gtest.h"

TEST(Stack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(Stack<int> bf(3));
}

TEST(Stack, canot_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(Stack<int> bf(-3));
}

TEST(Stack, can_get_element_from_stack)
{
    Stack<int> bf(3);
    bf.push(1);
    ASSERT_EQ(bf.pop(), 1);
}

TEST(Stack, can_create_copied_stack)
{
    Stack<int> bf(3);
    ASSERT_NO_THROW(Stack<int> bf1(bf));
}

TEST(Stack, can_create_assidment_stack)
{
    Stack<int> bf(3);
    Stack<int> bf1(3);
    bf.push(1);
    bf.push(2);
    bf1 = bf;
    ASSERT_EQ(bf.pop(),2);
    ASSERT_EQ(bf.pop(),1);
}


TEST(Stack, can_extract_from_empty_stack)
{
    Stack<int> bf(3);
    ASSERT_ANY_THROW(bf.pop());
}

TEST(Stack, can_extract_element_from_top_stack)
{
    Stack<int> bf(3);
    bf.push(1);
    ASSERT_EQ(bf.pop(),1);
}

TEST(Stack, can_get_element_from_top_stack)
{
    Stack<int> bf(3);
    ASSERT_ANY_THROW(bf.pop());
}

TEST(Stack, can_push_from_full_stack)
{
    Stack<int> bf(3);
    bf.push(1);
    bf.push(2);
    bf.push(3);
    ASSERT_ANY_THROW(bf.push(4));
}

TEST(Stack, can_compare_stack_true)
{
    Stack<int> bf(3);
    bf.push(1);
    bf.push(2);
    bf.push(3);
    Stack<int> bf1(3);
    bf1.push(1);
    bf1.push(2);
    bf1.push(3);
    ASSERT_TRUE(bf1==bf);
}