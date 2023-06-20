#include <gtest/gtest.h>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

// ARRAY------------------------------------------------------------------------

TEST(array, default_constructor_test_1) {
  s21::Array<int, 5> my_array;
  std::array<int, 5> orig_array;
  ASSERT_EQ(my_array.Size(), orig_array.size());
  ASSERT_EQ(my_array.Empty(), orig_array.empty());
}

TEST(array, default_constructor_test_2) {
  s21::Array<int, 0> my_array;
  std::array<int, 0> orig_array;
  ASSERT_EQ(my_array.Size(), orig_array.size());
  ASSERT_EQ(my_array.Empty(), orig_array.empty());
  ASSERT_TRUE(my_array.Empty());
}

TEST(array, initializer_list_constructor_test) {
  s21::Array<double, 4> my_array{1.33, -4.5, 9.99, 0.88};
  std::array<double, 4> orig_array{1.33, -4.5, 9.99, 0.88};
  ASSERT_EQ(my_array.Size(), orig_array.size());
  for (size_t i = 0; i < orig_array.size(); ++i) {
    ASSERT_EQ(my_array.At(i), orig_array.at(i));
  }
}

TEST(array, copy_constructor_test) {
  s21::Array<int, 5> my_array{11, 567, -89, 3, 8};
  std::array<int, 5> orig_array{11, 567, -89, 3, 8};
  s21::Array<int, 5> my_copy(my_array);
  std::array<int, 5> orig_copy(orig_array);
  ASSERT_EQ(my_copy.Size(), my_array.Size());
  ASSERT_EQ(orig_copy.size(), orig_array.size());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  for (size_t i = 0; i < orig_copy.size(); ++i) {
    ASSERT_EQ(my_copy.At(i), orig_copy.at(i));
  }
}

TEST(array, move_constructor_test) {
  s21::Array<int, 10> my_array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::array<int, 10> orig_array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Array<int, 10> my_move(std::move(my_array));
  std::array<int, 10> orig_move(std::move(orig_array));
  for (size_t i = 0; i < orig_array.size(); ++i) {
    ASSERT_EQ(my_move[i], orig_move[i]);
  }
}

TEST(array, move_operator_test) {
  s21::Array<int, 10> my_array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::array<int, 10> orig_array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Array<int, 10> my_move{0};
  std::array<int, 10> orig_move{0};
  my_move = std::move(my_array);
  orig_move = std::move(orig_array);
  for (size_t i = 0; i < orig_array.size(); ++i) {
    ASSERT_EQ(my_move[i], orig_move[i]);
  }
}

TEST(array, max_size_test) {
  s21::Array<int, 5> my_array{11, 567, -89, 3, 8};
  std::array<int, 5> orig_array{11, 567, -89, 3, 8};
  ASSERT_EQ(my_array.Size(), orig_array.size());
  ASSERT_EQ(my_array.MaxSize(), orig_array.max_size());
}

TEST(array, begin_test) {
  s21::Array<char, 3> my_array{'c', 's', 'm'};
  std::array<char, 3> orig_array{'c', 's', 'm'};
  auto it = my_array.Begin();
  auto orig = orig_array.begin();
  ASSERT_EQ(*it, *orig);
  ++it;
  ++orig;
  ASSERT_EQ(*it, *orig);
}

TEST(array, end_test) {
  s21::Array<char, 3> my_array{'c', 's', 'm'};
  std::array<char, 3> orig_array{'c', 's', 'm'};
  auto it = my_array.End();
  auto orig = orig_array.end();
  --it;
  --orig;
  ASSERT_EQ(*it, *orig);
}

TEST(array, front_test) {
  s21::Array<char, 5> my_array{'a', 'b', 'c', 'd', 'e'};
  std::array<char, 5> orig_array{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(my_array.Front(), orig_array.front());
}

TEST(array, back_test) {
  s21::Array<int, 8> my_array{1, 3, 5, 7, 9, 11, 13, 15};
  std::array<int, 8> orig_array{1, 3, 5, 7, 9, 11, 13, 15};
  ASSERT_EQ(my_array.Back(), orig_array.back());
}

TEST(array, data_test) {
  s21::Array<int, 5> my_array{11, 567, -89, 3, 8};
  std::array<int, 5> orig_array{11, 567, -89, 3, 8};
  ASSERT_EQ(*my_array.Data(), *orig_array.data());
}

TEST(array, fill_test) {
  s21::Array<int, 8> my_array{0};
  std::array<int, 8> orig_array{0};
  my_array.Fill(21);
  orig_array.fill(21);
  for (size_t i = 0; i < orig_array.size(); ++i) {
    ASSERT_EQ(my_array[i], orig_array[i]);
    ASSERT_EQ(my_array[i], 21);
  }
}

// LIST-------------------------------------------------------------------------

template <typename ValueType>
bool compare_lists(s21::List<ValueType> my_list,
                   std::list<ValueType> orig_list) {
  bool result = true;
  if (my_list.Size() == orig_list.size()) {
    auto it = my_list.Begin();
    auto orig = orig_list.begin();
    for (size_t i = 0; i != my_list.Size(); ++i) {
      if (*it != *orig) {
        result = false;
        break;
      }
      ++it;
      ++orig;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(list, default_constructor_test) {
  s21::List<int> my_list;
  std::list<int> orig_list;
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
  ASSERT_TRUE(my_list.Empty());
}

TEST(list, parameterized_constructor_test) {
  s21::List<int> my_list(8);
  std::list<int> orig_list(8);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
}

TEST(list, initializer_list_constructor_test) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, copy_constructor_test_1) {
  s21::List<char> my_list;
  std::list<char> orig_list;
  s21::List<char> my_copy(my_list);
  std::list<char> orig_copy(orig_list);
  ASSERT_EQ(my_list.Size(), my_copy.Size());
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  ASSERT_TRUE(my_copy.Empty());
}

TEST(list, copy_constructor_test_2) {
  s21::List<char> my_list{'x', 'y', 'z'};
  std::list<char> orig_list{'x', 'y', 'z'};
  s21::List<char> my_copy = my_list;
  std::list<char> orig_copy = orig_list;
  ASSERT_EQ(my_list.Size(), my_copy.Size());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  ASSERT_TRUE(compare_lists(my_copy, orig_copy));
}

TEST(list, move_constructor_test_1) {
  s21::List<int> my_list{11, 88, 74, 90};
  std::list<int> orig_list{11, 88, 74, 90};
  s21::List<int> my_move(std::move(my_list));
  std::list<int> orig_move(std::move(orig_list));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_TRUE(compare_lists(my_move, orig_move));
}

TEST(list, move_constructor_test_2) {
  s21::List<double> my_list;
  std::list<double> orig_list;
  s21::List<double> my_move(std::move(my_list));
  std::list<double> orig_move(std::move(orig_list));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_EQ(my_move.Empty(), orig_move.empty());
}

TEST(list, move_operator_test) {
  s21::List<char> my_list{'c', '%', '2'};
  std::list<char> orig_list{'c', '%', '2'};
  s21::List<char> my_move{'g', 'w', '^', '*'};
  std::list<char> orig_move{'g', 'w', '^', '*'};
  my_move = std::move(my_list);
  orig_move = std::move(orig_list);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_TRUE(compare_lists(my_move, orig_move));
}

TEST(list, push_back_test_1) {
  s21::List<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  my_list.PushBack(7.67);
  orig_list.push_back(7.67);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, push_back_test_2) {
  s21::List<std::string> my_list{"Blacksad", "Weekly"};
  std::list<std::string> orig_list{"Blacksad", "Weekly"};
  my_list.PushBack("Smirnov");
  my_list.PushBack("Fiston");
  orig_list.push_back("Smirnov");
  orig_list.push_back("Fiston");
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, push_front_test_1) {
  s21::List<int> my_list{1345, 56789, 6788, 9090};
  std::list<int> orig_list{1345, 56789, 6788, 9090};
  my_list.PushFront(1000);
  orig_list.push_front(1000);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, push_front_test_2) {
  s21::List<char> my_list;
  std::list<char> orig_list;
  my_list.PushFront('a');
  orig_list.push_front('a');
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
}

TEST(list, pop_back_test_1) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.PopBack();
  orig_list.pop_back();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, pop_back_test_2) {
  s21::List<float> my_list{0.6};
  std::list<float> orig_list{0.6};
  my_list.PopBack();
  orig_list.pop_back();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
  ASSERT_TRUE(my_list.Empty());
}

TEST(list, pop_front_test_1) {
  s21::List<int> my_list{56, -33, 1, 34, 12, 91};
  std::list<int> orig_list{56, -33, 1, 34, 12, 91};
  my_list.PopFront();
  orig_list.pop_front();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, pop_front_test_2) {
  s21::List<std::string> my_list{"list", "stack", "map"};
  std::list<std::string> orig_list{"list", "stack", "map"};
  my_list.PopFront();
  orig_list.pop_front();
  my_list.PopFront();
  orig_list.pop_front();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, clear_test) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.Clear();
  orig_list.clear();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
  ASSERT_TRUE(my_list.Empty());
}

TEST(list, iterator_insert_test_1) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.Insert(++my_list.Begin(), -9);
  orig_list.insert(++orig_list.begin(), -9);
  auto orig = orig_list.begin();
  for (auto it = my_list.Begin(); it != my_list.End(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, iterator_insert_test_2) {
  s21::List<double> my_list{1.8, 77.7, 6.67, 0.88};
  std::list<double> orig_list{1.8, 77.7, 6.67, 0.88};
  my_list.Insert(my_list.Begin(), -3.33);
  orig_list.insert(orig_list.begin(), -3.33);
  my_list.Insert(my_list.End(), 21.5);
  orig_list.insert(orig_list.end(), 21.5);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  auto orig = orig_list.begin();
  for (auto it = my_list.Begin(); it != my_list.End(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, iterator_insert_test_3) {
  s21::List<int> my_list;
  std::list<int> orig_list;
  my_list.Insert(my_list.Begin(), 111);
  orig_list.insert(orig_list.begin(), 111);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  auto orig = orig_list.begin();
  for (auto it = my_list.Begin(); it != my_list.End(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, erase_test_1) {
  s21::List<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  auto it1 = my_list.Begin();
  my_list.Erase(++it1);
  auto it2 = orig_list.begin();
  orig_list.erase(++it2);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, erase_test_2) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.Erase(my_list.Begin());
  orig_list.erase(orig_list.begin());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, erase_test_3) {
  s21::List<char> my_list{'x', 'y', 'z', 'o'};
  std::list<char> orig_list{'x', 'y', 'z', 'o'};
  auto it1 = my_list.Begin();
  ++it1;
  ++it1;
  my_list.Erase(++it1);
  auto it2 = orig_list.end();
  orig_list.erase(--it2);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, swap_test_1) {
  s21::List<double> my_list;
  std::list<double> orig_list;
  s21::List<double> my_swap{0.3};
  std::list<double> orig_swap{0.3};
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
  ASSERT_EQ(my_list.Size(), orig_list.size());
  my_swap.Swap(my_list);
  orig_swap.swap(orig_list);
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  ASSERT_EQ(my_swap.Empty(), orig_swap.empty());
  ASSERT_TRUE(my_swap.Empty());
}

TEST(list, swap_test_2) {
  s21::List<int> my_list{67, -7, 21};
  std::list<int> orig_list{67, -7, 21};
  s21::List<int> my_swap{1, 2, 3, 4, 5};
  std::list<int> orig_swap{1, 2, 3, 4, 5};
  my_swap.Swap(my_list);
  orig_swap.swap(orig_list);
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  ASSERT_TRUE(compare_lists(my_swap, orig_swap));
}

TEST(list, sort_test) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  orig_list.sort();
  my_list.Sort();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, reverse_test) {
  s21::List<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  orig_list.reverse();
  my_list.Reverse();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, unique_test_1) {
  s21::List<int> my_list{1, 1, -3, 1, 67, 67, 67, 3, 1, 1};
  std::list<int> orig_list{1, 1, -3, 1, 67, 67, 67, 3, 1, 1};
  orig_list.unique();
  my_list.Unique();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, unique_test_2) {
  s21::List<char> my_list{'a', 'b', 'd', 'd', 'i', 'a', 'a', 'c'};
  std::list<char> orig_list{'a', 'b', 'd', 'd', 'i', 'a', 'a', 'c'};
  orig_list.unique();
  my_list.Unique();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, splice_test_1) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  std::list<int> orig_list{1, 2, 3, 4, 5};
  s21::List<int> my_add{6, 7, 8};
  std::list<int> orig_add{6, 7, 8};
  orig_list.splice(orig_list.cend(), orig_add);
  my_list.Splice(my_list.Cend(), my_add);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, splice_test_2) {
  s21::List<char> my_list{'l', 'i', 's', 't'};
  std::list<char> orig_list{'l', 'i', 's', 't'};
  s21::List<char> my_add{'c', '+', '+'};
  std::list<char> orig_add{'c', '+', '+'};
  orig_list.splice(orig_list.cbegin(), orig_add);
  my_list.Splice(my_list.Cbegin(), my_add);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, splice_test_3) {
  s21::List<int> my_list;
  std::list<int> orig_list;
  s21::List<int> my_add{1, 2, 3};
  std::list<int> orig_add{1, 2, 3};
  orig_list.splice(orig_list.cbegin(), orig_add);
  my_list.Splice(my_list.Cbegin(), my_add);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, splice_test_4) {
  s21::List<double> my_list{0.01, -0.2, 1.98};
  std::list<double> orig_list{0.01, -0.2, 1.98};
  s21::List<double> my_add{3.33, 2.22};
  std::list<double> orig_add{3.33, 2.22};
  orig_list.splice(++orig_list.cbegin(), orig_add);
  my_list.Splice(++my_list.Cbegin(), my_add);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, merge_test_1) {
  s21::List<double> my_list{0.01, -0.2, 1.98};
  std::list<double> orig_list{0.01, -0.2, 1.98};
  s21::List<double> my_add{3.33, 2.22};
  std::list<double> orig_add{3.33, 2.22};
  orig_list.merge(orig_add);
  my_list.Merge(my_add);
  orig_list.sort();
  my_list.Sort();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, merge_test_2) {
  s21::List<int> my_list;
  std::list<int> orig_list;
  s21::List<int> my_add{21, 135, 0, -15};
  std::list<int> orig_add{21, 135, 0, -15};
  orig_list.merge(orig_add);
  my_list.Merge(my_add);
  orig_list.sort();
  my_list.Sort();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, merge_test_3) {
  s21::List<int> my_list{5, 89, -33, 784, 0, 45};
  std::list<int> orig_list{5, 89, -33, 784, 0, 45};
  s21::List<int> my_add{5, 89, -33, 784, 0, 45};
  std::list<int> orig_add{5, 89, -33, 784, 0, 45};
  orig_list.merge(orig_add);
  my_list.Merge(my_add);
  orig_list.sort();
  my_list.Sort();
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, iterator_operator_test_1) {
  s21::List<double> my_list{0.99, 8.56, -3.45, 1.34};
  std::list<double> orig_list{0.99, 8.56, -3.45, 1.34};
  s21::List<double>::Iterator it_my = my_list.Begin()++;
  std::list<double>::iterator it_orig = orig_list.begin()++;
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(list, const_iterator_operator_test_1) {
  s21::List<int> my_list{1, 9, 34, 8};
  std::list<int> orig_list{1, 9, 34, 8};
  s21::List<int>::ConstIterator it_my = ++my_list.Cbegin();
  std::list<int>::const_iterator it_orig = ++orig_list.cbegin();
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(list, const_iterator_operator_test_2) {
  s21::List<int> my_list{1, 9, 34, 8, 56, 89};
  std::list<int> orig_list{1, 9, 34, 8, 56, 89};
  s21::List<int>::ConstIterator it_my = ++my_list.Cbegin();
  std::list<int>::const_iterator it_orig = ++orig_list.cbegin();
  ASSERT_EQ(*(it_my + 1), *(++it_orig));
}

TEST(list, const_iterator_operator_test_3) {
  s21::List<int> my_list{1, 9, 34, 8, 56, 89};
  std::list<int> orig_list{1, 9, 34, 8, 56, 89};
  s21::List<int>::ConstIterator it_my = my_list.Cbegin();
  std::list<int>::const_iterator it_orig = orig_list.cbegin();
  it_my.operator++(3);
  it_orig.operator++(3);
  --it_my;
  --it_orig;
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(list, iterator_emplace_test_1) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.Emplace(my_list.Cbegin(), 9);
  orig_list.emplace(orig_list.cbegin(), 9);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());

  auto orig = orig_list.cbegin();
  for (auto it = my_list.Cbegin(); it != my_list.Cend(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, iterator_emplace_test_2) {
  s21::List<double> my_list{0.44, -0.1};
  std::list<double> orig_list{0.44, -0.1};
  my_list.Emplace(my_list.Cend(), 3.33);
  orig_list.emplace(orig_list.cend(), 3.33);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, iterator_emplace_test_3) {
  s21::List<double> my_list{0.44, -0.1};
  std::list<double> orig_list{0.44, -0.1};
  my_list.Emplace(++my_list.Cbegin(), 3.33);
  orig_list.emplace(++orig_list.cbegin(), 3.33);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, emplace_back_test_1) {
  s21::List<std::string> my_list{"Blacksad", "Weekly"};
  std::list<std::string> orig_list{"Blacksad", "Weekly"};
  my_list.EmplaceBack("Smirnov");
  orig_list.emplace_back("Smirnov");
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, emplace_back_test_2) {
  s21::List<int> my_list;
  std::list<int> orig_list;
  my_list.EmplaceBack(0);
  orig_list.emplace_back(0);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Back(), orig_list.back());
  ASSERT_EQ(my_list.Empty(), orig_list.empty());
  ASSERT_FALSE(my_list.Empty());
}

TEST(list, emplace_front_test_1) {
  s21::List<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.EmplaceFront(0);
  orig_list.emplace_front(0);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
  ASSERT_TRUE(compare_lists(my_list, orig_list));
}

TEST(list, emplace_front_test_2) {
  s21::List<double> my_list;
  std::list<double> orig_list;
  my_list.EmplaceFront(0.77);
  orig_list.emplace_front(0.77);
  ASSERT_EQ(my_list.Size(), orig_list.size());
  ASSERT_EQ(my_list.Front(), orig_list.front());
}

// MAP--------------------------------------------------------------------------

TEST(map, default_constructor_test) {
  s21::Map<int, char> my_map;
  std::map<int, char> orig_map;
  ASSERT_EQ(my_map.Size(), orig_map.size());
  ASSERT_EQ(my_map.Empty(), orig_map.empty());
}

TEST(map, initializer_list_constructor_test_1) {
  s21::Map<int, char> my_map{{1, 'f'}, {2, 't'}, {3, 'o'}};
  std::map<int, char> orig_map{{1, 'f'}, {2, 't'}, {3, 'o'}};
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, initializer_list_constructor_test_2) {
  s21::Map<int, std::string> my_map{
      {4, "fourth"},
      {1, "first"},
      {8, "eighth"},
      {3, "third"},
  };
  std::map<int, std::string> orig_map{
      {4, "fourth"},
      {1, "first"},
      {8, "eighth"},
      {3, "third"},
  };
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, copy_constructor_test) {
  s21::Map<int, char> my_map{{11, 'r'}, {8, 's'}, {17, 'p'}};
  std::map<int, char> orig_map{{11, 'r'}, {8, 's'}, {17, 'p'}};
  s21::Map<int, char> my_copy(my_map);
  std::map<int, char> orig_copy(orig_map);
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  auto it = my_copy.Begin();
  auto orig = orig_copy.begin();
  for (; orig != orig_copy.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, move_constructor_test) {
  s21::Map<int, double> my_map{{3, 6.890075}, {2, 12.6790}, {6, 5.89065}};
  std::map<int, double> orig_map{{3, 6.890075}, {2, 12.6790}, {6, 5.89065}};
  s21::Map<int, double> my_move(std::move(my_map));
  std::map<int, double> orig_move(std::move(orig_map));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  auto it = my_move.Begin();
  auto orig = orig_move.begin();
  for (; orig != orig_move.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, move_operator_test) {
  s21::Map<int, char> my_map{{11, 'r'}, {8, 's'}, {17, 'p'}};
  std::map<int, char> orig_map{{11, 'r'}, {8, 's'}, {17, 'p'}};
  s21::Map<int, char> my_move{{1, 'a'}, {2, 'b'}};
  std::map<int, char> orig_move{{1, 'a'}, {2, 'b'}};
  my_move = std::move(my_map);
  orig_move = std::move(orig_map);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  auto it = my_move.Begin();
  auto orig = orig_move.begin();
  for (; orig != orig_move.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, at_test_1) {
  s21::Map<int, char> my_map{{5, 'a'}, {1, 'b'}, {7, 'c'}, {3, 'f'}};
  std::map<int, char> orig_map{{5, 'a'}, {1, 'b'}, {7, 'c'}, {3, 'f'}};
  ASSERT_EQ(my_map.At(5), orig_map.at(5));
  ASSERT_EQ(my_map.At(1), orig_map.at(1));
  ASSERT_EQ(my_map.At(7), orig_map.at(7));
  ASSERT_EQ(my_map.At(3), orig_map.at(3));
}

TEST(map, at_test_2) {
  s21::Map<int, char> my_map{{5, 'a'}, {1, 'b'}, {7, 'c'}, {3, 'f'}};
  std::map<int, char> orig_map{{5, 'a'}, {1, 'b'}, {7, 'c'}, {3, 'f'}};
  ASSERT_EQ(my_map.At(5), orig_map.at(5));
  my_map.At(5) = 'g';
  orig_map.at(5) = 'g';
  my_map.At(3) = 'y';
  orig_map.at(3) = 'y';
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, square_brackets_test_1) {
  s21::Map<int, std::string> my_map{
      {4, "second"},
      {1, "first"},
      {3, "third"},
  };
  std::map<int, std::string> orig_map{
      {4, "second"},
      {1, "first"},
      {3, "third"},
  };
  ASSERT_EQ(my_map[4], orig_map[4]);
  my_map[4] = "fourth";
  orig_map[4] = "fourth";
  ASSERT_EQ(my_map[4], orig_map[4]);
  ASSERT_EQ(my_map[1], orig_map[1]);
  ASSERT_EQ(my_map[3], orig_map[3]);
}

TEST(map, square_brackets_test_2) {
  s21::Map<int, std::string> my_map{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  std::map<int, std::string> orig_map{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  my_map[5] = "five";
  orig_map[5] = "five";
  ASSERT_EQ(my_map[5], orig_map[5]);
}

TEST(map, clear_test) {
  s21::Map<int, char> my_map{{1, 'f'}, {2, 't'}, {3, 'o'}};
  std::map<int, char> orig_map{{1, 'f'}, {2, 't'}, {3, 'o'}};
  ASSERT_EQ(my_map.Size(), orig_map.size());
  my_map.Clear();
  orig_map.clear();
  ASSERT_EQ(my_map.Empty(), orig_map.empty());
  ASSERT_TRUE(my_map.Empty());
}

TEST(map, insert_test_1) {
  s21::Map<int, char> my_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  std::map<int, char> orig_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  my_map.Insert(std::pair<int, char>(7, 'd'));
  orig_map.insert(std::pair<int, char>(7, 'd'));
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, insert_test_2) {
  s21::Map<int, char> my_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  std::map<int, char> orig_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  my_map.Insert(std::pair<int, char>(5, 'a'));
  orig_map.insert(std::pair<int, char>(5, 'a'));
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, insert_test_3) {
  s21::Map<int, std::string> my_map;
  std::map<int, std::string> orig_map;
  my_map.Insert(1, "one");
  orig_map.insert(std::pair<int, std::string>(1, "one"));
  ASSERT_EQ(my_map.Size(), orig_map.size());
  ASSERT_TRUE(my_map.Contains(1));
  ASSERT_EQ(my_map[1], "one");
}

TEST(map, insert_test_4) {
  s21::Map<int, std::string> my_map{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  std::map<int, std::string> orig_map{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  std::pair<s21::Map<int, std::string>::Iterator, bool> it_my =
      my_map.Insert({5, "five"});
  std::pair<std::map<int, std::string>::iterator, bool> it_orig =
      orig_map.insert({5, "five"});
  EXPECT_TRUE(it_my.second == it_orig.second);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, insert_or_assign_test_1) {
  s21::Map<char, std::string> my_map{
      {'c', "cherry"}, {'a', "apple"}, {'b', "banana"}};
  std::map<char, std::string> orig_map{
      {'c', "cherry"}, {'a', "apple"}, {'b', "banana"}};
  my_map.InsertOrAssign('a', "apricot");
  orig_map.insert_or_assign('a', "apricot");
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, insert_or_assign_test_2) {
  s21::Map<int, int> my_map({{1, 3}, {4, 2}});
  std::map<int, int> orig_map({{1, 3}, {4, 2}});
  std::pair<s21::Map<int, int>::Iterator, bool> it_my =
      my_map.InsertOrAssign(5, 2);
  std::pair<std::map<int, int>::iterator, bool> it_orig =
      orig_map.insert_or_assign(5, 2);
  ASSERT_TRUE(it_my.second == it_orig.second);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_1) {
  s21::Map<int, char> my_map{{8, 'a'}, {3, 'b'}, {10, 'c'}, {1, 'd'}};
  std::map<int, char> orig_map{{8, 'a'}, {3, 'b'}, {10, 'c'}, {1, 'd'}};
  my_map.Erase(++my_map.Begin());
  orig_map.erase(++orig_map.begin());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_2) {
  s21::Map<int, char> my_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  std::map<int, char> orig_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  s21::Map<int, char>::Iterator it1 = ++my_map.Begin();
  std::map<int, char>::iterator it2 = ++orig_map.begin();
  my_map.Erase(++it1);
  orig_map.erase(++it2);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_3) {
  s21::Map<int, char> my_map{{8, 'a'}, {3, 'b'}, {10, 'c'},
                             {6, 'd'}, {1, 'e'}, {4, 'f'}};
  std::map<int, char> orig_map{{8, 'a'}, {3, 'b'}, {10, 'c'},
                               {6, 'd'}, {1, 'e'}, {4, 'f'}};
  my_map.Erase(++my_map.Begin());
  orig_map.erase(++orig_map.begin());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_4) {
  s21::Map<char, std::string> my_map{
      {'c', "cherry"}, {'a', "apple"}, {'b', "banana"}};
  std::map<char, std::string> orig_map{
      {'c', "cherry"}, {'a', "apple"}, {'b', "banana"}};
  my_map.Erase(my_map.Begin());
  orig_map.erase(orig_map.begin());
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_5) {
  s21::Map<int, char> my_map{{5, 'a'}, {2, 'b'}, {3, 'c'}, {0, 'd'}};
  std::map<int, char> orig_map{{5, 'a'}, {2, 'b'}, {3, 'c'}, {0, 'd'}};
  s21::Map<int, char>::Iterator it1 = ++my_map.Begin();
  std::map<int, char>::iterator it2 = ++orig_map.begin();
  ++it1;
  ++it2;
  my_map.Erase(++it1);
  orig_map.erase(++it2);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, erase_test_6) {
  s21::Map<char, std::string> my_map{{'a', "apple"}};
  std::map<char, std::string> orig_map{{'a', "apple"}};
  my_map.Erase(my_map.Begin());
  orig_map.erase(orig_map.begin());
  ASSERT_EQ(my_map.Size(), orig_map.size());
  ASSERT_EQ(my_map.Empty(), orig_map.empty());
  ASSERT_TRUE(my_map.Empty());
}

TEST(map, erase_test_7) {
  s21::Map<int, char> my_map{{1, 'a'}, {2, 'h'}, {3, 'o'}, {6, 'f'}, {7, 't'}};
  std::map<int, char> orig_map{
      {1, 'a'}, {2, 'h'}, {3, 'o'}, {6, 'f'}, {7, 't'}};
  s21::Map<int, char>::Iterator it1 = ++my_map.Begin();
  std::map<int, char>::iterator it2 = ++orig_map.begin();
  my_map.Erase(++it1);
  orig_map.erase(++it2);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, merge_test_1) {
  s21::Map<int, char> my_map{{8, 'a'}, {3, 'b'}, {10, 'c'}};
  std::map<int, char> orig_map{{8, 'a'}, {3, 'b'}, {10, 'c'}};
  s21::Map<int, char> my_add{{8, 'a'}, {1, 't'}, {5, 'r'}};
  std::map<int, char> orig_add{{8, 'a'}, {1, 't'}, {5, 'r'}};
  my_map.Merge(my_add);
  orig_map.merge(orig_add);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, merge_test_2) {
  s21::Map<char, std::string> my_map{{'c', "cherry"}};
  std::map<char, std::string> orig_map{{'c', "cherry"}};
  s21::Map<char, std::string> my_add{{'a', "apple"}, {'b', "banana"}};
  std::map<char, std::string> orig_add{{'a', "apple"}, {'b', "banana"}};
  my_map.Merge(my_add);
  orig_map.merge(orig_add);
  ASSERT_EQ(my_map.Size(), orig_map.size());
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, merge_test_3) {
  s21::Map<int, char> my_map{{8, 'a'}, {3, 'b'}, {10, 'c'}};
  std::map<int, char> orig_map{{8, 'a'}, {3, 'b'}, {10, 'c'}};
  s21::Map<int, char> my_add;
  std::map<int, char> orig_add;
  my_map.Merge(my_add);
  orig_map.merge(orig_add);
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

TEST(map, emplace_test) {
  s21::Map<int, int> my_map{{1, 3}, {4, 2}};
  std::map<int, int> orig_map{{1, 3}, {4, 2}};
  my_map.Emplace(std::pair<int, int>(5, 5));
  orig_map.emplace(std::pair<int, int>(5, 5));
  auto it = my_map.Begin();
  auto orig = orig_map.begin();
  for (; orig != orig_map.end(); ++it, ++orig) {
    ASSERT_EQ(it->first, orig->first);
    ASSERT_EQ(it->second, orig->second);
  }
}

// MULTISET---------------------------------------------------------------------

template <typename value_type>
bool compare_multisets(s21::Multiset<value_type> my_multiset,
                       std::multiset<value_type> orig_multiset) {
  if (my_multiset.Size() != orig_multiset.size()) {
    return false;
  }
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    if (*it != *orig) {
      return false;
    }
  }
  return true;
}

TEST(multiset, default_constructor_test) {
  s21::Multiset<int> my_multiset;
  std::multiset<int> orig_multiset;
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  ASSERT_EQ(my_multiset.Empty(), orig_multiset.empty());
}

TEST(multiset, initializer_list_constructor_test) {
  s21::Multiset<int> my_multiset{1, 0, 45, 0, 67, 0, 8, 123};
  std::multiset<int> orig_multiset{1, 0, 45, 0, 67, 0, 8, 123};
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, copy_constructor_test) {
  s21::Multiset<int> my_multiset{10, 8, 3, 3, -45, 3};
  std::multiset<int> orig_multiset{10, 8, 3, 3, -45, 3};
  s21::Multiset<int> my_copy(my_multiset);
  std::multiset<int> orig_copy(orig_multiset);
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  auto it = my_copy.Begin();
  auto orig = orig_copy.begin();
  for (; orig != orig_copy.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, move_constructor_test_1) {
  s21::Multiset<double> my_multiset{0.456, 7.456, -3.333, 4.004, -3.333};
  std::multiset<double> orig_multiset{0.456, 7.456, -3.333, 4.004, -3.333};
  s21::Multiset<double> my_move(std::move(my_multiset));
  std::multiset<double> orig_move(std::move(orig_multiset));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  auto it = my_move.Begin();
  auto orig = orig_move.begin();
  for (; orig != orig_move.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, move_constructor_test_2) {
  s21::Multiset<int> my_multiset{11, 12, 18, 11, 19, 21, 8};
  std::multiset<int> orig_multiset{11, 12, 18, 11, 19, 21, 8};
  s21::Multiset<int> my_move{-4, -2, -8, -4, -11};
  std::multiset<int> orig_move{-4, -2, -8, -4, -11};
  my_move = std::move(my_multiset);
  orig_move = std::move(orig_multiset);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  auto it = my_move.Begin();
  auto orig = orig_move.begin();
  for (; orig != orig_move.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, swap_constructor_test_1) {
  s21::Multiset<int> my_multiset{10, 11, 10, 15, 10};
  std::multiset<int> orig_multiset{10, 11, 10, 15, 10};
  s21::Multiset<int> my_swap{6, 3, 6, 3, 6, 3};
  std::multiset<int> orig_swap{6, 3, 6, 3, 6, 3};
  my_swap.Swap(my_multiset);
  orig_swap.swap(orig_multiset);
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  auto it = my_swap.Begin();
  auto orig = orig_swap.begin();
  for (; orig != orig_swap.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, insert_test_1) {
  s21::Multiset<int> my_multiset{21, 21, 21, 21};
  std::multiset<int> orig_multiset{21, 21, 21, 21};
  my_multiset.Insert(21);
  orig_multiset.insert(21);
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, insert_test_2) {
  s21::Multiset<char> my_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  std::multiset<char> orig_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  my_multiset.Insert('o');
  my_multiset.Insert('o');
  orig_multiset.insert('o');
  orig_multiset.insert('o');
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, insert_test_3) {
  s21::Multiset<int> my_multiset;
  std::multiset<int> orig_multiset;
  my_multiset.Insert(21);
  my_multiset.Insert(21);
  my_multiset.Insert(0);
  orig_multiset.insert(21);
  orig_multiset.insert(21);
  orig_multiset.insert(0);
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, erase_test_1) {
  s21::Multiset<int> my_multiset{21, 33, 28, 46, 18};
  std::multiset<int> orig_multiset{21, 33, 28, 46, 18};
  s21::Multiset<int>::Iterator it1 = my_multiset.Begin();
  std::multiset<int>::iterator it2 = orig_multiset.begin();
  my_multiset.Erase(++it1);
  orig_multiset.erase(++it2);
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, erase_test_2) {
  s21::Multiset<double> my_multiset{3.3, 1.22, 4.6, 0.8};
  std::multiset<double> orig_multiset{3.3, 1.22, 4.6, 0.8};
  my_multiset.Erase(my_multiset.Find(4.6));
  orig_multiset.erase(orig_multiset.find(4.6));
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, erase_test_3) {
  s21::Multiset<int> my_multiset{3, 1, 2};
  std::multiset<int> orig_multiset{3, 1, 2};
  my_multiset.Erase(my_multiset.Find(3));
  orig_multiset.erase(orig_multiset.find(3));
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, erase_test_4) {
  s21::Multiset<int> my_multiset{3, 1, 0};
  std::multiset<int> orig_multiset{3, 1, 0};
  my_multiset.Erase(my_multiset.Find(1));
  orig_multiset.erase(orig_multiset.find(1));
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, merge_test_1) {
  s21::Multiset<int> my_multiset{1, 4, 5, 7};
  s21::Multiset<int> my_add{2, 3, 6, 7};
  // std::multiset<int> orig_multiset{1, 4, 5, 7, 2, 3, 6, 7};
  std::multiset<int> orig_multiset{1, 4, 5, 7};
  std::multiset<int> orig_add{2, 3, 6, 7};
  my_multiset.Merge(my_add);
  orig_multiset.merge(orig_add);
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, merge_test_2) {
  s21::Multiset<int> my_multiset;
  s21::Multiset<int> my_add{21, 21, 45, 31};
  // std::multiset<int> orig_multiset{21, 21, 45, 31};
  std::multiset<int> orig_multiset;
  std::multiset<int> orig_add{21, 21, 45, 31};
  my_multiset.Merge(my_add);
  orig_multiset.merge(orig_add);
  ASSERT_EQ(my_multiset.Size(), orig_multiset.size());
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, find_test_1) {
  s21::Multiset<char> my_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  std::multiset<char> orig_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  s21::Multiset<char>::Iterator it1 = my_multiset.Find('o');
  std::multiset<char>::iterator it2 = orig_multiset.find('o');
  ASSERT_EQ(*it1, *it2);
}

TEST(multiset, count_test_1) {
  s21::Multiset<char> my_multiset;
  std::multiset<char> orig_multiset;
  ASSERT_EQ(my_multiset.Count(3), orig_multiset.count(3));
}

TEST(multiset, count_test_2) {
  s21::Multiset<int> my_multiset{8, 8, 5, 1, 8};
  std::multiset<int> orig_multiset{8, 8, 5, 1, 8};
  ASSERT_EQ(my_multiset.Count(8), orig_multiset.count(8));
}

TEST(multiset, count_test_3) {
  s21::Multiset<double> my_multiset{3.3, 1.22, 3.3, 4.6, 0.8};
  std::multiset<double> orig_multiset{3.3, 1.22, 3.3, 4.6, 0.8};
  ASSERT_EQ(my_multiset.Count(0.8), orig_multiset.count(0.8));
}

TEST(multiset, contains_test_1) {
  s21::Multiset<int> my_multiset{50, 10, 40, 5, 5, 15};
  ASSERT_TRUE(my_multiset.Contains(5));
}

TEST(multiset, contains_test_2) {
  s21::Multiset<int> my_multiset{50, 10, 40, 5, 5, 15};
  ASSERT_FALSE(my_multiset.Contains(0));
}

TEST(multiset, lower_bound_test_1) {
  s21::Multiset<int> my_multiset{50, 10, 40, 5, 5, 15};
  std::multiset<int> orig_multiset{50, 10, 40, 5, 5, 15};
  ASSERT_EQ(*my_multiset.LowerBound(5), *orig_multiset.lower_bound(5));
}

TEST(multiset, lower_bound_test_2) {
  s21::Multiset<char> my_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  std::multiset<char> orig_multiset{'s', 'c', 'h', 'o', 'o', 'l'};
  ASSERT_EQ(*my_multiset.LowerBound('r'), *orig_multiset.lower_bound('r'));
}

TEST(multiset, upper_bound_test_1) {
  s21::Multiset<int> my_multiset{50, 25, 75, 5, 5, 15};
  std::multiset<int> orig_multiset{50, 25, 75, 5, 5, 15};
  ASSERT_EQ(*my_multiset.UpperBound(74), *orig_multiset.upper_bound(74));
}

TEST(multiset, equal_range_test_1) {
  s21::Multiset<int> my_multiset{50, 25, 75, 10, 40, 5, 5, 15};
  std::multiset<int> orig_multiset{50, 25, 75, 10, 40, 5, 5, 15};
  auto it = my_multiset.EqualRange(3);
  auto orig = orig_multiset.equal_range(3);
  ASSERT_EQ(*it.first, *orig.first);
  ASSERT_EQ(*it.second, *orig.second);
}

TEST(multiset, emplace_test_1) {
  s21::Multiset<double> my_multiset{3.3, 1.22, 4.6, 0.8};
  std::multiset<double> orig_multiset{3.3, 1.22, 4.6, 0.8};
  my_multiset.Emplace(3.3);
  orig_multiset.emplace(3.3);
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(multiset, emplace_test_2) {
  s21::Multiset<double> my_multiset{0.8, 1.22, 0.8, 0.8};
  std::multiset<double> orig_multiset{0.8, 1.22, 0.8, 0.8};
  my_multiset.Emplace(0.8786);
  orig_multiset.emplace(0.8786);
  my_multiset.Emplace(1.11111111);
  orig_multiset.emplace(1.11111111);
  auto it = my_multiset.Begin();
  auto orig = orig_multiset.begin();
  for (; orig != orig_multiset.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

// QUEUE------------------------------------------------------------------------

TEST(queue, default_constructor_test) {
  s21::Queue<int> my_queue;
  std::queue<int> orig_queue;
  ASSERT_EQ(my_queue.Empty(), orig_queue.empty());
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
}

TEST(queue, initializer_list_constructor_test) {
  s21::Queue<int> my_queue{21, 456, -89, 67};
  std::queue<int> orig_queue;
  orig_queue.push(21);
  orig_queue.push(456);
  orig_queue.push(-89);
  orig_queue.push(67);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  while (!my_queue.Empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.Front(), orig_queue.front());
    my_queue.Pop();
    orig_queue.pop();
  }
  ASSERT_EQ(my_queue.Empty(), orig_queue.empty());
}

TEST(queue, copy_constructor_test_1) {
  s21::Queue<int> my_queue;
  std::queue<int> orig_queue;
  s21::Queue<int> my_copy(my_queue);
  std::queue<int> orig_copy(orig_queue);
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
}

TEST(queue, copy_constructor_test_2) {
  s21::Queue<double> my_queue;
  std::queue<double> orig_queue;
  my_queue.Push(0.88);
  my_queue.Push(3.33);
  my_queue.Push(-11.45);
  orig_queue.push(0.88);
  orig_queue.push(3.33);
  orig_queue.push(-11.45);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  s21::Queue<double> my_copy(my_queue);
  std::queue<double> orig_copy(orig_queue);
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  while (!my_copy.Empty() && !orig_copy.empty()) {
    ASSERT_EQ(my_copy.Front(), orig_copy.front());
    my_copy.Pop();
    orig_copy.pop();
  }
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
}

TEST(queue, move_constructor_test) {
  s21::Queue<int> my_queue;
  std::queue<int> orig_queue;
  for (int i = 0; i < 8; ++i) {
    my_queue.Push(i);
    orig_queue.push(i);
  }
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  s21::Queue<int> my_move(std::move(my_queue));
  std::queue<int> orig_move(std::move(orig_queue));
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  ASSERT_EQ(my_move.Size(), orig_move.size());
  while (!my_move.Empty() && !orig_move.empty()) {
    ASSERT_EQ(my_move.Front(), orig_move.front());
    my_move.Pop();
    orig_move.pop();
  }
}

TEST(queue, move_operator_test) {
  s21::Queue<char> my_queue;
  std::queue<char> orig_queue;
  my_queue.Push('a');
  my_queue.Push('b');
  my_queue.Push('c');
  my_queue.Push('d');
  orig_queue.push('a');
  orig_queue.push('b');
  orig_queue.push('c');
  orig_queue.push('d');
  s21::Queue<char> my_move{'h'};
  std::queue<char> orig_move;
  orig_move.push('h');
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  ASSERT_EQ(my_move.Size(), orig_move.size());
  my_move = std::move(my_queue);
  orig_move = std::move(orig_queue);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  while (!my_move.Empty() && !orig_move.empty()) {
    ASSERT_EQ(my_move.Front(), orig_move.front());
    my_move.Pop();
    orig_move.pop();
  }
}

TEST(queue, swap_test_1) {
  s21::Queue<int> my_queue;
  std::queue<int> orig_queue;
  s21::Queue<int> my_swap;
  std::queue<int> orig_swap;
  ASSERT_EQ(my_queue.Empty(), orig_queue.empty());
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  my_swap.Swap(my_queue);
  orig_swap.swap(orig_queue);
  ASSERT_EQ(my_swap.Empty(), orig_swap.empty());
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
}

TEST(queue, swap_test_2) {
  s21::Queue<char> my_queue;
  std::queue<char, std::list<char>> orig_queue;
  my_queue.Push('a');
  my_queue.Push('b');
  my_queue.Push('c');
  my_queue.Push('d');
  orig_queue.push('a');
  orig_queue.push('b');
  orig_queue.push('c');
  orig_queue.push('d');
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  s21::Queue<char> my_swap{'x', 'y', 'z'};
  std::list<char> tmp{'x', 'y', 'z'};
  std::queue<char, std::list<char>> orig_swap(tmp);
  my_swap.Swap(my_queue);
  orig_swap.swap(orig_queue);
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  while (!my_swap.Empty() && !orig_swap.empty()) {
    ASSERT_EQ(my_swap.Front(), orig_swap.front());
    my_swap.Pop();
    orig_swap.pop();
  }
  ASSERT_EQ(my_swap.Empty(), orig_swap.empty());
}

TEST(queue, front_test) {
  s21::Queue<int> my_queue{0, 1, 4, 77, 5, 33};
  std::list<int> tmp{0, 1, 4, 77, 5, 33};
  std::queue<int, std::list<int>> orig_queue(tmp);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  while (!my_queue.Empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.Front(), orig_queue.front());
    my_queue.Pop();
    orig_queue.pop();
  }
  ASSERT_EQ(my_queue.Empty(), orig_queue.empty());
}

TEST(queue, push_test) {
  s21::Queue<double> my_queue{0.78, 3.33, -5.35, 8.845, -0.99, 1.11};
  std::list<double> tmp{0.78, 3.33, -5.35, 8.845, -0.99, 1.11};
  std::queue<double, std::list<double>> orig_queue(tmp);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  my_queue.Push(0.33);
  orig_queue.push(0.33);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  ASSERT_EQ(my_queue.Back(), orig_queue.back());

  while (!my_queue.Empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.Front(), orig_queue.front());
    my_queue.Pop();
    orig_queue.pop();
  }
}

TEST(queue, emplace_back_test) {
  s21::Queue<int> my_queue{23456, 545, 444, 678};
  std::list<int> tmp{23456, 545, 444, 678};
  std::queue<int, std::list<int>> orig_queue(tmp);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  my_queue.EmplaceBack(123);
  my_queue.EmplaceBack(-5466);
  orig_queue.emplace(123);
  orig_queue.emplace(-5466);
  ASSERT_EQ(my_queue.Size(), orig_queue.size());
  ASSERT_EQ(my_queue.Back(), orig_queue.back());

  while (!my_queue.Empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.Front(), orig_queue.front());
    my_queue.Pop();
    orig_queue.pop();
  }
}

// SET--------------------------------------------------------------------------

template <typename value_type>
bool compare_sets(s21::Set<value_type> my_set, std::set<value_type> orig_set) {
  if (my_set.Size() != orig_set.size()) {
    return false;
  }
  auto it = my_set.Begin();
  auto orig = orig_set.begin();
  for (; orig != orig_set.end(); ++it, ++orig) {
    if (*it != *orig) {
      return false;
    }
  }
  return true;
}

TEST(set, default_constructor_test) {
  s21::Set<int> my_set;
  std::set<int> orig_set;
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_EQ(my_set.Empty(), orig_set.empty());
}

TEST(set, initializer_list_constructor_test) {
  s21::Set<int> my_set{1, 21, 45, 0, 67, -33, 8, 123};
  std::set<int> orig_set{1, 21, 45, 0, 67, -33, 8, 123};
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, copy_constructor_test) {
  s21::Set<int> my_set{10, 8, -45, 3};
  std::set<int> orig_set{10, 8, -45, 3};
  s21::Set<int> my_copy(my_set);
  std::set<int> orig_copy(orig_set);
  ASSERT_TRUE(compare_sets(my_copy, orig_copy));
}

TEST(set, move_constructor_test_1) {
  s21::Set<double> my_set{0.66, 5.78, -3.45, 12.35};
  std::set<double> orig_set{0.66, 5.78, -3.45, 12.35};
  s21::Set<double> my_move(std::move(my_set));
  std::set<double> orig_move(std::move(orig_set));
  ASSERT_TRUE(compare_sets(my_move, orig_move));
}

TEST(set, move_constructor_test_2) {
  s21::Set<int> my_set{45, 12, 34, 15, 65};
  std::set<int> orig_set{45, 12, 34, 15, 65};
  s21::Set<int> my_move{10, -2, 8, 15, 0};
  std::set<int> orig_move{10, -2, 8, 15, 0};
  my_move = std::move(my_set);
  orig_move = std::move(orig_set);
  ASSERT_TRUE(compare_sets(my_move, orig_move));
}

TEST(set, swap_constructor_test_1) {
  s21::Set<int> my_set{10, -2, 8, 15, 0};
  std::set<int> orig_set{10, -2, 8, 15, 0};
  s21::Set<int> my_swap{6, 0, -3, 11, 8};
  std::set<int> orig_swap{6, 0, -3, 11, 8};
  my_swap.Swap(my_set);
  orig_swap.swap(orig_set);
  ASSERT_TRUE(compare_sets(my_swap, orig_swap));
}

TEST(set, swap_constructor_test_2) {
  s21::Set<double> my_set{0.1, -1.1, 0.7, 0.9, 2.1};
  std::set<double> orig_set{0.1, -1.1, 0.7, 0.9, 2.1};
  s21::Set<double> my_swap;
  std::set<double> orig_swap;
  ASSERT_TRUE(my_swap.Empty());
  my_swap.Swap(my_set);
  orig_swap.swap(orig_set);
  ASSERT_FALSE(my_swap.Empty());
  ASSERT_TRUE(compare_sets(my_swap, orig_swap));
}

TEST(set, clear_test) {
  s21::Set<char> my_set{'s', 'a', 't', 'p', 'f'};
  std::set<char> orig_set{'s', 'a', 't', 'p', 'f'};
  my_set.Clear();
  orig_set.clear();
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_EQ(my_set.Empty(), orig_set.empty());
  ASSERT_TRUE(my_set.Empty());
}

TEST(set, insert_test_1) {
  s21::Set<int> my_set{345, 234, 768, 213};
  std::set<int> orig_set{345, 234, 768, 213};
  my_set.Insert(342);
  orig_set.insert(342);
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, insert_test_2) {
  s21::Set<int> my_set;
  std::set<int> orig_set;
  my_set.Insert(21);
  orig_set.insert(21);
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, insert_test_3) {
  s21::Set<double> my_set{0.1, -1.1, 0.7, 0.9, 2.1};
  std::set<double> orig_set{0.1, -1.1, 0.7, 0.9, 2.1};
  my_set.Insert(0.0000007);
  my_set.Insert(0.0000007);
  my_set.Insert(-1.154675);
  orig_set.insert(0.0000007);
  orig_set.insert(0.0000007);
  orig_set.insert(-1.154675);
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, erase_test_1) {
  s21::Set<int> my_set{1, 5, 4, 8, -3, 6};
  std::set<int> orig_set{1, 5, 4, 8, -3, 6};
  my_set.Erase(my_set.Begin());
  orig_set.erase(orig_set.begin());
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, erase_test_2) {
  s21::Set<char> my_set{'s', 'a', 't', 'p', 'f'};
  std::set<char> orig_set{'s', 'a', 't', 'p', 'f'};
  my_set.Erase(++my_set.Begin());
  orig_set.erase(++orig_set.begin());
  ASSERT_EQ(my_set.Size(), orig_set.size());
  auto it = my_set.Begin();
  auto orig = orig_set.begin();
  for (; orig != orig_set.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(set, erase_test_3) {
  s21::Set<int> my_set{12, 5, 9};
  std::set<int> orig_set{12, 5, 9};
  auto it = ++my_set.Begin();
  my_set.Erase(++it);
  orig_set.erase(--orig_set.end());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, erase_test_4) {
  s21::Set<int> my_set{5, 1, 12, 4, -1};
  std::set<int> orig_set{5, 1, 12, 4, -1};
  my_set.Erase(++my_set.Begin());
  orig_set.erase(++orig_set.begin());
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, erase_test_5) {
  s21::Set<int> my_set{5};
  std::set<int> orig_set{5};
  my_set.Erase(my_set.Begin());
  orig_set.erase(orig_set.begin());
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_EQ(my_set.Empty(), orig_set.empty());
  ASSERT_TRUE(my_set.Empty());
}

TEST(set, merge_test_1) {
  s21::Set<int> my_set{1, 5, 4};
  s21::Set<int> my_add{8, -3, 6};
  // std::set<int> orig_set{1, 5, 4, 8, -3, 6};
  std::set<int> orig_set{1, 5, 4};
  std::set<int> orig_add{8, -3, 6};
  my_set.Merge(my_add);
  orig_set.merge(orig_add);
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, merge_test_2) {
  s21::Set<std::string> my_set{"Weekly", "Blacksad", "Smirnov"};
  s21::Set<std::string> my_add;
  std::set<std::string> orig_set{"Weekly", "Blacksad", "Smirnov"};
  std::set<std::string> orig_add;
  my_set.Merge(my_add);
  orig_set.merge(orig_add);
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, merge_test_3) {
  s21::Set<int> my_set{1, 8, 12, 6, 23, 5, -3};
  s21::Set<int> my_add{1, 8, 12, 6, 23, 5, -3};
  std::set<int> orig_set{1, 8, 12, 6, 23, 5, -3};
  std::set<int> orig_add{1, 8, 12, 6, 23, 5, -3};
  my_set.Merge(my_add);
  orig_set.merge(orig_add);
  ASSERT_EQ(my_set.Size(), orig_set.size());
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, find_test_1) {
  s21::Set<double> my_set{0.1, -1.1, 0.7, 0.9, 2.1};
  std::set<double> orig_set{0.1, -1.1, 0.7, 0.9, 2.1};
  auto it = my_set.Find(0.7);
  auto orig = orig_set.find(0.7);
  ASSERT_EQ(*it, *orig);
}

TEST(set, find_test_2) {
  s21::Set<int> my_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  std::set<int> orig_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  s21::Set<int>::Iterator it = my_set.Find(15);
  std::set<int>::iterator orig = orig_set.find(15);
  ASSERT_EQ(*it, *orig);
}

TEST(set, contains_test_1) {
  s21::Set<int> my_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  ASSERT_TRUE(my_set.Contains(12));
}

TEST(set, contains_test_2) {
  s21::Set<int> my_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  ASSERT_FALSE(my_set.Contains(21));
}

TEST(set, iterator_test_1) {
  s21::Set<int> my_set{5, 10, 15};
  std::set<int> orig_set{5, 10, 15};
  auto it = my_set.Begin();
  auto orig = orig_set.begin();
  ++it;
  ++orig;
  ++it;
  ++orig;
  --it;
  --orig;
  ASSERT_EQ(*it, *orig);
}

TEST(set, emplace_test_1) {
  s21::Set<int> my_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  std::set<int> orig_set{1, 11, 8, 12, 6, 23, 15, -8, 26};
  my_set.Emplace(4);
  orig_set.emplace(4);
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

TEST(set, emplace_test_2) {
  s21::Set<std::string> my_set{"Weekly", "Blacksad"};
  std::set<std::string> orig_set{"Weekly", "Blacksad"};
  my_set.Emplace("Smirnov");
  orig_set.emplace("Smirnov");
  ASSERT_TRUE(compare_sets(my_set, orig_set));
}

// STACK------------------------------------------------------------------------

TEST(stack, default_constructor_test) {
  s21::Stack<int> my_stack;
  std::stack<int> orig_stack;
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  ASSERT_EQ(my_stack.Empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.Empty());
}

TEST(stack, initializer_list_constructor_test) {
  s21::Stack<int> my_stack{3, 1};
  std::vector<int> tmp{3, 1};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, copy_constructor_test_1) {
  s21::Stack<double> my_stack;
  std::stack<double> orig_stack;
  s21::Stack<double> my_copy(my_stack);
  std::stack<double> orig_copy(orig_stack);
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
  ASSERT_TRUE(my_copy.Empty());
}

TEST(stack, copy_constructor_test_2) {
  s21::Stack<int> my_stack{1, 3, 5};
  std::vector<int> tmp{1, 3, 5};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  s21::Stack<int> my_copy(my_stack);
  std::stack<int, std::vector<int>> orig_copy(orig_stack);
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  while (!orig_copy.empty()) {
    ASSERT_EQ(my_copy.Top(), orig_copy.top());
    my_copy.Pop();
    orig_copy.pop();
  }
}

TEST(stack, move_constructor_test_1) {
  s21::Stack<int> my_stack;
  std::stack<int> orig_stack;
  s21::Stack<int> my_move(std::move(my_stack));
  std::stack<int> orig_move(std::move(orig_stack));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_EQ(my_move.Empty(), orig_move.empty());
  ASSERT_TRUE(my_move.Empty());
}

TEST(stack, move_constructor_test_2) {
  s21::Stack<char> my_stack{'a', 'b', 'c', 'd'};
  std::vector<char> tmp{'a', 'b', 'c', 'd'};
  std::stack<char, std::vector<char>> orig_stack(tmp);
  s21::Stack<char> my_move(std::move(my_stack));
  std::stack<char, std::vector<char>> orig_move(std::move(orig_stack));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  ASSERT_EQ(my_move.Empty(), orig_move.empty());
  ASSERT_FALSE(my_move.Empty());
  while (!orig_move.empty()) {
    ASSERT_EQ(my_move.Top(), orig_move.top());
    my_move.Pop();
    orig_move.pop();
  }
}

TEST(stack, move_operator_test) {
  s21::Stack<double> my_stack{0.456, 1.567, -4.678, 0.789};
  std::vector<double> tmp{0.456, 1.567, -4.678, 0.789};
  std::stack<double, std::vector<double>> orig_stack(tmp);
  s21::Stack<double> my_move{3.001, 5.456};
  std::vector<double> tmp_move{3.001, 5.456};
  std::stack<double, std::vector<double>> orig_move(tmp_move);
  my_move = std::move(my_stack);
  orig_move = std::move(orig_stack);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  while (!orig_move.empty()) {
    ASSERT_EQ(my_move.Top(), orig_move.top());
    my_move.Pop();
    orig_move.pop();
  }
}

TEST(stack, push_test_1) {
  s21::Stack<int> my_stack{3, 4, 9};
  std::vector<int> tmp{3, 4, 9};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  my_stack.Push(9);
  my_stack.Push(15);
  my_stack.Push(34);
  orig_stack.push(9);
  orig_stack.push(15);
  orig_stack.push(34);
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, push_test_2) {
  s21::Stack<std::string> my_stack;
  my_stack.Push("mullsher");
  my_stack.Push("staunton");
  std::stack<std::string> orig_stack;
  orig_stack.push("mullsher");
  orig_stack.push("staunton");
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, empty_test) {
  s21::Stack<char> my_stack{'a', 'b', 'c', 'd'};
  std::vector<char> tmp{'a', 'b', 'c', 'd'};
  std::stack<char, std::vector<char>> orig_stack(tmp);
  my_stack.Push('e');
  orig_stack.push('e');
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
  ASSERT_EQ(my_stack.Empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.Empty());
}

TEST(stack, swap_test_1) {
  s21::Stack<double> my_stack{3.0001, 4.767090, -0.56753, -5.6786};
  s21::Stack<double> my_swap;
  my_stack.Swap(my_swap);
  std::vector<double> tmp{3.0001, 4.767090, -0.56753, -5.6786};
  std::stack<double, std::vector<double>> orig_stack(tmp);
  std::stack<double, std::vector<double>> orig_swap;
  orig_stack.swap(orig_swap);
  ASSERT_EQ(my_stack.Empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.Empty());
  while (!orig_swap.empty()) {
    ASSERT_EQ(my_swap.Top(), orig_swap.top());
    my_swap.Pop();
    orig_swap.pop();
  }
}

TEST(stack, swap_test_2) {
  s21::Stack<int> my_stack{4, 67, -34, 2, 91, 3, 8};
  s21::Stack<int> my_swap{3, 0, 1, 7, 9};
  my_stack.Swap(my_swap);
  std::vector<int> tmp{4, 67, -34, 2, 91, 3, 8};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  std::vector<int> tmp_swap{3, 0, 1, 7, 9};
  std::stack<int, std::vector<int>> orig_swap(tmp_swap);
  orig_stack.swap(orig_swap);
  while (!orig_swap.empty()) {
    ASSERT_EQ(my_swap.Top(), orig_swap.top());
    my_swap.Pop();
    orig_swap.pop();
  }
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, emplace_test_1) {
  s21::Stack<char> my_stack{'a', 'b', 'c', 'd'};
  std::vector<char> tmp{'a', 'b', 'c', 'd'};
  std::stack<char, std::vector<char>> orig_stack(tmp);
  my_stack.EmplaceFront('o');
  orig_stack.emplace('o');
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, emplace_test_2) {
  s21::Stack<int> my_stack;
  std::stack<int> orig_stack;
  ASSERT_EQ(my_stack.Empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.Empty());
  my_stack.EmplaceFront(21);
  orig_stack.emplace(21);
  my_stack.EmplaceFront(3);
  orig_stack.emplace(3);
  ASSERT_EQ(my_stack.Size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.Top(), orig_stack.top());
    my_stack.Pop();
    orig_stack.pop();
  }
}

// VECTOR-----------------------------------------------------------------------

TEST(vector, default_constructor_test) {
  s21::Vector<int> my_vector;
  std::vector<int> orig_vector;
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  ASSERT_EQ(my_vector.Data(), orig_vector.data());
}

TEST(vector, parameterized_constructor_test) {
  s21::Vector<int> my_vector(11);
  std::vector<int> orig_vector(11);
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
}

TEST(vector, initializer_list_constructor_test) {
  s21::Vector<int> my_vector{1, 4, 12, 45, -88, 2, 67};
  std::vector<int> orig_vector{1, 4, 12, 45, -88, 2, 67};
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector.At(i), orig_vector.at(i));
  }
}

TEST(vector, copy_constructor_test_1) {
  s21::Vector<int> my_vector;
  std::vector<int> orig_vector;
  s21::Vector<int> my_copy(my_vector);
  std::vector<int> orig_copy(orig_vector);
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  ASSERT_EQ(my_copy.Capacity(), orig_copy.capacity());
}

TEST(vector, copy_constructor_test_2) {
  s21::Vector<double> my_vector{0.33, -1.4567, 66.1, 0.005, 33.3};
  std::vector<double> orig_vector{0.33, -1.4567, 66.1, 0.005, 33.3};
  s21::Vector<double> my_copy(my_vector);
  std::vector<double> orig_copy(orig_vector);
  ASSERT_EQ(my_copy.Empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.Size(), orig_copy.size());
  ASSERT_EQ(my_copy.Capacity(), orig_copy.capacity());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_copy.At(i), orig_copy.at(i));
  }
}

TEST(vector, move_constructor_test_1) {
  s21::Vector<int> my_vector{1, 4, 12, 45, -88, 2, 67};
  std::vector<int> orig_vector{1, 4, 12, 45, -88, 2, 67};
  s21::Vector<int> my_move(std::move(my_vector));
  std::vector<int> orig_move(std::move(orig_vector));
  ASSERT_EQ(my_move.Size(), orig_move.size());
  for (size_t i = 0; i < orig_move.size(); ++i) {
    ASSERT_EQ(my_move.At(i), orig_move.at(i));
  }
}

TEST(vector, move_constructor_test_2) {
  s21::Vector<char> my_vector{'v', 't', '=', 'g'};
  std::vector<char> orig_vector{'v', 't', '=', 'g'};
  s21::Vector<char> my_move{'1', '9'};
  std::vector<char> orig_move{'1', '9'};
  my_move = std::move(my_vector);
  orig_move = std::move(orig_vector);
  ASSERT_EQ(my_move.Size(), orig_move.size());
  for (size_t i = 0; i < orig_move.size(); ++i) {
    ASSERT_EQ(my_move.At(i), orig_move.at(i));
  }
}

TEST(vector, swap_test_1) {
  s21::Vector<double> my_vector;
  std::vector<double> orig_vector;
  s21::Vector<double> my_swap;
  std::vector<double> orig_swap;
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  my_swap.Swap(my_vector);
  orig_swap.swap(orig_vector);
  ASSERT_EQ(my_swap.Empty(), orig_swap.empty());
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  ASSERT_EQ(my_swap.Capacity(), orig_swap.capacity());
}

TEST(vector, swap_test_2) {
  s21::Vector<int> my_vector{1, 0, 9, -3, 21};
  std::vector<int> orig_vector{1, 0, 9, -3, 21};
  s21::Vector<int> my_swap;
  std::vector<int> orig_swap;
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  my_swap.Swap(my_vector);
  orig_swap.swap(orig_vector);
  ASSERT_EQ(my_swap.Empty(), orig_swap.empty());
  ASSERT_EQ(my_swap.Size(), orig_swap.size());
  ASSERT_EQ(my_swap.Capacity(), orig_swap.capacity());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_swap.At(i), orig_swap.at(i));
  }
}

TEST(vector, at_test) {
  s21::Vector<float> my_vector{0.675, 9.764, 1.34566, 5.69879};
  std::vector<float> orig_vector{0.675, 9.764, 1.34566, 5.69879};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector.At(i), orig_vector.at(i));
  }
}

TEST(vector, operator_square_brackets_test) {
  s21::Vector<int> my_vector{21, 34, 2321, -81, 111};
  std::vector<int> orig_vector{21, 34, 2321, -81, 111};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, data_test) {
  s21::Vector<int> my_vector{1, 3, 88, 0, -1};
  std::vector<int> orig_vector{1, 3, 88, 0, -1};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  int* my_data = my_vector.Data();
  int* orig_data = orig_vector.data();
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_data[i], orig_data[i]);
  }
}

TEST(vector, front_test) {
  s21::Vector<int> my_vector{21, 15, 1};
  std::vector<int> orig_vector{21, 15, 1};
  ASSERT_EQ(my_vector.Front(), orig_vector.front());
}

TEST(vector, back_test_1) {
  s21::Vector<std::string> my_vector{"Blacksad", "Weekly"};
  std::vector<std::string> orig_vector{"Blacksad", "Weekly"};
  ASSERT_EQ(my_vector.Back(), orig_vector.back());
}

TEST(vector, back_test_2) {
  s21::Vector<double> my_vector{0.33, -1.4567, 66.1, 0.005, 33.3};
  std::vector<double> orig_vector{0.33, -1.4567, 66.1, 0.005, 33.3};
  my_vector.PopBack();
  orig_vector.pop_back();
  ASSERT_EQ(my_vector.Back(), orig_vector.back());
}

TEST(vector, push_back_test_1) {
  s21::Vector<float> my_vector{0.3, 1.99};
  std::vector<float> orig_vector{0.3, 1.99};
  my_vector.PushBack(4.5);
  orig_vector.push_back(4.5);
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.At(2), orig_vector.at(2));
  ASSERT_EQ(my_vector.Back(), orig_vector.back());
}

TEST(vector, push_back_test_2) {
  s21::Vector<std::string> my_vector{"Blacksad", "Weekly"};
  std::vector<std::string> orig_vector{"Blacksad", "Weekly"};
  my_vector.PushBack("Smirnov");
  my_vector.PushBack("Fiston");
  orig_vector.push_back("Smirnov");
  orig_vector.push_back("Fiston");
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector.At(i), orig_vector.at(i));
  }
}

TEST(vector, pop_back_test) {
  s21::Vector<int> my_vector{0, 1, 4, 77, 5, 33};
  std::vector<int> orig_vector{0, 1, 4, 77, 5, 33};
  my_vector.PopBack();
  orig_vector.pop_back();
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Back(), orig_vector.back());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, insert_test_1) {
  s21::Vector<int> my_vector{30, 112, -34, 61};
  std::vector<int> orig_vector{30, 112, -34, 61};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  my_vector.Insert(my_vector.Begin() + my_vector.Size(), 77);
  orig_vector.insert(orig_vector.begin() + orig_vector.size(), 77);
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, insert_test_2) {
  s21::Vector<double> my_vector{0.9, 11.2, 33.4};
  std::vector<double> orig_vector{0.9, 11.2, 33.4};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  my_vector.Insert(my_vector.Begin(), -77.09);
  orig_vector.insert(orig_vector.begin(), -77.09);
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, erase_test) {
  s21::Vector<int> my_vector{1, 3, 9, 81, 6561};
  std::vector<int> orig_vector{1, 3, 9, 81, 6561};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  my_vector.Erase(my_vector.Begin() + 1);
  orig_vector.erase(orig_vector.begin() + 1);
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, clear_test) {
  s21::Vector<int> my_vector{1, 3, 2, 4};
  std::vector<int> orig_vector{1, 3, 2, 4};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  my_vector.Clear();
  orig_vector.clear();
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Empty(), orig_vector.empty());
}

TEST(vector, reserve_capacity_test_1) {
  s21::Vector<int> my_vector;
  std::vector<int> orig_vector;
  my_vector.Reserve(12);
  orig_vector.reserve(12);
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
}

TEST(vector, reserve_capacity_test_2) {
  s21::Vector<float> my_vector{0.3, 1.99, -2.76, 3.0};
  std::vector<float> orig_vector{0.3, 1.99, -2.76, 3.0};
  my_vector.Reserve(8);
  orig_vector.reserve(8);
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
}

TEST(vector, shrink_to_fit_capacity_test) {
  s21::Vector<char> my_vector{'s', 'c', 'h', 'o', 'o', 'l'};
  std::vector<char> orig_vector{'s', 'c', 'h', 'o', 'o', 'l'};
  my_vector.Reserve(12);
  orig_vector.reserve(12);
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  my_vector.ShrinkToFit();
  orig_vector.shrink_to_fit();
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
}

TEST(vector, emplace_test_1) {
  s21::Vector<int> my_vector;
  std::vector<int> orig_vector;
  my_vector.Emplace(my_vector.Cend(), 21);
  orig_vector.emplace(orig_vector.cend(), 21);
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector[0], orig_vector[0]);
}

TEST(vector, emplace_test_2) {
  s21::Vector<int> my_vector{1, 67, -345, 11, 58};
  std::vector<int> orig_vector{1, 67, -345, 11, 58};
  my_vector.Emplace(my_vector.Cbegin() + 3, 21);
  orig_vector.emplace(orig_vector.cbegin() + 3, 21);
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector[0], orig_vector[0]);
}

TEST(vector, emplace_test_3) {
  s21::Vector<double> my_vector{0.45676, 8.9075, 5.345, 7.9096, 6.001};
  std::vector<double> orig_vector{0.45676, 8.9075, 5.345, 7.9096, 6.001};
  my_vector.Emplace(++my_vector.Cbegin(), 0.009);
  orig_vector.emplace(++orig_vector.cbegin(), 0.009);
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector[0], orig_vector[0]);
}

TEST(vector, emplace_back_test_1) {
  s21::Vector<int> my_vector{1, 3, 2, 4};
  std::vector<int> orig_vector{1, 3, 2, 4};
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  my_vector.EmplaceBack(5);
  orig_vector.emplace_back(5);
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector[i], orig_vector[i]);
  }
}

TEST(vector, emplace_back_test_2) {
  s21::Vector<std::string> my_vector{"Blacksad", "Weekly"};
  std::vector<std::string> orig_vector{"Blacksad", "Weekly"};
  my_vector.EmplaceBack("Smirnov");
  my_vector.EmplaceBack("Fiston");
  orig_vector.emplace_back("Smirnov");
  orig_vector.emplace_back("Fiston");
  ASSERT_EQ(my_vector.Size(), orig_vector.size());
  ASSERT_EQ(my_vector.Capacity(), orig_vector.capacity());
  for (size_t i = 0; i < orig_vector.size(); ++i) {
    ASSERT_EQ(my_vector.At(i), orig_vector.at(i));
  }
}

TEST(vector, const_iterator_operator_test_1) {
  s21::Vector<int> my_vector{1, 3, 2, 4};
  std::vector<int> orig_vector{1, 3, 2, 4};
  s21::Vector<int>::ConstIterator it_my = my_vector.Cbegin() + 2;
  std::vector<int>::const_iterator it_orig = orig_vector.cbegin() + 2;
  --it_my;
  --it_orig;
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(vector, const_iterator_operator_test_2) {
  s21::Vector<double> my_vector{0.56, -3.44, 8.88, 0.23};
  std::vector<double> orig_vector{0.56, -3.44, 8.88, 0.23};
  s21::Vector<double>::ConstIterator it1 = my_vector.Cbegin();
  std::vector<double>::const_iterator it2 = orig_vector.cbegin();
  ASSERT_TRUE(*it1 == *it2);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}