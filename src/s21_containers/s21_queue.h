#ifndef S21_CONTAINERS_S21_QUEUE_H
#define S21_CONTAINERS_S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  // QUEUE MEMBER TYPE

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // QUEUE MAMBER FUNCTIONS

  // default constructor, creates empty queue
  queue() { inner_list = list<value_type>(); }

  // initializer list constructor, creates queue initizialized using
  // std::initializer_list
  queue(std::initializer_list<value_type> const &items) {
    inner_list = list<value_type>(items);
  }

  // copy constructor
  queue(const queue &temp_queue) : inner_list(temp_queue.inner_list) {}

  // move constructor
  queue(queue &&temp_queue) noexcept
      : inner_list(std::move(temp_queue.inner_list)) {}

  // destructor
  ~queue() { this->inner_list.clear(); }

  // assignment operator overload for moving object
  queue &operator=(queue &&temp_queue) {
    this->inner_list = std::move(temp_queue.inner_list);
    return *this;
  }

  // QUEUE CAPACITY

  // checks whether the container is empty
  bool empty() { return inner_list.empty(); }

  // returns the number of elements
  size_type size() { return inner_list.size(); }

  // QUEUE MODIFIERS

  // inserts element at the top
  void push(value_type value) { this->inner_list.push_back(value); }

  // removes the top element
  void pop() { this->inner_list.pop_front(); }

  // swaps the contents
  void swap(queue &other) { this->inner_list.swap(other.inner_list); }

  // QUEUE ELEMENT ACCESS

  // accesses the top element
  const_reference front() { return this->inner_list.front(); }

  const_reference back() { return this->inner_list.back(); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    return this->inner_list.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  list<value_type> inner_list;
};
}  // namespace s21

#endif  // S21_CONTAINERS_S21_QUEUE_H