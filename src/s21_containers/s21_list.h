#ifndef S21_CONTAINERS_S21_LIST_H
#define S21_CONTAINERS_S21_LIST_H

#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class list {
 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}

    Node(T value, Node *nextNode, Node *prevNode)
        : data(value), next(nextNode), prev(prevNode) {}

    T getData() const { return data; }

    void setData(T newData) { data = newData; }

    Node *getNext() const { return next; }

    void setNext(Node *newNext) { next = newNext; }

    Node *getPrev() const { return prev; }

    void setPrev(Node *newPrev) { prev = newPrev; }
  };

  Node *head;
  size_t count;

  void checkIndex(size_t index) const;

  Node *getNodeByIndex(size_t index) const;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class listIterator {
   private:
    Node *current;

   public:
    listIterator(Node *node) : current(node) {}

    listIterator(list<T> &l, size_t index) {
      if (index < l.count) {
        current = l.getNodeByIndex(index);
      } else {
        current = nullptr;
      }
    }

    typename list<T>::Node *getNode() const { return current; }

    listIterator operator++() {
      current = current->getNext();
      return *this;
    }

    listIterator operator--() {
      current = current->getPrev();
      return *this;
    }

    listIterator operator++(int) {
      listIterator temp = *this;
      current = current->getNext();
      return temp;
    }

    listIterator operator--(int) {
      listIterator temp = *this;
      current = current->getPrev();
      return temp;
    }

    reference operator*() const { return current->data; }

    listIterator operator+(size_t n) const {
      auto temp = *this;

      for (size_t i = 0; i < n; ++i) {
        ++temp;
      }

      return temp;
    }

    listIterator &operator+=(size_t n) {
      for (size_t i = 0; i < n; ++i) {
        ++(*this);
      }

      return *this;
    }

    bool operator==(const listIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const listIterator &other) const {
      return current != other.current;
    }
  };

  using iterator = listIterator;
  using const_iterator = const listIterator;

  list();

  list(size_type n);

  list(std::initializer_list<value_type> const &items);

  list(const list &l);

  list(list &&l) noexcept;

  ~list();

  list &operator=(list &&l) noexcept;

  const_reference front();

  const_reference back();

  iterator begin() const;

  iterator end() const;

  size_type size() const;

  bool empty() const;

  size_type max_size() const;

  void clear();

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  void push_back(const_reference value);

  void pop_back();

  void push_front(const_reference value);

  void pop_front();

  void swap(list &other);

  void merge(list &other);

  void splice(const_iterator pos, list &other);

  void reverse();

  void unique();

  void sort();

  T getDataByIndex(size_t index) const;

  T setDataByIndex(size_t index, T data);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_CONTAINERS_S21_LIST_H