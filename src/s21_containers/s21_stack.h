#ifndef S21_CONTAINERS_S21_STACK_H
#define S21_CONTAINERS_S21_STACK_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  // STACK MEMBER TYPE

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // STACK MAMBER FUNCTIONS

  // default constructor, creates empty stack
  stack() { inner_list = list<value_type>(); }

  // initializer list constructor, creates stack initizialized using
  // std::initializer_list
  stack(std::initializer_list<value_type> const &items) {
    inner_list = list<value_type>(items);
  }

  // copy constructor
  stack(const stack &temp_stack) : inner_list(temp_stack.inner_list) {}

  // move constructor
  stack(stack &&temp_stack) noexcept
      : inner_list(std::move(temp_stack.inner_list)) {}

  // destructor
  ~stack() { this->inner_list.clear(); }

  // assignment operator overload for moving object
  stack &operator=(stack &&temp_stack) {
    this->inner_list = std::move(temp_stack.inner_list);
    return *this;
  }

  // STACK CAPACITY

  // checks whether the container is empty
  bool empty() { return inner_list.empty(); }

  // returns the number of elements
  size_type size() { return inner_list.size(); }

  // STACK MODIFIERS

  // inserts element at the top
  void push(value_type value) { this->inner_list.push_back(value); }

  // removes the top element
  void pop() { this->inner_list.pop_back(); }

  // swaps the contents
  void swap(stack &other) { this->inner_list.swap(other.inner_list); }

  // STACK ELEMENT ACCESS

  // accesses the top element
  const_reference top() { return this->inner_list.back(); }

 private:
  list<value_type> inner_list;
};
}  // namespace s21

#endif  // S21_CONTAINERS_S21_STACK_H