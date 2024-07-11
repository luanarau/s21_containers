#ifndef S21_CONTAINERS_S21_VECTOR_H
#define S21_CONTAINERS_S21_VECTOR_H

#include <initializer_list>

namespace s21 {
template <typename T, typename Alloc = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using alloc_traits = std::allocator_traits<Alloc>;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept(alloc_traits::propagate_on_container_swap::value);
  ~vector();

  vector &operator=(const vector &v);
  vector &operator=(vector &&v) noexcept(
      alloc_traits::propagate_on_container_move_assignment::value);
  vector &operator=(std::initializer_list<value_type> const &items);

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front();
  const_reference front() const;

  const_reference back() const;
  reference back();

  iterator data() noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type new_capacity);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(const_iterator pos, const_reference value);
  iterator insert(const_iterator pos, T &&value);
  iterator insert(const_iterator pos, size_type count, const T &value);
  iterator erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept(
      alloc_traits::propagate_on_container_swap::value);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  iterator data_;
  size_type size_;
  size_type capacity_;
  Alloc alloc_;

  void destroy_data();
  void init_value_type_for_insert(size_type length);
  void add_value_in_back(iterator cur_data, const_reference value);
  void copy_in_data(const iterator other_data);
  void copy_from_data(iterator new_data);
};

template <typename T, typename Alloc>
inline vector<T, Alloc>::vector()
    : data_(nullptr), size_(0), capacity_(0), alloc_() {}

template <typename T, typename Alloc>
inline vector<T, Alloc>::vector(size_type n) : size_(n), capacity_(n) {
  if (n > 0) {
    data_ = alloc_traits::allocate(alloc_, size_);
    for (size_type i = 0; i < size_; ++i) {
      try {
        alloc_traits::construct(alloc_, data_ + i, value_type(value_type()));
      } catch (...) {
        for (size_type j = 0; j < i; ++j) {
          alloc_traits::destroy(alloc_, data_ + j);
        }
        alloc_traits::deallocate(alloc_, data_, size_);
        throw;
      }
    }
  } else {
    data_ = nullptr;
  }
}

template <typename T, typename Alloc>
inline vector<T, Alloc>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, typename Alloc>
inline vector<T, Alloc>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_) {
  if (v.empty()) {
    data_ = nullptr;
  } else {
    copy_in_data(v.data_);
  }
}

template <typename T, typename Alloc>
inline vector<T, Alloc>::vector(vector &&v) noexcept(
    alloc_traits::propagate_on_container_swap::value)
    : vector() {
  if (this != &v) {
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(alloc_, v.alloc_);
    std::swap(data_, v.data_);
  }
}

template <typename T, typename Alloc>
inline vector<T, Alloc>::~vector() {
  destroy_data();

  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T, typename Alloc>
inline vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &v) {
  if (this != &v) {
    if (!empty()) {
      destroy_data();
    }

    size_ = v.size_;
    capacity_ = v.capacity_;

    copy_in_data(v.data_);
  }
  return *this;
}

template <typename T, typename Alloc>
inline vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&v) noexcept(
    alloc_traits::propagate_on_container_move_assignment::value) {
  if (this != &v) {
    if (!empty()) {
      destroy_data();
    }

    alloc_ = std::move(v.alloc_);
    data_ = std::move(v.data_);
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }
  return *this;
}

template <typename T, typename Alloc>
inline vector<T, Alloc> &vector<T, Alloc>::operator=(
    std::initializer_list<value_type> const &items) {
  if (!empty() && items.size() > capacity_) {
    destroy_data();
    data_ = alloc_traits::allocate(alloc_, items.size());
    capacity_ = items.size();
  } else if (!empty() && items.size() <= capacity_) {
    clear();
  }

  size_ = items.size();
  std::uninitialized_copy(items.begin(), items.end(), data_);

  return *this;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::reference vector<T, Alloc>::at(
    size_type pos) {
  return (pos >= size() ? throw std::out_of_range("Index out of range")
                        : data_[pos]);
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  return (pos >= size() ? throw std::out_of_range("Index out of range")
                        : data_[pos]);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
  return data_[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
  return data_[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
  return (size_ > 0 ? data_[size_ - 1]
                    : throw std::out_of_range("Index out of range"));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
  return (size_ > 0 ? data_[size_ - 1]
                    : throw std::out_of_range("Index out of range"));
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::data() noexcept {
  return data_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept {
  return data_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin()
    const noexcept {
  return data_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept {
  return (data_ + size());
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end()
    const noexcept {
  return (data_ + size());
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::clear() {
  if (data_) {
    for (size_type i = 0; i < size_; ++i) {
      alloc_traits::destroy(alloc_, data_ + i);
    }
  }
  size_ = 0;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    iterator pos) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("Iterator out of range");
  }
  size_t iter_pos = pos - begin();

  --size_;
  for (size_type i = iter_pos; i < size_; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }

  return begin() + iter_pos;
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::push_back(const_reference value) {
  if (size_ == capacity_) {
    size_type new_capacity = (capacity_ > 0 ? capacity_ * 2 : 1);
    iterator new_data = alloc_traits::allocate(alloc_, new_capacity);

    copy_from_data(new_data);

    add_value_in_back(new_data, value);

    destroy_data();

    capacity_ = new_capacity;
    data_ = new_data;
  } else {
    add_value_in_back(data_, value);
  }
  ++size_;
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::pop_back() {
  if (!empty()) {
    --size_;
    (data_ + size_)->~value_type();
  }
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::swap(vector &other) noexcept(
    alloc_traits::propagate_on_container_swap::value) {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(alloc_, other.alloc_);
    std::swap(data_, other.data_);
  }
}

template <typename T, typename Alloc>
inline bool vector<T, Alloc>::empty() const noexcept {
  return size() == 0;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
  size_type max_alloc = alloc_traits::max_size(alloc_);
  return max_alloc;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
  return size_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }

  iterator new_data = alloc_traits::allocate(alloc_, new_capacity);

  copy_from_data(new_data);

  destroy_data();

  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
  return capacity_;
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_data = alloc_traits::allocate(alloc_, size_);

    copy_from_data(new_data);
    destroy_data();

    data_ = new_data;
    capacity_ = size_;
  }
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator out of range");
  }

  size_t iter_pos = pos - begin();
  if (size_ == capacity_) {
    reserve((capacity_ > 0 ? capacity_ * 2 : 1));
  }

  try {
    alloc_traits::construct(alloc_, data_ + size_, value_type(value_type()));
  } catch (...) {
    for (size_type j = 0; j < size_; ++j) {
      alloc_traits::destroy(alloc_, data_ + j);
    }
    alloc_traits::deallocate(alloc_, data_, size_);
    throw;
  }

  for (size_type i = size_; i > iter_pos; --i) {
    data_[i] = std::move(data_[i - 1]);
  }

  data_[iter_pos] = value;
  ++size_;

  return begin() + iter_pos;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, T &&value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator out of range");
  }
  size_t iter_pos = pos - begin();
  if (size_ == capacity_) {
    reserve((capacity_ > 0 ? capacity_ * 2 : 1));
  }

  try {
    alloc_traits::construct(alloc_, data_ + size_, value_type(value_type()));
  } catch (...) {
    for (size_type j = 0; j < size_; ++j) {
      alloc_traits::destroy(alloc_, data_ + j);
    }
    alloc_traits::deallocate(alloc_, data_, size_);
    throw;
  }

  for (size_type i = size_; i > iter_pos; --i) {
    data_[i] = std::move(data_[i - 1]);
  }

  data_[iter_pos] = std::move(value);
  ++size_;

  return begin() + iter_pos;
}

template <typename T, typename Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, size_type count, const T &value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator out of range");
  }
  size_t iter_pos = pos - begin();
  if (size_ + count >= capacity_) {
    reserve(size_ + count);
  }

  init_value_type_for_insert(size_ + count);

  for (size_type i = size_ + count - 1; i >= iter_pos + count; --i) {
    data_[i] = std::move(data_[i - count]);
  }

  for (size_type i = iter_pos; i < iter_pos + count; ++i) {
    data_[i] = value;
  }

  size_ += count;

  return begin() + iter_pos;
}

template <typename T, typename Alloc>
template <typename... Args>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert_many(
    const_iterator pos, Args &&...args) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator out of range");
  }

  size_t iter_pos = pos - begin();
  size_type count = (sizeof...(Args));
  if (size_ + count >= capacity_) {
    reserve(size_ + count);
  }

  init_value_type_for_insert(size_ + count);

  for (size_type i = size_ + count - 1; i >= iter_pos + count; --i) {
    data_[i] = std::move(data_[i - count]);
  }

  size_type i = iter_pos;
  ((data_[i++] = std::move(args)), ...);
  size_ += sizeof...(Args);

  return begin() + iter_pos;
}

template <typename T, typename Alloc>
template <typename... Args>
inline void vector<T, Alloc>::insert_many_back(Args &&...args) {
  size_type count = (sizeof...(Args));
  if (size_ + count >= capacity_) {
    reserve(size_ + count);
  }

  init_value_type_for_insert(size_ + count);

  size_type i = size_;
  ((data_[i++] = std::move(args)), ...);
  size_ += sizeof...(Args);
}

// ADDITIONAL FUNCTIONS

template <typename T, typename Alloc>
inline void vector<T, Alloc>::destroy_data() {
  for (size_type i = 0; i < size_; ++i) {
    alloc_traits::destroy(alloc_, data_ + i);
  }

  alloc_traits::deallocate(alloc_, data_, capacity_);
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::init_value_type_for_insert(size_type length) {
  for (size_type i = size_; i < length; ++i) {
    try {
      alloc_traits::construct(alloc_, data_ + i, value_type(value_type()));
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        alloc_traits::destroy(alloc_, data_ + j);
      }
      alloc_traits::deallocate(alloc_, data_, size_);
      throw;
    }
  }
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::add_value_in_back(iterator cur_data,
                                                const_reference value) {
  try {
    alloc_traits::construct(alloc_, cur_data + size_, value_type(value));
  } catch (...) {
    for (size_type j = 0; j < size_; ++j) {
      alloc_traits::destroy(alloc_, cur_data + j);
    }
    alloc_traits::deallocate(alloc_, cur_data, size_);
    throw;
  }
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::copy_in_data(const iterator other_data) {
  data_ = alloc_traits::allocate(alloc_, capacity_);

  for (size_type i = 0; i < size_; ++i) {
    try {
      alloc_traits::construct(alloc_, data_ + i, value_type(other_data[i]));
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        alloc_traits::destroy(alloc_, data_ + j);
      }
      alloc_traits::deallocate(alloc_, data_, size_);
      throw;
    }
  }
}

template <typename T, typename Alloc>
inline void vector<T, Alloc>::copy_from_data(iterator new_data) {
  for (size_type i = 0; i < size_; ++i) {
    try {
      alloc_traits::construct(alloc_, new_data + i,
                              std::move(value_type(data_[i])));
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        alloc_traits::destroy(alloc_, new_data + j);
      }
      alloc_traits::deallocate(alloc_, new_data, size_);
      throw;
    }
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_VECTOR_H