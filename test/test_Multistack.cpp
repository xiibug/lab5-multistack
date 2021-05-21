#include "Multistack.h"
#include "../gtest/gtest.h"

TEST(TMultistack, can_create_multistack)
{
	ASSERT_NO_THROW(TMultiStack<int> t(3, 2));
}

TEST(TMultistack, cannot_create_multistack_with_negative_length)
{
	ASSERT_ANY_THROW(TMultiStack<int> t(-3, 2));
}
TEST(TMultistack, cannot_create_multistack_with_negative_scount)
{
	ASSERT_ANY_THROW(TMultiStack<int> t(3, -2));
}
TEST(TMultistack, can_push_and_get_from_multistack)
{
	TMultiStack<int> t(7, 3);
	t.Push(1, 1);
	t.Push(2, 1);
	EXPECT_EQ(2, t.Get(1));
}
TEST(TMultistack, cannot_push_into_negative_stack)
{
	TMultiStack<int> t(7, 3);
	ASSERT_ANY_THROW(t.Push(1, -1));
}
TEST(TMultistack, cannot_push_if_multistack_full)
{
	TMultiStack<int> t(2, 2);
	t.Push(1, 1);
	t.Push(2, 1);
	ASSERT_ANY_THROW(t.Push(1, 0));
}
TEST(TMultistack, can_copy_multistack)
{
	TMultiStack<int> t(2, 2);
	t.Push(1, 1);
	t.Push(2, 1);
	t.Push(3, 0);
	TMultiStack<int> q(t);
	ASSERT_EQ(q, t);
}
TEST(TMultistack, can_use_assignment_operator) {
	TMultiStack<int> t(2, 2);
	t.Push(1, 0);
	t.Push(2, 1);
	t.Push(3, 1);
	TMultiStack<int> w;
	w = t;
	EXPECT_EQ(w, t);
}
TEST(TMultistack, copied_multistack_has_its_own_memory)
{
	TMultiStack<int> t(2, 2);
	t.Push(1, 1);
	t.Push(2, 1);
	TMultiStack<int> q(t);
	q.Push(1, 0);
	EXPECT_NE(t, q);
}
TEST(TMultistack, copied_multistack_has_its_own_memory_2)
{
	TMultiStack<int> t(2, 2);
	t.Push(1, 1);
	t.Push(2, 1);
	TMultiStack<int> q;
	q = t;
	q.Push(1, 0);
	EXPECT_NE(t, q);
}
TEST(TMultistack, can_use_file_input_output)
{
	TMultiStack<int> t(2, 2);
	t.Push(1, 1);
	t.Push(2, 1);
	t.Push(3, 0);

	ofstream fout;
	fout.open("file.txt");
	fout << t;
	fout.close();

	TMultiStack<int> q(1, 1);
	ifstream fin;
	fin.open("file.txt");
	fin >> q;
	fin.close();
	EXPECT_EQ(t, q);
}