#include "test_entry.h"

TEST(Vector, ConstructorDefaultVector) {
  s21::vector<int> s21_empty_vector;
  std::vector<int> std_empty_vector;

  EXPECT_EQ(s21_empty_vector.empty(), std_empty_vector.empty());
}

TEST(Vector, ConstructorWithParametrVector_Empty) {
  s21::vector<int> s21_vector(0);

  EXPECT_TRUE(s21_vector.empty());
}

TEST(Vector, ConstructorWithParametrVector) {
  s21::vector<int> s21_vector(10);
  std::vector<int> std_vector(10);

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_TRUE(s21_vector[i] == std_vector[i]);
  }
}

TEST(Vector, InitializerListConstructor_Empty) {
  s21::vector<int> v = {};

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(Vector, InitializerListConstructor) {
  s21::vector<std::string> v = {"HELLO,", "PEER.", "!HOW ARE YOU?"};

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.front(), "HELLO,");
  EXPECT_EQ(v.back(), "!HOW ARE YOU?");
}

TEST(Vector, CopyConstructor_Empty) {
  s21::vector<int> v;
  s21::vector<int> copy_v(v);

  EXPECT_TRUE(v.empty() == copy_v.empty());
  EXPECT_EQ(v.size(), copy_v.size());
  EXPECT_EQ(v.capacity(), copy_v.capacity());
}

TEST(Vector, CopyConstructor) {
  s21::vector<int> v = {123, 43, 567, 22222, 1111, 1234, 45};
  s21::vector<int> copy_v(v);

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), copy_v.size());
  EXPECT_EQ(v.capacity(), copy_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, MoveConstructor) {
  s21::vector<int> v = {123, 4, 567, 8910, 1112, 1314, 15};
  s21::vector<int> move_v(std::move(v));

  std::vector<int> std_v = {123, 4, 567, 8910, 1112, 1314, 15};
  std::vector<int> std_move_v(std::move(std_v));

  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(std_v.empty());

  EXPECT_EQ(move_v.front(), 123);
  EXPECT_EQ(move_v.back(), 15);
}

TEST(Vector, OperatorOfEqual_Copy_1) {
  s21::vector<int> v = {123, 4, 567, 8910, 1112, 1314, 15};
  s21::vector<int> copy_v = v;

  EXPECT_FALSE(v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, OperatorOfEqual_Copy_2) {
  s21::vector<int> v = {123, 4, 567, 8910, 1112, 1314, 15};
  s21::vector<int> copy_v = {123, 4, 567, 8910};

  copy_v = v;

  EXPECT_FALSE(v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, OperatorOfEqual_Copy_3) {
  s21::vector<int> v = {123, 4, 567, 8910};
  s21::vector<int> copy_v = {123, 4, 567, 8910, 1112, 1314, 15};

  copy_v = v;

  EXPECT_FALSE(v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, OperatorOfEqual_Copy_4) {
  s21::vector<std::string> v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};
  s21::vector<std::string> copy_v = {"Its", "normal", ".!"};

  copy_v = v;

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, OperatorOfEqual_Copy_5) {
  s21::vector<std::string> v = {"Its", "normal", ".!"};
  s21::vector<std::string> copy_v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};

  copy_v = v;

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], copy_v[i]);
  }
}

TEST(Vector, OperatorOfEqual_Move_1) {
  s21::vector<int> v = {123, 4, 567, 8910, 1112, 1314, 15};
  s21::vector<int> move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(move_v.front(), 123);
  EXPECT_EQ(move_v.back(), 15);
}

TEST(Vector, OperatorOfEqual_Move_2) {
  s21::vector<int> v = {123, 4, 567, 8910, 1112, 1314, 15};
  s21::vector<int> move_v = {123, 4, 567, 8910};

  move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(move_v.front(), 123);
  EXPECT_EQ(move_v.back(), 15);
}

TEST(Vector, OperatorOfEqual_Move_3) {
  s21::vector<int> v = {123, 4, 567, 8910};
  s21::vector<int> move_v = {123, 4, 567, 8910, 1112, 1314, 15};

  move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(move_v.front(), 123);
  EXPECT_EQ(move_v.back(), 8910);
}

TEST(Vector, OperatorOfEqual_Move_4) {
  s21::vector<int> v;
  s21::vector<int> move_v = {123, 4, 567, 8910, 1112, 1314, 15};

  move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(move_v.empty());
}

TEST(Vector, OperatorOfEqual_Move_5) {
  s21::vector<std::string> v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};
  s21::vector<std::string> move_v = {"Its", "normal", ".!"};

  move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(move_v.front(), "123, 4, 567, 8910");
  EXPECT_EQ(move_v.back(), "Pipebomb");
}

TEST(Vector, OperatorOfEqual_Move_6) {
  s21::vector<std::string> v = {"Its", "normal", ".!"};
  s21::vector<std::string> move_v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};

  move_v = std::move(v);

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(move_v.front(), "Its");
  EXPECT_EQ(move_v.back(), ".!");
}

TEST(Vector, OperatorOfEqual_InitList_1) {
  s21::vector<int> s21_v = {123, 4, 567, 8910, 1112, 1314, 15};
  std::vector<int> std_v = {123, 4, 567, 8910, 1112, 1314, 15};

  s21_v = {765, 456, 22, 11};
  std_v = {765, 456, 22, 11};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.front(), std_v.front());
  EXPECT_EQ(s21_v.back(), std_v.back());
}

TEST(Vector, OperatorOfEqual_InitList_2) {
  s21::vector<int> v = {765, 456, 22, 11};

  v = {123, 4, 567, 8910, 1112, 1314, 15};

  EXPECT_EQ(v.size(), 7);
  EXPECT_EQ(v.capacity(), 7);
  EXPECT_EQ(v.front(), 123);
  EXPECT_EQ(v.back(), 15);
}

TEST(Vector, OperatorOfEqual_InitList_3) {
  s21::vector<std::string> v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};

  v = {"Its", "normal", ".!"};

  EXPECT_EQ(v.front(), "Its");
  EXPECT_EQ(v.back(), ".!");
}

TEST(Vector, OperatorOfEqual_InitList_4) {
  s21::vector<std::string> v = {"Its", "normal", ".!"};

  v = {"123, 4, 567, 8910", "HAHAHA", "Pipebomb"};

  EXPECT_EQ(v.front(), "123, 4, 567, 8910");
  EXPECT_EQ(v.back(), "Pipebomb");
}

TEST(Vector, ElementAccess_At) {
  s21::vector<int> s21_vector = {123, 4, 567, 8910, 1112, 1314, 15};
  std::vector<int> std_v = {123, 4, 567, 8910, 1112, 1314, 15};

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.at(i), std_v.at(i));
  }
  EXPECT_ANY_THROW(s21_vector.at(19));
}

TEST(Vector, ElementAccess_At_const) {
  s21::vector<int> s21_vector = {123, 4, 567, 8910, 1112, 1314, 15};

  const auto ref = s21_vector.at(5);
  EXPECT_EQ(s21_vector[5], ref);
}

TEST(Vector, ElementAccess_CurlyBrace) {
  s21::vector<int> s21_vector = {123, 4, 567, 8910, 1112, 1314, 15};
  std::vector<int> std_v = {123, 4, 567, 8910, 1112, 1314, 15};

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  s21_vector[3] = 5;
  EXPECT_EQ(s21_vector[3], 5);
}

TEST(Vector, ElementAccess_Front) {
  s21::vector<std::string> s21_vector = {"HELLO,", "PEER.", "!HOW ARE YOU?"};
  std::vector<std::string> std_v = {"HELLO,", "PEER.", "!HOW ARE YOU?"};

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.front(), std_v.front());
}

TEST(Vector, ElementAccess_Back) {
  s21::vector<std::string> s21_vector = {"HELLO,", "PEER.", "!HOW ARE YOU?"};
  std::vector<std::string> std_v = {"HELLO,", "PEER.", "!HOW ARE YOU?"};

  EXPECT_EQ(s21_vector.back(), std_v.back());
}

TEST(Vector, ElementAccess_Data) {
  s21::vector<std::string> s21_vector = {"HELLO,", "PEER.", "!HOW ARE YOU?"};
  std::vector<std::string> std_v = {"HELLO,", "PEER.", "!HOW ARE YOU?"};

  std::string *ptr = s21_vector.data();
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(ptr[i], std_v[i]);
  }
  s21_vector = {"Pudge", " = ", "Pasha"};
  EXPECT_EQ(ptr[0], "Pudge");
}

TEST(Vector, Empty) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, Size_1) {
  s21::vector<int> s21_vector(100);
  std::vector<int> std_vector(100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Size_2) {
  s21::vector<int> s21_vector(100);
  std::vector<int> std_vector(100);

  s21_vector.pop_back();
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Size_3) {
  s21::vector<int> s21_vector(100);
  std::vector<int> std_vector(100);

  s21_vector.push_back(100);
  std_vector.push_back(100);
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Max_Size_1) {
  s21::vector<int> s21_vector(100);
  std::vector<int> std_vector(100);

  EXPECT_EQ(s21_vector.max_size(), std_vector.max_size());
}

TEST(Vector, Max_Size_2) {
  s21::vector<double> s21_vector(100);
  std::vector<double> std_vector(100);

  EXPECT_EQ(s21_vector.max_size(), std_vector.max_size());
}

TEST(Vector, Max_Size_3) {
  s21::vector<std::string> s21_vector = {"HOHHOHOH"};
  std::vector<std::string> std_vector = {"URARAU", "27 its a club"};

  EXPECT_EQ(s21_vector.max_size(), std_vector.max_size());
}

TEST(Vector, Reserve_1) {
  s21::vector<std::string> s21_vector = {"HOHHOHOH", "27 its a club"};
  std::vector<std::string> std_vector = {"URARAU", "27 its a club"};

  s21_vector.reserve(100);
  std_vector.reserve(100);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Reserve_2) {
  s21::vector<std::string> s21_vector = {"HOHHOHOH", "27 its a club"};
  std::vector<std::string> std_vector = {"URARAU", "27 its a club"};

  s21_vector.reserve(1000);
  std_vector.reserve(1000);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Reserve_3) {
  s21::vector<std::string> s21_vector = {"HOHHOHOH", "27 its a club"};
  std::vector<std::string> std_vector = {"URARAU", "27 its a club"};

  s21_vector.reserve(1);
  std_vector.reserve(1);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Capacity_1) {
  s21::vector<int> s21_vector(96);
  std::vector<int> std_vector(96);

  s21_vector.push_back(1);
  std_vector.push_back(1);

  s21_vector.push_back(12);
  std_vector.push_back(12);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Capacity_2) {
  s21::vector<int> s21_vector(96);
  std::vector<int> std_vector(96);

  s21_vector.pop_back();
  std_vector.pop_back();

  s21_vector.pop_back();
  std_vector.pop_back();

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Shrink_to_fit_1) {
  s21::vector<int> s21_vector(96);
  std::vector<int> std_vector(96);

  s21_vector.reserve(1000);
  std_vector.reserve(1000);

  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Shrink_to_fit_2) {
  s21::vector<std::string> s21_vector(10);
  std::vector<std::string> std_vector(10);

  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Vector, Clear) {
  s21::vector<int> s21_vector(100);
  std::vector<int> std_vector(100);

  s21_vector.clear();
  std_vector.clear();

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Vector, Clear_1) {
  s21::vector<int> s21_vector = {654, 23, 1234, 123, 123423, 123, -23};
  std::vector<int> std_vector = {12, 12, 12, 12};

  s21_vector.clear();
  std_vector.clear();

  EXPECT_EQ(s21_vector.capacity(), 7);
  EXPECT_EQ(s21_vector.size(), 0);
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Vector, Begin_1) {
  s21::vector<std::string> s21_vector;
  std::vector<std::string> std_vector;

  EXPECT_EQ(s21_vector.begin(), s21_vector.end());
  EXPECT_EQ(std_vector.begin(), std_vector.end());
}

TEST(Vector, Begin_2) {
  s21::vector<std::string> v = {"1, 2, 3, 4, 5", "HAHAHA", "HOHOHO", "NO"};
  auto it = v.begin();
  EXPECT_EQ(*it, "1, 2, 3, 4, 5");
  *it = "10";
  EXPECT_EQ(v[0], "10");
}

TEST(Vector, Begin_3) {
  s21::vector<std::string> v = {"1, 2, 3, 4, 5", "HAHAHA", "HOHOHO", "NO"};
  auto it = v.begin() + 1;
  EXPECT_EQ(*it, "HAHAHA");
}

TEST(Vector, End_1) {
  s21::vector<std::string> v;
  auto it = v.end();
  EXPECT_EQ(it, v.begin());
}

TEST(Vector, End_2) {
  s21::vector<std::string> v = {"1, 2, 3, 4, 5", "HAHAHA", "HOHOHO", "NO"};
  auto beginIt = v.begin();
  auto endIt = v.end();
  EXPECT_NE(beginIt, endIt);
}

TEST(Vector, End_3) {
  s21::vector<std::string> v = {"1, 2, 3, 4, 5", "HAHAHA", "HOHOHO", "NO"};
  auto endIt = v.end() - 2;
  EXPECT_EQ(*endIt, "HOHOHO");
}

TEST(Vector, Insert_1) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  std::vector<std::string> std_v = {"Prorok", "Magic and Musculs", "Berserk",
                                    "Pruh"};

  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, "Kirka");
  auto std_check = std_v.insert(std_v.begin() + 1, "Kirka");

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_2) {
  s21::vector<std::string> s21_vector(1);
  std::vector<std::string> std_v(1);

  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, "Kirka");
  auto std_check = std_v.insert(std_v.begin() + 1, "Kirka");

  for (size_t i = 0; i < std_v.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_3) {
  s21::vector<double> s21_vector(10);
  std::vector<double> std_v(10);

  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, 1234.34);
  auto std_check = std_v.insert(std_v.begin() + 1, 1234.34);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_4) {
  s21::vector<double> s21_vector(5);
  std::vector<double> std_v(5);

  for (size_t i = 0; i < 100; ++i) {
    s21_vector.insert(s21_vector.begin() + i, 1234.34 + i * 2);
    std_v.insert(std_v.begin() + i, 1234.34 + i * 2);
  }

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
}

TEST(Vector, Insert_5) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  std::vector<std::string> std_v = {"Prorok", "Magic and Musculs", "Berserk",
                                    "Pruh"};

  const std::string k = "Kirka";
  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, k);
  auto std_check = std_v.insert(std_v.begin() + 1, k);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_6) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  std::vector<std::string> std_v = {"Prorok", "Magic and Musculs", "Berserk",
                                    "Pruh"};

  const std::string k = "Kirka";
  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, 50, k);
  auto std_check = std_v.insert(std_v.begin() + 1, 50, k);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_7) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};

  const std::string k = "Kirka";
  EXPECT_ANY_THROW(s21_vector.insert(s21_vector.begin() + 110, 50, k));
}

TEST(Vector, Insert_8) {
  s21::vector<double> s21_vector(5);

  EXPECT_ANY_THROW(s21_vector.insert(s21_vector.end() - 50, 1234.34 + 2 * 2));
}

TEST(Vector, Insert_9) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};

  const std::string k = "Kirka";
  EXPECT_ANY_THROW(s21_vector.insert(s21_vector.begin() + 110, k));
}

TEST(Vector, Insert_10) {
  s21::vector<int> s21_vector = {34, 34, 12, 43, -54};
  std::vector<int> std_v = {34, 34, 12, 43, -54};

  auto s21_check = s21_vector.insert(s21_vector.begin() + 1, 111);
  auto std_check = std_v.insert(std_v.begin() + 1, 111);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_11) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  std::vector<std::string> std_v = {"Prorok", "Magic and Musculs", "Berserk",
                                    "Pruh"};

  auto s21_check = s21_vector.insert(s21_vector.end(), "Kirka");
  auto std_check = std_v.insert(std_v.end(), "Kirka");

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Insert_12) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  std::vector<std::string> std_v = {"Prorok", "Magic and Musculs", "Berserk",
                                    "Pruh"};

  auto s21_check = s21_vector.insert(s21_vector.begin(), "Kirka");
  auto std_check = std_v.insert(std_v.begin(), "Kirka");

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_v[i]);
  }
  EXPECT_EQ(s21_vector.capacity(), std_v.capacity());
  EXPECT_EQ(s21_vector.size(), std_v.size());
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(Vector, Swap_1) {
  s21::vector<std::string> s21_vector = {"Prorok", "Magic and Musculs",
                                         "Berserk", "Pruh"};
  s21::vector<std::string> s21_fector = {"Truba", "Polish", "Keyboard",
                                         "reborn", "CheckCheck"};

  s21_vector.swap(s21_fector);

  EXPECT_EQ(s21_vector[0], "Truba");
  EXPECT_EQ(s21_vector[4], "CheckCheck");
  EXPECT_EQ(s21_fector[0], "Prorok");
  EXPECT_EQ(s21_fector[3], "Pruh");
}

TEST(Vector, Swap_2) {
  s21::vector<std::string> s21_vector;
  s21::vector<std::string> s21_fector = {"Truba", "Polish", "Keyboard",
                                         "reborn", "CheckCheck"};

  s21_vector.swap(s21_fector);

  EXPECT_TRUE(s21_fector.empty());
  EXPECT_EQ(s21_vector[0], "Truba");
  EXPECT_EQ(s21_vector[4], "CheckCheck");
}

TEST(Vector, Swap_3) {
  s21::vector<std::string> s21_vector;
  s21::vector<std::string> s21_fector;

  s21_vector.swap(s21_fector);

  EXPECT_TRUE(s21_fector.empty());
  EXPECT_TRUE(s21_vector.empty());
}

TEST(Vector, Swap_4) {
  s21::vector<std::string> s21_vector(20);
  s21::vector<std::string> s21_fector;

  s21_vector.swap(s21_fector);

  EXPECT_EQ(s21_fector.size(), 20);
  EXPECT_FALSE(s21_fector.empty());
  EXPECT_TRUE(s21_vector.empty());
}

TEST(Vector, Erase_1) {
  s21::vector<std::string> s21_vector = {"Truba", "Polish", "Keyboard",
                                         "reborn", "CheckCheck"};
  std::vector<std::string> std_vector = {"Truba", "Polish", "Keyboard",
                                         "reborn", "CheckCheck"};

  std::string s21_value = *(s21_vector.erase(s21_vector.begin() + 3));
  std::string std_value = *(std_vector.erase(std_vector.begin() + 3));

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector[3], std_vector[3]);
  EXPECT_EQ(s21_value, std_value);
}

TEST(Vector, Erase_2) {
  s21::vector<std::string> s21_vector = {"Truba", "Polish", "Keyboard",
                                         "reborn", "CheckCheck"};

  EXPECT_ANY_THROW(s21_vector.erase(s21_vector.begin() - 2));
}

TEST(Vector, SameTest_1) {
  s21::vector<int> s21_vector(15);

  s21_vector.pop_back();
  s21_vector.push_back(34);
  s21_vector.push_back(999);
  s21_vector.pop_back();
  s21_vector.insert_many(s21_vector.begin(), 7, 6, 5, 4, 3);
  EXPECT_EQ(s21_vector.capacity(), 30);
  EXPECT_EQ(s21_vector.size(), 20);
  EXPECT_EQ(s21_vector.front(), 7);
  EXPECT_EQ(s21_vector.back(), 34);
}

TEST(Vector, SameTest_2) {
  s21::vector<int> s21_vector;

  s21_vector.push_back(34);
  s21_vector.push_back(4);
  s21_vector.push_back(3);
  s21_vector.push_back(2);
  s21_vector.push_back(1);
  s21_vector.push_back(999);
  s21_vector.pop_back();
  s21_vector.insert_many((s21_vector.begin() + 2), 7, 6, 5, 4, 3);
  EXPECT_EQ(s21_vector.capacity(), 10);
  EXPECT_EQ(s21_vector.size(), 10);
  EXPECT_EQ(s21_vector.front(), 34);
  EXPECT_EQ(s21_vector.back(), 1);
}

TEST(Vector, SameTest_3) {
  s21::vector<int> s21_vector(100);

  s21_vector.push_back(34);
  s21_vector.push_back(4);
  s21_vector.push_back(999);
  s21_vector[0] = 100;
  s21_vector[1] = 101;
  s21_vector.pop_back();
  s21_vector.pop_back();
  s21_vector.insert_many((s21_vector.begin() + 2), 7, 6, 5, 4, 3);
  s21_vector.shrink_to_fit();
  EXPECT_EQ(s21_vector.capacity(), 106);
  EXPECT_EQ(s21_vector.size(), 106);
  EXPECT_EQ(s21_vector.front(), 100);
  EXPECT_EQ(s21_vector.back(), 34);
}

TEST(Vector, SameTest_4) {
  s21::vector<int> s21_vector(100);

  s21_vector.erase(s21_vector.begin());
  s21_vector.erase(s21_vector.begin());
  s21_vector.erase(s21_vector.begin());
  s21_vector.erase(s21_vector.begin());
  s21_vector.push_back(34);
  s21_vector.push_back(4);
  s21_vector.push_back(999);
  s21_vector[0] = 100;
  s21_vector[1] = 101;
  s21_vector.pop_back();
  s21_vector.pop_back();
  s21_vector.insert_many((s21_vector.begin() + 2), 7, 6, 5, 4, 3);
  s21_vector.shrink_to_fit();
  EXPECT_EQ(s21_vector.capacity(), 102);
  EXPECT_EQ(s21_vector.size(), 102);
  EXPECT_EQ(s21_vector.front(), 100);
  EXPECT_EQ(s21_vector.back(), 34);
}

TEST(Vector_Dop_method, Insert_many_1) {
  s21::vector<int> s21_vector = {34, 654, -23, 344, 8787};

  s21_vector.insert_many(s21_vector.begin(), 434, 111, 111);
  EXPECT_EQ(s21_vector.size(), 8);
  EXPECT_EQ(s21_vector.capacity(), 8);
  EXPECT_EQ(*s21_vector.begin(), 434);
}

TEST(Vector_Dop_method, Insert_many_2) {
  s21::vector<int> s21_vector = {34, 654, -23, 344, 8787};

  s21_vector.insert_many(s21_vector.end(), 434, 111, 111);
  EXPECT_EQ(s21_vector.size(), 8);
  EXPECT_EQ(s21_vector.capacity(), 8);
  EXPECT_EQ(*(s21_vector.end() - 1), 111);
}

TEST(Vector_Dop_method, Insert_many_3) {
  s21::vector<std::string> s21_vector = {"34, 654, -23, 344, 8787", "HIHI",
                                         "DONT DO HIHI"};

  s21_vector.insert_many(s21_vector.end(), "434", "WHAT", "DO HUHU");
  EXPECT_EQ(s21_vector.size(), 6);
  EXPECT_EQ(s21_vector.capacity(), 6);
  EXPECT_EQ(*(s21_vector.end() - 1), "DO HUHU");
}

TEST(Vector_Dop_method, Insert_many_4) {
  s21::vector<std::string> s21_vector = {"34, 654, -23, 344, 8787", "HIHI",
                                         "DONT DO HIHI"};

  s21_vector.insert_many(s21_vector.end() - 2, "434", "WHAT", "DO HUHU");
  EXPECT_EQ(s21_vector.size(), 6);
  EXPECT_EQ(s21_vector.capacity(), 6);
  EXPECT_EQ(*(s21_vector.end() - 3), "DO HUHU");
}

TEST(Vector_Dop_method, Insert_many_5) {
  s21::vector<std::string> s21_vector = {"34, 654, -23, 344, 8787", "HIHI",
                                         "DONT DO HIHI"};

  EXPECT_ANY_THROW(
      s21_vector.insert_many(s21_vector.end() - 5, "434", "WHAT", "DO HUHU"));
}

TEST(Vector_Dop_method, Insert_many_6) {
  s21::vector<std::string> s21_vector = {"34, 654, -23, 344, 8787", "HIHI",
                                         "DONT DO HIHI"};

  EXPECT_ANY_THROW(
      s21_vector.insert_many(s21_vector.begin() + 7, "434", "WHAT", "DO HUHU"));
}

TEST(Vector_Dop_method, Insert_many_back_1) {
  s21::vector<int> s21_vector = {34, 654, -23, 344, 8787};

  s21_vector.insert_many_back(434, 111, 111);
  EXPECT_EQ(s21_vector.size(), 8);
  EXPECT_EQ(s21_vector.capacity(), 8);
  EXPECT_EQ(*(s21_vector.end() - 1), 111);
}

TEST(Vector_Dop_method, Insert_many_back_2) {
  s21::vector<std::string> s21_vector = {"34, 654, -23, 344, 8787", "HIHI",
                                         "DONT DO HIHI"};

  s21_vector.insert_many_back("434, 111, 111", "HUHAHI", "Kisk", "Dub zeleney");

  EXPECT_EQ(s21_vector.size(), 7);
  EXPECT_EQ(s21_vector.capacity(), 7);
  EXPECT_EQ(*(s21_vector.end() - 1), "Dub zeleney");

  s21_vector.insert_many_back("NOOOoooooooo");

  EXPECT_EQ(s21_vector.size(), 8);
  EXPECT_EQ(s21_vector.capacity(), 8);
  EXPECT_EQ(*(s21_vector.end() - 1), "NOOOoooooooo");
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
