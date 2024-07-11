#ifndef S21_CONTAINERS_RBTREE_H
#define S21_CONTAINERS_RBTREE_H
#include "BSTree.h"

namespace s21 {
template <typename K, typename D>
class RBTree : public s21::Tree<K, D> {
 public:
  using key_type = K;
  using mapped_type = D;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  RBTree() : Tree<K, D>(){};
  RBTree(const std::initializer_list<value_type> &items);
  RBTree(const RBTree &m) : Tree<K, D>(m){};
  RBTree(RBTree &&m) noexcept : Tree<K, D>(std::move(m)){};
  ~RBTree() = default;

  void insert(K k, D d);
  void fixInsert(K key);
  void remove(K key);

  class Readwrite {};

 private:
  typename Tree<K, D>::Node *rotateLeft(typename Tree<K, D>::Node *node);
  typename Tree<K, D>::Node *rotateRight(typename Tree<K, D>::Node *node);

  typename Tree<K, D>::Node *remove(typename Tree<K, D>::Node *node, int key);
};

template <typename K, typename D>
RBTree<K, D>::RBTree(const std::initializer_list<value_type> &items) {
  Tree<K, D>::size = 0;
  Tree<K, D>::root = nullptr;
  for (value_type i : items) insert(i.first, i.second);
}

template <typename K, typename D>
inline typename Tree<K, D>::Node *RBTree<K, D>::rotateLeft(
    typename Tree<K, D>::Node *node) {
  typename Tree<K, D>::Node *right = node->right;
  if (right == nullptr) return node;
  node->right = right->left;
  if (right->left != nullptr) {
    right->left->parent = node;
  }
  right->parent = node->parent;
  if (node->parent == nullptr) {
    Tree<K, D>::root = right;
  } else if (node == node->parent->left) {
    node->parent->left = right;
  } else {
    node->parent->right = right;
  }
  right->left = node;
  node->parent = right;
  right->isRed = node->isRed;
  node->isRed = true;
  return right;
}

template <typename K, typename D>
inline typename Tree<K, D>::Node *RBTree<K, D>::rotateRight(
    typename Tree<K, D>::Node *node) {
  typename Tree<K, D>::Node *left = node->left;
  if (left == nullptr) return node;
  node->left = left->right;
  if (left->right != nullptr) {
    left->right->parent = node;
  }
  left->parent = node->parent;
  if (node->parent == nullptr) {
    Tree<K, D>::root = left;
  } else if (node == node->parent->left) {
    node->parent->left = left;
  } else {
    node->parent->right = left;
  }
  left->right = node;
  node->parent = left;
  left->isRed = node->isRed;
  node->isRed = true;
  return left;
}

template <typename K, typename D>
inline void RBTree<K, D>::insert(K k, D d) {
  Tree<K, D>::insert(k, d);
  fixInsert(k);
}

template <typename K, typename D>
inline void RBTree<K, D>::fixInsert(K key) {
  typename Tree<K, D>::Node *node = Tree<K, D>::root, *parent = nullptr;
  Tree<K, D>::find(node, parent, key);
  while (node->isRed == true && node != Tree<K, D>::root &&
         node->parent->isRed == true) {
    if (node->parent == node->parent->parent->left) {
      typename Tree<K, D>::Node *uncle = nullptr;
      if (node->parent->parent) uncle = node->parent->parent->right;
      if (uncle != nullptr && uncle->isRed == true) {
        node->parent->isRed = false;
        uncle->isRed = false;
        node->parent->parent->isRed = true;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotateLeft(node);
        }
        node->parent->isRed = false;
        if (node->parent->parent != nullptr) node->parent->parent->isRed = true;
        if (node->parent->parent == Tree<K, D>::root) {
          node = rotateRight(node->parent->parent);
          Tree<K, D>::root = node;
        } else if (node->parent != Tree<K, D>::root)
          node = rotateRight(node->parent->parent);
        else
          node = rotateRight(node->parent);
      }
    } else {
      typename Tree<K, D>::Node *uncle = nullptr;
      if (node->parent->parent) uncle = node->parent->parent->left;
      if (uncle != nullptr && uncle->isRed == true) {
        node->parent->isRed = false;
        uncle->isRed = false;
        node->parent->parent->isRed = true;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          node = rotateRight(node);
        }
        node->parent->isRed = false;
        if (node->parent->parent) node->parent->parent->isRed = true;
        if (node->parent->parent == Tree<K, D>::root) {
          node = rotateLeft(node->parent->parent);
          Tree<K, D>::root = node;
        } else if (node->parent != Tree<K, D>::root)
          node = rotateLeft(node->parent->parent);
        else
          node = rotateLeft(node->parent);
      }
    }
  }
  Tree<K, D>::root->isRed = false;
}

template <typename K, typename D>
inline void RBTree<K, D>::remove(K key) {
  typename Tree<K, D>::Node *node = Tree<K, D>::root;
  remove(node, key);
}

template <typename K, typename D>
inline typename Tree<K, D>::Node *RBTree<K, D>::remove(
    typename Tree<K, D>::Node *node, int key) {
  typename Tree<K, D>::Node *parent = nullptr;
  Tree<K, D>::find(node, parent, key);
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left == nullptr || node->right == nullptr) {
    typename Tree<K, D>::Node *child =
        node->left != nullptr ? node->left : node->right;
    if (child != nullptr) {
      child->parent = node->parent;
    }
    if (node->parent == nullptr) {
      Tree<K, D>::root = child;
    } else if (node == node->parent->left) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
    if (child != nullptr && node->isRed == false && child->isRed == true) {
      child->isRed = false;
    }
    delete node;
    Tree<K, D>::set_size(Tree<K, D>::sizeofTree() - 1);
    return child;

  } else {
    typename Tree<K, D>::Node *minRight = node->right;
    while (minRight->left != nullptr) {
      minRight = minRight->left;
    }
    node->key = minRight->key;
    node->data = minRight->data;
    remove(node->right, minRight->key);
  }
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right != nullptr && node->right->isRed && node->left != nullptr &&
      node->left->isRed) {
    node = rotateLeft(node);
  }
  if (node->left != nullptr && node->left->isRed &&
      node->left->left != nullptr && node->left->left->isRed) {
    node = rotateRight(node);
  }
  if (node->left != nullptr && node->right != nullptr && node->left->isRed &&
      node->right->isRed) {
    node->isRed = true;
    node->left->isRed = false;
    node->right->isRed = false;
  }
  return node;
}

}  // namespace s21

#endif  // S21_CONTAINERS_RBTREE_H