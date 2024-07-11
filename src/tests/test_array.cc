#include "test_entry.h"

TEST(array, ConstructorDefault) {
  s21::array<int, 5> s21_array{};
  std::array<int, 5> std_array{};

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array, ConstructorInitializerList) {
  s21::array<int, 10> s21_array = {1, 2, 3, 4, 5};
  std::array<int, 10> std_array = {1, 2, 3, 4, 5};

  auto it1 = s21_array.begin();
  auto it2 = std_array.begin();

  while (it1 != s21_array.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array, ConstructorCopy) {
  s21::array<char, 10> s21_array_1 = {'a', 'b', 'c', 'd'};
  std::array<char, 10> std_array_1 = {'a', 'b', 'c', 'd'};

  s21::array<char, 10> &s21_array_2 = s21_array_1;
  std::array<char, 10> &std_array_2 = std_array_1;

  EXPECT_EQ(s21_array_1.size(), s21_array_2.size());
  EXPECT_EQ(std_array_1.size(), std_array_2.size());
}

TEST(array, ConstructorMove) {
  s21::array<char, 10> s21_array_1 = {'a', 'b', 'c', 'd'};
  std::array<char, 10> std_array_1 = {'a', 'b', 'c', 'd'};

  s21::array<char, 10> s21_array_2 = std::move(s21_array_1);
  std::array<char, 10> std_array_2 = std::move(std_array_1);

  EXPECT_EQ(s21_array_1.size(), std_array_1.size());
  EXPECT_EQ(s21_array_2.size(), std_array_2.size());
  EXPECT_EQ(s21_array_2.empty(), std_array_2.empty());
}

TEST(array, OperatorMove) {
  s21::array<char, 10> s21_array_1 = {'a', 'b', 'c', 'd'};
  std::array<char, 10> std_array_1 = {'a', 'b', 'c', 'd'};

  s21::array<char, 10> s21_array_2{};
  std::array<char, 10> std_array_2{};

  s21_array_2 = std::move(s21_array_1);
  std_array_2 = std::move(std_array_2);

  EXPECT_EQ(s21_array_1.size(), std_array_1.size());
  EXPECT_EQ(s21_array_2.size(), std_array_2.size());
  EXPECT_EQ(s21_array_2.empty(), std_array_2.empty());
}

TEST(array, At) {
  s21::array<char, 10> s21_array_2 = {'a', 'b', 'c', 'd'};
  std::array<char, 10> std_array_2 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_array_2.at(3), std_array_2.at(3));
  EXPECT_EQ(s21_array_2.at(7), std_array_2.at(7));
}

TEST(array, Index) {
  s21::array<int, 10> s21_array = {1, 2, 3, 4, 5};
  std::array<int, 10> std_array = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_array[4], std_array[4]);
  EXPECT_EQ(s21_array[8], std_array[8]);
}

TEST(array, Front) {
  s21::array<double, 7> s21_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};
  std::array<double, 7> std_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};

  EXPECT_EQ(s21_array.front(), std_array.front());
}

TEST(array, Back) {
  s21::array<double, 7> s21_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};
  std::array<double, 7> std_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};

  EXPECT_EQ(s21_array.back(), std_array.back());
}

TEST(array, Iterators) {
  s21::array<double, 10> s21_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};
  std::array<double, 10> std_array = {1.1, 10, 2.4, 2.4, 5.111, -4, 30};

  EXPECT_TRUE(std::equal(s21_array.begin(), s21_array.end(), std_array.begin(),
                         std_array.end()));
}

TEST(array, Capacity) {
  s21::array<double, 10> s21_array_1{};
  std::array<double, 10> std_array_1{};

  EXPECT_EQ(s21_array_1.size(), std_array_1.size());
  EXPECT_EQ(s21_array_1.empty(), std_array_1.empty());
  EXPECT_EQ(s21_array_1.max_size(), std_array_1.max_size());

  s21::array<double, 10> s21_array_2 = {1};
  std::array<double, 10> std_array_2 = {1};

  EXPECT_EQ(s21_array_2.size(), std_array_2.size());
  EXPECT_EQ(s21_array_2.empty(), std_array_2.empty());
  EXPECT_EQ(s21_array_2.max_size(), std_array_2.max_size());
}

TEST(array, Swap) {
  s21::array<char, 10> s21_array_1 = {'a', 'b', 'c', 'd', 'e'};
  s21::array<char, 10> s21_array_2 = {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  s21::array<char, 10> s21_array_3 = {'a', 'b', 'c', 'd', 'e'};
  s21::array<char, 10> s21_array_4 = {'q', 'w', 'e', 'r', 't', 'y', 'u'};

  s21_array_1.swap(s21_array_2);

  auto it1 = s21_array_1.begin();
  auto it2 = s21_array_2.begin();
  auto it3 = s21_array_3.begin();
  auto it4 = s21_array_4.begin();

  while (it1 != s21_array_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }

  while (it2 != s21_array_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }

  EXPECT_EQ(s21_array_1.size(), s21_array_4.size());
  EXPECT_EQ(s21_array_2.size(), s21_array_3.size());
}

TEST(array, Fill) {
  s21::array<int, 3> s21_array = {10, 20, 30};
  std::array<int, 3> std_array = {10, 20, 30};

  s21_array.fill(21);
  std_array.fill(21);

  auto it1 = s21_array.begin();
  auto it2 = std_array.begin();

  while (it1 != s21_array.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_array.size(), std_array.size());
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }