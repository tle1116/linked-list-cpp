#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;


//CORE
TEST(LinkedListCore, push_front) {
  LinkedList<int> list;

  list.push_front(1);
  list.push_front(2);

  ASSERT_THAT(list.size(), Eq(2));

  EXPECT_THAT(list.at(0), Eq(2));
  EXPECT_THAT(list.at(1), Eq(1));
}

TEST(LinkedListCore, push_back) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  ASSERT_THAT(list.size(), Eq(2));

  EXPECT_THAT(list.at(0), Eq(1));
  EXPECT_THAT(list.at(1), Eq(2));
}

TEST(LinkedListCore, pop_front) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  int value = list.pop_front();

  ASSERT_THAT(value, Eq(1));
  
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.at(0), Eq(2));
}

TEST(LinkedListCore, pop_back) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  int value = list.pop_back();

  ASSERT_THAT(value, Eq(2));
  
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.at(0), Eq(1));
}

TEST(LinkedListCore, pop_back_empty) {
  LinkedList<int> list;

  EXPECT_THROW(list.pop_back(), runtime_error);
}

TEST(LinkedListCore, pop_back_single) {
  LinkedList<int> list;

  list.push_back(10);

  int value = list.pop_back();

  ASSERT_THAT(value, Eq(10));
  
  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(list.empty(), Eq(true));
}

TEST(LinkedListCore, empty) {
  LinkedList<int> list;

  EXPECT_THAT(list.empty(), Eq(true));

  list.push_back(1);

  EXPECT_THAT(list.empty(), Eq(false));
}

TEST(LinkedListCore, clear) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  list.clear();

  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(list.empty(), Eq(true));
}

TEST(LinkedListCore, invalidIndex) {
  LinkedList<int> list;

  list.push_back(1);

  EXPECT_THROW(list.at(5), out_of_range);
}

TEST(LinkedListCore, emptyList) {
  LinkedList<int> list;

  EXPECT_THROW(list.pop_front(), runtime_error);
}

// AUGMENTED
TEST(LinkedListAugmented, copyConstructor) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);
  
  LinkedList<int> copy(list);

  EXPECT_THAT(copy.size(), 2);
  EXPECT_THAT(copy.at(0), 1);
  EXPECT_THAT(copy.at(1), 2);
}

TEST(LinkedListAugmented, copyConstructorEmpty) {
  LinkedList<int> list;
  
  LinkedList<int> copy(list);

  EXPECT_THAT(copy.size(), 0);
}

TEST(LinkedListAugmented, assignmentOperater) {
  LinkedList<int> list1;

  list1.push_back(1);
  list1.push_back(2);

  LinkedList<int> list2;
  
  list2 = list1;

  EXPECT_THAT(list2.size(), 2);
  EXPECT_THAT(list2.at(0), 1);
  EXPECT_THAT(list2.at(1), 2);
}

TEST(LinkedListAugmented, assignmentOperaterEmpty) {
  LinkedList<int> list1;
  LinkedList<int> list2;

  list2 = list1;

  EXPECT_THAT(list2.size(), 0);
}

TEST(LinkedListAugmented, assignmentOperaterSelf ) {
  LinkedList<int> list;
  
  list.push_back(1);
  list.push_back(2);

  LinkedList<int>& ref = list;
  list = ref;

  EXPECT_THAT(list.size(), 2);
  EXPECT_THAT(list.at(0), 1);
  EXPECT_THAT(list.at(1), 2);
}

TEST(LinkedListAugmented, to_string) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  EXPECT_THAT(list.to_string(), "[1, 2]");
}

TEST(LinkedListAugmented, Find) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  EXPECT_THAT(list.find(2), 1);
}

TEST(LinkedListAugmented, findNotFound) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  EXPECT_THAT(list.find(3), -1);
}

TEST(LinkedListAugmented, removeLast) {
  LinkedList<int> list;

  list.push_back(1);
  list.push_back(2);

  list.remove_last(2);

  EXPECT_THAT(list.size(), 1);
  EXPECT_THAT(list.at(0), 1);
}

