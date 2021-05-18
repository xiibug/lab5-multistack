#include "Stack.h"
#include "../gtest/gtest.h"

TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStack<int> t(3));
}

TEST(TStack, cannot_create_stack_with_negative_length){
	ASSERT_ANY_THROW(TStack<int> t(-1));
}


TEST(TStack, can_push_and_get_from_stack) {
	TStack<int> t(3);
	t.Push(2);
	EXPECT_EQ(t.Get(), 2);
}

TEST(TStack, cannot_push_into_full_stack) {
	TStack<int> t(1);
	t.Push(1);
	ASSERT_ANY_THROW(t.Push(0));
}

TEST(TStack, cannot_get_if_stack_empty) {
	TStack<int> t(1);
	ASSERT_ANY_THROW(t.Get());
}

TEST(TStack, can_use_copy_operator) {
	TStack<int> t(3);
	t.Push(1);
	t.Push(2);
	TStack<int> c(t);
	EXPECT_EQ(t, c);
}

TEST(TStack, can_use_assignment_operator) {
	TStack<int> t(3);
	t.Push(1);
	t.Push(2);
	TStack<int> c=t;
	EXPECT_EQ(t, c);
}

TEST(TStack, can_get_length) {
	TStack<int> t(3);
	t.Push(1);
	t.Push(2);
	EXPECT_EQ(t.Length(), 2);
}

TEST(TStack, can_find_min) {
	TStack<int> t(3);
	t.Push(4);
	t.Push(2);
	t.Push(3);
	EXPECT_EQ(t.FindMin(), 2);
}

TEST(TStack, can_find_max) {
	TStack<int> t(3);
	t.Push(2);
	t.Push(4);
	t.Push(5);
	EXPECT_EQ(t.FindMax(), 5);
}

TEST(TStack, can_use_file_input_output) {
	TStack<int> t(4), s(3);
	t.Push(2);
	t.Push(4);
	t.Push(5);
	ofstream fout;
	fout.open("file.txt");
	fout << t;
	fout.close();

	ifstream fin;
	fin.open("file.txt");
	fin >> s;
	fin.close();

	EXPECT_EQ(t, s);
}