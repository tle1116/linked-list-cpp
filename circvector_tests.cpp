#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

//CORE
TEST(CircVectorCore, defaultConstructor) {
  CircVector<int> vec;

  EXPECT_THAT(vec.size(), 0);
  EXPECT_THAT(vec.get_capacity(), 10);
}

TEST(CircVectorCore, push_front) {
  CircVector<int> vec;

  for(int i = 0; i < 50; i++) {
    vec.push_front(i);
  }
  EXPECT_THAT(vec.size(), 50);
  EXPECT_THAT(vec.at(0), 49);
  EXPECT_THAT(vec.at(49), 0);
  
}

TEST(CircVectorCore, push_back) {
  CircVector<int> vec;

  for(int i =0; i < 50; i++) {
    vec.push_back(i);
  }

  EXPECT_THAT(vec.size(), 50);
  EXPECT_THAT(vec.at(0), 0);
  EXPECT_THAT(vec.at(49), 49);
}

TEST(CircVectorCore, push_back_no_wrap) {
  CircVector<int> vec;

  for(int i =0; i < 10; i++) {
    vec.push_back(i);
  }
  vec.pop_front();
  vec.pop_front();

  vec.push_back(500);

  EXPECT_THAT(vec.at(vec.size() - 1), 500);
}

TEST(CircVectorCore, pop_front) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  int value = vec.pop_front();

  EXPECT_THAT(value, 1);
  EXPECT_THAT(vec.size(), 1);
  EXPECT_THAT(vec.at(0), 2);
}

TEST(CircVectorCore, pop_front_throw) {
  CircVector<int> vec;

  EXPECT_THROW(vec.pop_front(), runtime_error);
}

TEST(CircVectorCore, pop_back) {
  CircVector<int> vec;

  EXPECT_THROW(vec.pop_back(), runtime_error);

  vec.push_back(1);
  vec.push_back(2);

  int value = vec.pop_back();

  EXPECT_THAT(value, 2);
  EXPECT_THAT(vec.size(), 1);
}

TEST(CircVectorCore, pop_back_wrap) {
  CircVector<int> vec;

  for(int i = 0; i < 20; i++) {
    vec.push_back(i);
  }
  for(int i = 0; i < 10; i++) {
    vec.pop_front();
  }
  vec.push_back(50);
  
  int value = vec.pop_back();
  
  EXPECT_THAT(value, 50);
}

TEST(CircVectorCore, clear) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  vec.clear();

  EXPECT_THAT(vec.size(), 0);
}

TEST(CircVectorCore, invalidIndex) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  EXPECT_THROW(vec.at(2), out_of_range);
}

TEST(CircVectorCore, empty) {
  CircVector<int> vec;

  EXPECT_THAT(vec.empty(), true);

  vec.push_back(5);

  EXPECT_THAT(vec.empty(), false);
}

//AUGMENTED
TEST(CircVectorAugmented, copyConstructor) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  CircVector<int> copy(vec);

  EXPECT_THAT(copy.size(), 2);
  EXPECT_THAT(copy.at(0), 1);
  EXPECT_THAT(copy.at(1), 2);
}

TEST(CircVectorAugmented, copyConstructorEmpty) {
  CircVector<int> vec;

  CircVector<int> copy(vec);

  EXPECT_THAT(copy.size(), 0);
}

TEST(CircVectorAugmented, assignmentOperator) {
  CircVector<int> vec1;

  vec1.push_back(1);
  vec1.push_back(2);

  CircVector<int> vec2;

  vec2 = vec1;

  EXPECT_THAT(vec2.size(), 2);
  EXPECT_THAT(vec2.at(0), 1);
  EXPECT_THAT(vec2.at(1), 2);
}

TEST(CircVectorAugmented, assignmentOperaterEmpty) {
  CircVector<int> list1;
  CircVector<int> list2;

  list2 = list1;

  EXPECT_THAT(list2.size(), 0);
}

TEST(CircVectorAugmented, assignmentOperaterSelf ) {
  CircVector<int> vec;
  
  vec.push_back(1);
  vec.push_back(2);

  CircVector<int>& ref = vec;
  vec = ref;

  EXPECT_THAT(vec.size(), 2);
  EXPECT_THAT(vec.at(0), 1);
  EXPECT_THAT(vec.at(1), 2);
}

TEST(CircVectorAugmented, to_string) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  EXPECT_THAT(vec.to_string(), "[1, 2]");
}

TEST(CircVectorAugmented, Find) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  CircVector<int> copy(vec);

  EXPECT_THAT(copy.find(2), 1);
}

TEST(CircVectorAugmented, findNotFound) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  EXPECT_THAT(vec.find(3), -1);
}

TEST(CircVectorAugmented, removeLast) {
  CircVector<int> vec;

  vec.push_back(1);
  vec.push_back(2);

  vec.remove_last(2);

  EXPECT_THAT(vec.size(), 1);
  EXPECT_THAT(vec.at(0), 1);
}