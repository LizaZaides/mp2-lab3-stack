#include "..\mp2-lab3-stack\container.h"
#include "gtest.h"

TEST(ContainerTest, can_create_container_with_positive_size) {
    ASSERT_NO_THROW(Container<int> c(5));
}

TEST(ContainerTest, cannot_create_container_with_zero_size) {
    ASSERT_ANY_THROW(Container<int> c(0));
}

TEST(ContainerTest, cannot_create_container_with_negative_size) {
    ASSERT_ANY_THROW(Container<int> c(-3));
}

TEST(ContainerTest, can_create_copied_container) {
    Container<int> c1(3);
    c1.push_back(1);
    c1.push_back(2);
    ASSERT_NO_THROW(Container<int> c2(c1));
}

TEST(ContainerTest, can_create_moved_container) {
    Container<int> c1(3);
    c1.push_back(1);
    ASSERT_NO_THROW(Container<int> c2(std::move(c1)));
}

TEST(ContainerTest, can_push_back_element) {
    Container<int> c(3);
    ASSERT_NO_THROW(c.push_back(10));
}

TEST(ContainerTest, push_back_increases_count) {
    Container<int> c(3);
    c.push_back(10);
    c.push_back(20);
    ASSERT_EQ(c.get_count(), 2);
}

TEST(ContainerTest, pop_back_returns_last_element) {
    Container<int> c(3);
    c.push_back(10);
    c.push_back(20);
    ASSERT_EQ(c.pop_back(), 20);
    ASSERT_EQ(c.pop_back(), 10);
}

TEST(ContainerTest, cannot_pop_back_from_empty_container) {
    Container<int> c(3);
    ASSERT_ANY_THROW(c.pop_back());
}

TEST(ContainerTest, pop_back_decreases_count) {
    Container<int> c(3);
    c.push_back(1);
    c.push_back(2);
    c.pop_back();
    ASSERT_EQ(c.get_count(), 1);
}


TEST(ContainerTest, container_grows_when_full) {
    Container<int> c(2);
    c.push_back(1);
    c.push_back(2);
    ASSERT_NO_THROW(c.push_back(3));
    ASSERT_EQ(c.get_count(), 3);
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], 2);
    ASSERT_EQ(c[2], 3);
}

TEST(ContainerTest, can_read_element_by_index) {
    Container<int> c(3);
    c.push_back(10);
    c.push_back(20);
    ASSERT_EQ(c[0], 10);
    ASSERT_EQ(c[1], 20);
}

TEST(ContainerTest, can_modify_element_by_index) {
    Container<int> c(3);
    c.push_back(10);
    c[0] = 15;
    ASSERT_EQ(c[0], 15);
}


TEST(ContainerTest, invalid_index_throws) {
    Container<int> c(3);
    c.push_back(10);
    ASSERT_ANY_THROW(c[1]);
    ASSERT_ANY_THROW(c[-1]);
}

TEST(ContainerTest, clear_makes_container_empty) {
    Container<int> c(3);
    c.push_back(1);
    c.push_back(2);
    c.clear();
    ASSERT_EQ(c.get_count(), 0);
}

TEST(ContainerTest, copy_is_deep) {
    Container<int> c1(3);
    c1.push_back(10);
    c1.push_back(20);
    Container<int> c2(c1);
    c1[0] = 12;
    ASSERT_EQ(c2[0], 10);
}


TEST(ContainerTest, assignment_copies_data) {
    Container<int> c1(3);
    c1.push_back(10);
    Container<int> c2(5);
    c2.push_back(99);
    c2 = c1; 
    ASSERT_EQ(c2.get_count(), 1);
    ASSERT_EQ(c2[0], 10);
}

TEST(ContainerTest, self_assignment_is_safe) {
    Container<int> c(3);
    c.push_back(10);
    c = c;
    ASSERT_EQ(c.get_count(), 1);
    ASSERT_EQ(c[0], 10);
}

TEST(ContainerTest, move_assignment_works) {
    Container<int> c1(3);
    c1.push_back(10);
    Container<int> c2(3);
    c2 = std::move(c1);
    ASSERT_EQ(c2.get_count(), 1);
    ASSERT_EQ(c2[0], 10);
    ASSERT_EQ(c1.get_count(), 0);
}

TEST(ContainerTest, get_size_returns_capacity) {
    Container<int> c(5);
    ASSERT_EQ(c.get_size(), 5);
}

TEST(ContainerTest, get_size_increases_after_resize) {
    Container<int> c(2);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    ASSERT_EQ(c.get_size(), 4);
}

TEST(ContainerTest, size_method_shrinks_container) {
    Container<int> c(5);
    c.push_back(10);
    c.push_back(20);
    c.push_back(30);
    c.Size(2);
    ASSERT_EQ(c.get_size(), 2);
    ASSERT_EQ(c.get_count(), 2); 
    ASSERT_EQ(c[0], 10);
    ASSERT_EQ(c[1], 20);
}

TEST(ContainerTest, size_method_grows_container) {
    Container<int> c(2);
    c.push_back(1);
    c.push_back(2);
    c.Size(5);
    ASSERT_EQ(c.get_size(), 5);
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], 2);
}


TEST(ContainerTest, size_method_throws_on_invalid_input) {
    Container<int> c(3);
    ASSERT_ANY_THROW(c.Size(0));
    ASSERT_ANY_THROW(c.Size(-5));
}