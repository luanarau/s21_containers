#ifndef S21_CONTAINERS_S21_MULTISET_H
#define S21_CONTAINERS_S21_MULTISET_H

#include <algorithm>
#include <limits>

#include "../s21_containers/RBTree.h"
#include "../s21_containers/s21_vector.h"

namespace s21 {
template <typename Key>
class multiset : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename Tree<Key, Key>::Iterator;
  using const_iterator = typename Tree<Key, Key>::ConstIterator;

  multiset() : RBTree<key_type, value_type>(){};
  multiset(const std::initializer_list<value_type> &items);
  multiset(const multiset &m) : RBTree<key_type, value_type>(m){};
  multiset(multiset &&m) noexcept
      : RBTree<key_type, value_type>(std::move(m)){};
  ~multiset() = default;
  multiset &operator=(multiset &&other) noexcept;
  multiset &operator=(const multiset &other);

  bool empty();
  size_type size();
  size_type max_size() noexcept;

  bool contains(const Key &key);
  iterator find(const Key &key);

  void clear();
  [[maybe_unused]] iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  size_type count(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  s21::vector<iterator> insert_many(Args &&...args);
};

template <typename Key>
multiset<Key>::multiset(
    const typename std::initializer_list<value_type> &items) {
  Tree<Key, Key>::size = 0;
  Tree<Key, Key>::root = nullptr;
  for (value_type i : items) insert(i);
}

template <typename Key>
inline multiset<Key> &multiset<Key>::operator=(multiset &&other) noexcept {
  if (this != &other) {
    Tree<Key, Key>::root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename Key>
inline multiset<Key> &multiset<Key>::operator=(const multiset &other) {
  if (this != &other) {
    multiset temp(other);
    clear();
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key>
inline bool multiset<Key>::empty() {
  return Tree<Key, Key>::isempty();
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::size() {
  return Tree<Key, Key>::sizeofTree();
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::max_size() noexcept {
  return std::numeric_limits<typename multiset<Key>::size_type>::max() /
         sizeof(multiset<Key>);
}

template <typename Key>
inline bool multiset<Key>::contains(const Key &key) {
  return s21::Tree<Key, Key>::finder(key);
}

template <typename Key>
inline typename s21::multiset<Key>::iterator multiset<Key>::find(
    const Key &key) {
  return s21::Tree<Key, Key>::find(key);
}

template <typename Key>
inline void multiset<Key>::clear() {
  Tree<Key, Key>::clear();
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::insert(
    const typename multiset<Key>::value_type &value) {
  typename multiset<Key>::iterator ret;
  s21::Tree<Key, Key>::insert(value, value);
  s21::RBTree<Key, Key>::fixInsert(value);
  ret = s21::Tree<Key, Key>::findIter(value);
  return ret;
}

template <typename Key>
inline void multiset<Key>::erase(typename multiset<Key>::iterator pos) {
  std::pair<const Key, Key> ret = *pos;
  RBTree<Key, Key>::remove(ret.first);
}

template <typename Key>
inline void multiset<Key>::swap(multiset &other) {
  Tree<Key, Key>::swap(other);
}

template <typename Key>
inline void multiset<Key>::merge(multiset &other) {
  typename multiset<Key>::iterator pos = other.Tree<Key, Key>::begin();
  for (auto it = pos; it != other.Tree<Key, Key>::end();) {
    insert((*it).first);
    auto temp_it = it;
    ++it;
    other.erase(temp_it);
  }
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  if (!contains(key)) return 0;
  size_type size = 0;
  iterator pos = find(key);
  while (pos != Tree<Key, Key>::end() && (*pos).second == key) {
    size++;
    ++pos;
  }
  return size;
}

template <typename Key>
inline std::pair<typename multiset<Key>::iterator,
                 typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  if (!contains(key))
    return std::make_pair(Tree<Key, Key>::end(), Tree<Key, Key>::end());
  iterator pos1 = find(key), pos2(pos1), pos3(pos1);
  while (pos2 != Tree<Key, Key>::end() && (*pos2).second == key) {
    pos3 = pos2;
    ++pos2;
  }
  return std::make_pair(pos1, pos3);
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::lower_bound(
    const Key &key) {
  if (!contains(key)) return Tree<Key, Key>::end();
  iterator pos1 = find(key), pos2(pos1);
  while (pos2 != Tree<Key, Key>::end() && (*pos2).second == key) {
    pos1 = pos2;
    ++pos2;
  }
  return pos1;
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::upper_bound(
    const Key &key) {
  if (!contains(key)) return Tree<Key, Key>::end();
  iterator pos = find(key), pos2(pos);
  while (pos != Tree<Key, Key>::end() && (*pos).second == key) {
    pos2 = pos;
    ++pos;
  }
  return pos;
}

template <typename Key>
template <typename... Args>
inline s21::vector<typename multiset<Key>::iterator> multiset<Key>::insert_many(
    Args &&...args) {
  return {insert(std::forward<Args>(args))...};
}

}  // namespace s21

#endif  // S21_CONTAINERSPLUS_S21_MULTISET_H