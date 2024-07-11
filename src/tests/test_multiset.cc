#include "test_entry.h"

TEST(multiset, allcase) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  std::pair<typename s21::multiset<int>::iterator,
            typename s21::multiset<int>::iterator>
      p;
  p = my_multiset.equal_range(10);
  auto it_temp = my_multiset.lower_bound(10);
  it_temp = my_multiset.upper_bound(10);
  EXPECT_EQ(my_multiset.size(), 10U);
  auto it = my_multiset.begin();
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 9U);
  it = my_multiset.begin();
  EXPECT_EQ((int)(*it).first, 10);
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 8U);
  my_multiset.max_size();
  my_multiset.insert(8);
  my_multiset.insert(9);
  my_multiset.Tree<int, int>::remove(8);
  my_multiset.clear();
  my_multiset.insert(8);
  my_multiset.insert(10);
  my_multiset.Tree<int, int>::remove(10);
  my_multiset.insert(10);
  my_multiset.insert(7);
  my_multiset.insert(6);
  my_multiset.Tree<int, int>::remove(7);
  my_multiset.insert(7);
  my_multiset.insert(9);
  auto it1 = my_multiset.begin(), it2 = it1;
  for (; it1 != my_multiset.end(); ++it1) it2 = it1;
  for (; it2 != my_multiset.begin(); --it2)
    ;
}

TEST(multiset, ContainsMultiset) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::multiset<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_multiset.contains(2), false);
  EXPECT_EQ(my_multiset.contains(2.1), true);
}

TEST(multiset, FindMultiset) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5, 6};
  auto my_it = my_set.find(4);
  EXPECT_TRUE((*my_it).second == 4);
}

TEST(multiset, SwapMultiset) {
  s21::multiset<int> my_set = {1};
  s21::multiset<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  auto check = (*(my_set.begin())).first;
  EXPECT_EQ(check, 3);
  check = (*my_swap_set.begin()).first;
  EXPECT_EQ(check, 1);
}

TEST(multiset, MergeMultiset) {
  s21::multiset<int> my_set = {1};
  s21::multiset<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*orig_it) == (*my_it).first);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(multiset, CountMultiset) {
  s21::multiset<int> my_set = {3, 4, 5, 5};
  EXPECT_EQ(my_set.count(5), 2);
}

TEST(multiset, InsManyMultiset) {
  s21::multiset<int> my_set;
  s21::vector vec = my_set.insert_many(10, 20, 30);
  auto x = (*(my_set.begin())).second;
  EXPECT_EQ(x, 10);
  s21::multiset<int> set({1, 2, 3, 4, 5, 6, 7, 8, 9});
  set.erase(set.find(6));
  set.erase(set.find(7));
  set.erase(set.find(4));
  s21::multiset<int> copy, copy2;
  copy = set;
  copy2 = std::move(set);
}
