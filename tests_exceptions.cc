#include <gtest/gtest.h>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(array, exception_test_1) {
  s21::Array<int, 5> my_array{1, 21, 67, 2, 4};
  ASSERT_THROW(my_array.At(5), std::out_of_range);
}

TEST(array, exception_test_2) {
  try {
    s21::Array<int, 5> my_array{1, 21, 67, 2, 4, 7, 8};
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Invalid amount of items");
  }
}

TEST(list, exception_test_1) {
  s21::List<int> my_list;
  ASSERT_THROW(my_list.Front(), std::out_of_range);
}

TEST(list, exception_test_2) {
  s21::List<int> my_list;
  ASSERT_THROW(my_list.Back(), std::out_of_range);
}

TEST(list, exception_test_3) {
  s21::List<int> my_list;
  ASSERT_THROW(my_list.Erase(my_list.Begin()), std::out_of_range);
}

TEST(map, exception_test_1) {
  s21::Map<int, char> my_map{{5, 'a'}, {6, 'b'}, {3, 'c'}};
  ASSERT_THROW(my_map.At(1), std::out_of_range);
}

TEST(queue, exception_test_1) {
  s21::Queue<int> my_queue;
  ASSERT_THROW(my_queue.Front(), std::out_of_range);
}

TEST(queue, exception_test_2) {
  s21::Queue<int> my_queue;
  ASSERT_THROW(my_queue.Back(), std::out_of_range);
}

TEST(vector, exception_test_1) {
  s21::Vector<int> my_vector{1, 3, 5, 7, 9};
  ASSERT_THROW(my_vector.At(8), std::out_of_range);
}

TEST(vector, exception_test_2) {
  s21::Vector<char> my_vector{'s', 'c', 'h', 'o', 'o', 'l'};
  ASSERT_THROW(my_vector.Insert(my_vector.End() + 2, 'r'), std::out_of_range);
}

TEST(vector, exception_test_3) {
  s21::Vector<char> my_vector{'s', 'c', 'h', 'o', 'o', 'l'};
  ASSERT_THROW(my_vector.Erase(my_vector.End() + 2), std::out_of_range);
}

TEST(vector, exception_test_4) {
  s21::Vector<int> my_vector{1, 67, -345, 11, 58};
  ASSERT_THROW(my_vector.Emplace(++my_vector.Cend()), std::out_of_range);
}