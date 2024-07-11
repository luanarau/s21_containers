#ifndef S21_CONTAINERSPLUS_S21_ARRAY_H
#define S21_CONTAINERSPLUS_S21_ARRAY_H

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() = default;

  array(std::initializer_list<value_type> const &items) {
    size_type i = 0;

    for (auto it = items.begin(); it != items.end(); ++it) {
      values_[i++] = *it;
    }

    for (; i < N; ++i) {
      values_[i] = value_type();
    }
  }

  array(const array &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      values_[i] = a.values_[i];
    }
  }

  array(array &&a) noexcept {
    for (size_type i = 0; i < N; ++i) {
      values_[i] = std::move(a.values_[i]);
    }
  }

  ~array() = default;

  array &operator=(array &&a) noexcept {
    if (this != &a) {
      for (size_type i = 0; i < a.size(); ++i) {
        values_[i] = std::move(a.values_[i]);
      }
    }

    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }

    return values_[pos];
  }

  reference operator[](size_type pos) { return values_[pos]; }

  const_reference front() { return values_[0]; }

  const_reference back() { return values_[N - 1]; }

  iterator data() { return begin(); }

  iterator begin() { return values_; }

  iterator end() { return values_ + N; }

  bool empty() { return N == 0; }

  size_type size() { return N; }

  size_type max_size() { return N; }

  void swap(array &other) {
    for (size_type i = 0; i < N; ++i) {
      std::swap(values_[i], other.values_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      values_[i] = value;
    }
  }

 private:
  value_type values_[N];
};
}  // namespace s21

#endif  // S21_CONTAINERSPLUS_S21_ARRAY_H