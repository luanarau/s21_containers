#ifndef S21_CONTAINERS_S21_SET_H
#define S21_CONTAINERS_S21_SET_H

#include <algorithm>
#include <limits>

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename Tree<Key, Key>::Iterator;
  using const_iterator = typename Tree<Key, Key>::ConstIterator;

  set() : RBTree<key_type, value_type>(){};
  set(const std::initializer_list<value_type> &items);
  set(const set &m) : RBTree<key_type, value_type>(m){};
  set(set &&m) noexcept : RBTree<key_type, value_type>(std::move(m)){};
  ~set() = default;
  set &operator=(set &&other) noexcept;
  set &operator=(const set &other);

  bool empty();
  size_type size();
  size_type max_size() noexcept;

  bool contains(const Key &key);
  iterator find(const Key &key);

  void clear();
  [[maybe_unused]] std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename Key>
set<Key>::set(const typename std::initializer_list<value_type> &items) {
  Tree<Key, Key>::size = 0;
  Tree<Key, Key>::root = nullptr;
  for (value_type i : items) insert(i);
}

template <typename Key>
inline set<Key> &set<Key>::operator=(set &&other) noexcept {
  if (this != &other) {
    Tree<Key, Key>::root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename Key>
inline set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    set temp(other);
    clear();
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key>
inline bool set<Key>::empty() {
  return Tree<Key, Key>::isempty();
}

template <typename Key>
inline typename set<Key>::size_type set<Key>::size() {
  return Tree<Key, Key>::sizeofTree();
}

template <typename Key>
inline typename set<Key>::size_type set<Key>::max_size() noexcept {
  return std::numeric_limits<typename set<Key>::size_type>::max() /
         sizeof(set<Key>);
}

template <typename Key>
inline bool set<Key>::contains(const Key &key) {
  return s21::Tree<Key, Key>::finder(key);
}

template <typename Key>
inline typename s21::set<Key>::iterator set<Key>::find(const Key &key) {
  return s21::Tree<Key, Key>::find(key);
}

template <typename Key>
inline void set<Key>::clear() {
  Tree<Key, Key>::clear();
}

template <typename Key>
inline std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const typename set<Key>::value_type &value) {
  std::pair<typename set<Key>::iterator, bool> ret;
  if (contains(value)) {
    ret = std::make_pair(Tree<Key, Key>::end(), false);
    return ret;
  }
  s21::Tree<Key, Key>::insert(value, value);
  s21::RBTree<Key, Key>::fixInsert(value);
  ret = std::make_pair(s21::Tree<Key, Key>::findIter(value), true);
  return ret;
}

template <typename Key>
inline void set<Key>::erase(typename set<Key>::iterator pos) {
  std::pair<const Key, Key> ret = *pos;
  RBTree<Key, Key>::remove(ret.first);
}

template <typename Key>
inline void set<Key>::swap(set &other) {
  Tree<Key, Key>::swap(other);
}

template <typename Key>
inline void set<Key>::merge(set &other) {
  typename set<Key>::iterator pos = other.Tree<Key, Key>::begin();
  for (auto it = pos; it != other.Tree<Key, Key>::end();) {
    if ((insert((*it).first)).second) {
      auto temp_it = it;
      ++it;
      other.erase(temp_it);
    } else
      ++it;
  }
}

template <typename Key>
template <typename... Args>
inline s21::vector<std::pair<typename set<Key>::iterator, bool>>
set<Key>::insert_many(Args &&...args) {
  return {insert(std::forward<Args>(args))...};
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_H