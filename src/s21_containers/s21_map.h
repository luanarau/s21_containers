#ifndef S21_CONTAINERS_S21_MAP_H
#define S21_CONTAINERS_S21_MAP_H

#include <algorithm>
#include <limits>
#include <utility>

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map : public RBTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename Tree<Key, T>::Iterator;
  using const_iterator = typename Tree<Key, T>::ConstIterator;

  map() : RBTree<key_type, mapped_type>(){};
  map(std::initializer_list<
      typename RBTree<key_type, mapped_type>::value_type> const &items)
      : RBTree<key_type, mapped_type>(items){};
  map(const map &m) : RBTree<key_type, mapped_type>(m){};
  map(map &&m) noexcept : RBTree<key_type, mapped_type>(std::move(m)){};
  ~map() = default;
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);

  T &at(const Key &key);
  T &operator[](const Key &key);

  bool empty();
  size_type size();
  size_type max_size() noexcept;

  bool contains(const Key &key);

  void clear();
  [[maybe_unused]] std::pair<iterator, bool> insert(const value_type &value);
  [[maybe_unused]] std::pair<iterator, bool> insert(const Key &key,
                                                    const T &obj);
  [[maybe_unused]] std::pair<iterator, bool> insert_or_assign(const Key &key,
                                                              const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename Key, typename T>
inline map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    Tree<Key, Key>::root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
inline map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    map temp(other);
    clear();
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename T>
inline T &map<Key, T>::at(const Key &key) {
  Key k = key;
  Key &ref = k;
  if (contains(key))
    return Tree<Key, T>::search(ref)->data;
  else
    throw typename RBTree<Key, T>::Readwrite{};
}

template <typename Key, typename T>
inline T &map<Key, T>::operator[](const Key &key) {
  Key k = key;
  Key &ref = k;
  if (contains(key)) {
    return Tree<Key, T>::search(ref)->data;
  } else
    throw typename RBTree<Key, T>::Readwrite{};
}

template <typename Key, typename T>
inline bool map<Key, T>::empty() {
  return Tree<Key, T>::isempty();
}

template <typename Key, typename T>
inline typename map<Key, T>::size_type map<Key, T>::size() {
  return Tree<Key, T>::sizeofTree();
}

template <typename Key, typename T>
inline typename map<Key, T>::size_type map<Key, T>::max_size() noexcept {
  return std::numeric_limits<typename map<Key, T>::size_type>::max() /
         sizeof(map<Key, T>);
}

template <typename Key, typename T>
inline bool map<Key, T>::contains(const Key &key) {
  return s21::Tree<Key, T>::finder(key);
}

template <typename Key, typename T>
inline void map<Key, T>::clear() {
  Tree<Key, T>::clear();
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const typename map<Key, T>::value_type &value) {
  return map<Key, T>::insert(value.first, value.second);
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<typename map<Key, T>::iterator, bool> ret;
  if (contains(key)) {
    ret = std::make_pair(Tree<Key, T>::end(), false);
    return ret;
  }
  s21::Tree<Key, T>::insert(key, obj);
  s21::RBTree<Key, T>::fixInsert(key);
  ret = std::make_pair(s21::Tree<Key, T>::findIter(key), true);
  return ret;
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  if (contains(key)) {
    Tree<Key, T>::replace(key, obj);
    s21::RBTree<Key, T>::fixInsert(key);
    auto aboba = s21::Tree<Key, T>::findIter(key);
    auto ret = std::make_pair(aboba, false);
    return ret;
  }
  Tree<Key, T>::insert(key, obj);
  RBTree<Key, T>::fixInsert(key);
  return std::make_pair(s21::Tree<Key, T>::findIter(key), true);
}

template <typename Key, typename T>
inline void map<Key, T>::erase(typename map<Key, T>::iterator pos) {
  std::pair<const Key, T> ret = *pos;
  RBTree<Key, T>::remove(ret.first);
}

template <typename Key, typename T>
inline void map<Key, T>::swap(map &other) {
  Tree<Key, T>::swap(other);
}

template <typename Key, typename T>
inline void map<Key, T>::merge(map &other) {
  typename map<Key, T>::iterator pos = other.Tree<Key, T>::begin();
  for (auto it = pos; it != other.Tree<Key, T>::end();) {
    if (insert((*it).first, (*it).second).second) {
      auto temp_it = it;
      ++it;
      other.erase(temp_it);
    } else
      ++it;
  }
}

template <typename Key, typename T>
template <typename... Args>
inline s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  return {insert(std::forward<Args>(args))...};
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MAP_H