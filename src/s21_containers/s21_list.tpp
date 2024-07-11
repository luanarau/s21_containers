#include "s21_list.h"

namespace s21 {
template <typename T>
list<T>::list() : head(nullptr), count(0) {}

template <typename T>
list<T>::list(size_type n) : head(nullptr), count(0) {
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head(nullptr), count(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list &l) : head(nullptr), count(0) {
  for (const auto &item : l) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(list<T> &&l) noexcept : head(l.head), count(l.count) {
  l.head = nullptr;
  l.count = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    head = l.head;
    count = l.count;
    l.head = nullptr;
    l.count = 0;
  }

  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (!head) {
    throw std::out_of_range("List is empty");
  }

  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (!head) {
    throw std::out_of_range("List is empty");
  }

  auto current = begin();
  auto last = end();

  if (current == last) {
    throw std::out_of_range("List is empty");
  }

  auto prev = current;

  while (++current != last) {
    prev = current;
  }

  return *prev;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
  return iterator(head);
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return count;
}

template <typename T>
bool list<T>::empty() const {
  return count == 0;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::clear() {
  auto current = begin();
  auto last = end();

  while (current != last) {
    auto *temp = current.getNode();
    ++current;
    delete temp;
  }

  head = nullptr;
  count = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *newNode = new Node(value, nullptr, nullptr);

  if (pos == begin()) {
    newNode->setNext(head);

    if (head) {
      head->setPrev(newNode);
    }

    head = newNode;
  } else if (pos == end()) {
    Node *last = getNodeByIndex(count - 1);
    last->setNext(newNode);
    newNode->setPrev(last);
  } else {
    Node *current = pos.getNode();
    newNode->setNext(current);
    newNode->setPrev(current->getPrev());

    if (current->getPrev()) {
      current->getPrev()->setNext(newNode);
    }

    current->setPrev(newNode);
  }

  count++;

  return iterator(newNode);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == end()) {
    return;
  }

  auto *current = pos.getNode();

  if (current->getPrev()) {
    current->getPrev()->setNext(current->getNext());
  } else {
    head = current->getNext();
  }

  if (current->getNext()) {
    current->getNext()->setPrev(current->getPrev());
  }

  delete current;
  count--;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void list<T>::pop_back() {
  if (!head) {
    return;
  }

  Node *last = getNodeByIndex(count - 1);

  if (last->getPrev()) {
    last->getPrev()->setNext(nullptr);
  } else {
    head = nullptr;
  }

  delete last;
  --count;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  head = new Node(value, head, nullptr);

  if (head->getNext()) {
    head->getNext()->setPrev(head);
  }

  count++;
}

template <typename T>
void list<T>::pop_front() {
  if (!head) {
    return;
  }

  auto *temp = head;
  head = head->getNext();

  if (head) {
    head->setPrev(nullptr);
  }

  delete temp;

  count--;
}

template <typename T>
void list<T>::swap(list<T> &other) {
  auto tempHead = head;
  auto tempCount = count;

  head = other.head;
  count = other.count;

  other.head = tempHead;
  other.count = tempCount;
}

template <typename T>
void list<T>::merge(list<T> &other) {
  list mergedList;

  auto it1 = begin();
  auto it2 = other.begin();

  while (it1 != end() && it2 != other.end()) {
    if (*it1 <= *it2) {
      mergedList.push_back(*it1);
      ++it1;
    } else {
      mergedList.push_back(*it2);
      ++it2;
    }
  }

  while (it1 != end()) {
    mergedList.push_back(*it1);
    ++it1;
  }

  while (it2 != other.end()) {
    mergedList.push_back(*it2);
    ++it2;
  }

  clear();

  for (const auto &item : mergedList) {
    push_back(item);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list<T> &other) {
  if (other.empty()) {
    return;
  }

  iterator insertPos = pos;

  if (pos == end()) {
    for (const auto &item : other) {
      push_back(item);
    }
  } else {
    for (const auto &item : other) {
      insert(insertPos, item);
    }
  }

  other.clear();
}

template <typename T>
void list<T>::reverse() {
  if (!head) {
    return;
  }

  iterator current = begin();
  iterator previous = nullptr;
  iterator next(head);

  while (current != nullptr) {
    next = current + 1;
    current.getNode()->setNext(previous.getNode());
    previous = current;
    current = next;
  }

  head = previous.getNode();
}

template <typename T>
void list<T>::unique() {
  if (!head) {
    return;
  }

  iterator current = begin();
  iterator previous = nullptr;

  while (current != end()) {
    if (previous.getNode() && *current == *previous) {
      iterator temp = current;
      previous.getNode()->setNext(current.getNode()->getNext());
      current = current.getNode()->getNext();
      delete temp.getNode();
      count--;
    } else {
      previous = current;
      ++current;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (count <= 1) {
    return;
  }

  for (long unsigned int i = 0; i < count - 1; i++) {
    for (long unsigned int j = 0; j < count - i - 1; j++) {
      if (getDataByIndex(j) > getDataByIndex(j + 1)) {
        T temp = setDataByIndex(j, getDataByIndex(j + 1));
        setDataByIndex(j + 1, temp);
      }
    }
  }
}

template <typename T>
void list<T>::checkIndex(size_t index) const {
  if (index >= count) {
    throw std::out_of_range("Index " + std::to_string(index) + " missing.");
  }
}

template <typename T>
typename list<T>::Node *list<T>::getNodeByIndex(size_t index) const {
  auto *current = head;

  for (size_t i = 0; i < index; i++) {
    current = current->getNext();
  }

  return current;
}

template <typename T>
T list<T>::getDataByIndex(size_t index) const {
  checkIndex(index);

  return getNodeByIndex(index)->getData();
}

template <typename T>
T list<T>::setDataByIndex(size_t index, T data) {
  checkIndex(index);

  auto *node = getNodeByIndex(index);
  T oldData = node->getData();
  node->setData(data);

  return oldData;
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it = pos;
  ((it = insert(it, std::forward<Args>(args)), ++it), ...);
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(args), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(begin(), args...);
}

}  // namespace s21
