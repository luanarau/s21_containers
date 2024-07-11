#include "test_entry.h"

TEST(list, ConstructorDefault) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, ConstructorParameterized) {
  s21::list<int> s21_list(1);
  std::list<int> std_list(1);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, ConstructorInitializerList) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, ConstructorCopy) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};

  const s21::list<char> &s21_list_2 = s21_list_1;
  const std::list<char> &std_list_2 = std_list_1;

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
  EXPECT_EQ(std_list_1.size(), std_list_2.size());
}

TEST(list, ConstructorMove) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};

  s21::list<char> s21_list_2 = std::move(s21_list_1);
  std::list<char> std_list_2 = std::move(std_list_1);

  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
  EXPECT_EQ(s21_list_1.empty(), std_list_1.empty());
}

TEST(list, Clear) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.clear();
  std_list.clear();

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, Insert) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  s21_list_1.insert(s21_list_1.begin() + 1, 'b');

  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();

  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, Erase) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  s21_list_2.erase(s21_list_2.begin() + 1);

  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();

  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, Push) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, Pop) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, Swap) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd', 'e'};
  s21::list<char> s21_list_2 = {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  s21::list<char> s21_list_3 = {'a', 'b', 'c', 'd', 'e'};
  s21::list<char> s21_list_4 = {'q', 'w', 'e', 'r', 't', 'y', 'u'};

  s21_list_1.swap(s21_list_2);

  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  auto it3 = s21_list_3.begin();
  auto it4 = s21_list_4.begin();

  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }

  while (it2 != s21_list_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }

  EXPECT_EQ(s21_list_1.size(), s21_list_4.size());
  EXPECT_EQ(s21_list_2.size(), s21_list_3.size());
}

TEST(list, Merge) {
  s21::list<double> s21_list_1 = {0.1, 0.2, 0.3};
  s21::list<double> s21_list_2 = {-1, 0, 1, 2};
  std::list<double> std_list_1 = {0.1, 0.2, 0.3};
  std::list<double> std_list_2 = {-1, 0, 1, 2};

  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);

  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();

  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(list, Splice) {
  s21::list<int> s21_list_1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_2 = {10, 20, 30, 40, 50};
  std::list<int> std_list_1 = {1, 2, 3, 4, 5};
  std::list<int> std_list_2 = {10, 20, 30, 40, 50};

  auto it1 = s21_list_1.begin() + 2;
  auto it2 = std_list_1.begin();
  std::advance(it2, 2);

  s21_list_1.splice(it1, s21_list_2);
  std_list_1.splice(it2, std_list_2);

  auto it3 = s21_list_1.begin();
  auto it4 = std_list_1.begin();

  while (it3 != s21_list_1.end()) {
    EXPECT_EQ(*it3, *it4);
    ++it3, ++it4;
  }

  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
}

TEST(list, Reverse) {
  s21::list<int> s21_list_1 = {1, 2, 3, 4};
  s21::list<int> s21_list_2 = {4, 3, 2, 1};

  s21_list_1.reverse();

  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();

  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, Unique) {
  s21::list<int> s21_list{1, 2, 2, 3, 3, 2, 1, 1, 2};
  std::list<int> std_list{1, 2, 2, 3, 3, 2, 1, 1, 2};

  s21_list.unique();
  std_list.unique();

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, Sort) {
  s21::list<double> s21_list{1.1, 10, 2.4, 2.4, 5.111, -4, 30};
  std::list<double> std_list{1.1, 10, 2.4, 2.4, 5.111, -4, 30};

  s21_list.sort();
  std_list.sort();

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, InsertMany) {
  s21::list<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21::list<int>::listIterator it1(s21_list, 3);
  s21_list.insert_many(it1, 10, 20, 30);

  auto it2 = std_list.begin();
  std::advance(it2, 3);
  std_list.insert(it2, 10);
  std_list.insert(it2, 20);
  std_list.insert(it2, 30);

  auto it3 = s21_list.begin();
  auto it4 = std_list.begin();

  while (it3 != s21_list.end()) {
    EXPECT_EQ(*it3, *it4);
    ++it3, ++it4;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, InsertManyBack) {
  s21::list<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.insert_many_back(10, 20, 30);

  std_list.push_back(10);
  std_list.push_back(20);
  std_list.push_back(30);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, InsertManyFront) {
  s21::list<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.insert_many_front(10, 20, 30);

  std_list.push_front(30);
  std_list.push_front(20);
  std_list.push_front(10);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();

  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }