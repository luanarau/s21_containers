
#ifndef S21_CONTAINERS_BSTREE_H
#define S21_CONTAINERS_BSTREE_H

#include "s21_vector.h"

namespace s21 {
template <typename Tk, typename Td>
class Tree {
 public:
  class Iterator;

 protected:
  class Node {
   public:
    Tk key;
    Td data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    bool isRed;
    Node(Tk key = Tk(), Td data = Td()) : key(key), data(data), isRed(true) {}
    Node(Tk key, Td data, Node *parent)
        : key(key), data(data), parent(parent), isRed(true) {}
  };
  Node *root;
  int size;

  void remove_no(Node *&parent, Node *&temp);
  void remove_l(Node *&parent, Node *&temp);
  void remove_r(Node *&parent, Node *&temp);
  void remove_all(Node *&parent, Node *&temp);

 public:
  using key_type = Tk;
  using mapped_type = Td;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  Tree();
  Tree(const Tree &other);
  Tree(Tree &&other) noexcept;
  ~Tree();

  Node *CopyTree(Node *node, Node *parent);

  void insert(Tk keyn, Td data);
  void replace(Tk keyn, Td data);
  bool remove(Tk key);
  bool finder(Tk key);
  Node *search(Tk key);
  Iterator find(Tk key);
  void find(Node *&temp, Node *&parent, Tk keyn);
  Iterator findIter(Tk keyn);

  void swap(Tree &other);

  void clear();

  class Iterator {
   private:
    Tree *tree;
    Node *cur;

   public:
    Iterator() noexcept : tree(nullptr) {}
    Iterator(Tree *tree, Node *cur) : tree(tree), cur(cur) {}
    Iterator(const Iterator &other) : tree(other.tree), cur(other.cur) {}
    Iterator &operator=(const Iterator &other) {
      tree = other.tree;
      cur = other.cur;
      return *this;
    }
    explicit Iterator(Tree<Tk, Td> *tree) noexcept : tree(tree) {}
    ~Iterator() = default;

    virtual value_type operator*();
    Iterator operator--();
    Iterator operator++();
    bool operator==(const Iterator &a);
    bool operator!=(const Iterator &a);
  };
  Iterator begin();
  Iterator end();

  class ConstIterator : Iterator {
   public:
    ConstIterator() noexcept : Iterator() {}
    explicit ConstIterator(Tree<Tk, Td> *tree) noexcept : Iterator(tree) {}
    ~ConstIterator() = default;
    const_reference operator*() const { return Iterator::operator*(); };
  };

  Node *max(Node *cur);
  Node *min(Node *cur);
  Node *predecessor(Node *cur);
  Node *successor(Node *cur);
  Node *pred_add(Node *cur);
  Node *pred_sub(Node *cur);

  bool isempty();
  void set_size(int size) { this->size = size; }
  int sizeofTree() const;

  class Readwrite {};
};

template <typename Tk, typename Td>
Tree<Tk, Td>::Tree() {
  size = 0;
  root = nullptr;
}

template <typename Tk, typename Td>
Tree<Tk, Td>::Tree(const Tree &other) {
  root = CopyTree(other.root, nullptr);
  set_size(other.sizeofTree());
}

template <typename Tk, typename Td>
Tree<Tk, Td>::Tree(Tree &&other) noexcept {
  root = other.root;
  set_size(other.sizeofTree());
  other.set_size(0);
  other.root = nullptr;
}

template <typename Tk, typename Td>
Tree<Tk, Td>::~Tree() {
  clear();
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::CopyTree(Tree::Node *node,
                                                    Tree::Node *parent) {
  if (node == nullptr) return nullptr;
  Node *new_node = new Node(node->key, node->data, parent);
  new_node->left = CopyTree(node->left, new_node);
  new_node->right = CopyTree(node->right, new_node);
  return new_node;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::insert(Tk keyn, Td data) {
  Node *cur = root;
  while (cur) {
    if (keyn < cur->key && cur->left == nullptr) {
      Node *newNode = new Node(keyn, data);
      cur->left = newNode;
      newNode->parent = cur;
      size++;
      return;
    } else if ((keyn > cur->key || keyn == cur->key) && cur->right == nullptr) {
      Node *newNode = new Node(keyn, data);
      cur->right = newNode;
      newNode->parent = cur;
      size++;
      return;
    } else if (keyn > cur->key || keyn == cur->key)
      cur = cur->right;
    else if (keyn < cur->key)
      cur = cur->left;
  }
  size++;
  root = new Node(keyn, data);
  return;
}

template <typename Tk, typename Td>
inline void Tree<Tk, Td>::replace(Tk keyn, Td data) {
  Node *cur = root;
  while (cur && cur->key != keyn) {
    if (keyn > cur->key)
      cur = cur->right;
    else if (keyn < cur->key)
      cur = cur->left;
  }
  cur->key = keyn;
  cur->data = data;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::find(Node *&temp, Node *&parent, Tk keyn) {
  while (temp != nullptr) {
    if (keyn == (temp)->key) {
      break;
    }
    parent = temp;
    if (keyn < (temp)->key) {
      temp = (temp)->left;
    } else if (keyn > (temp)->key) {
      temp = (temp)->right;
    }
  }
}

template <typename Tk, typename Td>
inline typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::findIter(Tk keyn) {
  typename Tree<Tk, Td>::Iterator it = Tree<Tk, Td>::begin();
  while (keyn != (*it).first) {
    if (keyn < (*it).first) {
      --it;
    } else if (keyn > (*it).first) {
      ++it;
    } else
      break;
  }
  return it;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::remove_no(Node *&parent, Node *&temp) {
  if (parent->left == temp) {
    parent->left = nullptr;
  } else if (parent->right == temp)
    parent->right = nullptr;
  delete temp;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::remove_l(Node *&parent, Node *&temp) {
  if (parent->left == temp) {
    parent->left = temp->left;
    temp->left->parent = parent;
  } else if (parent->right == temp) {
    parent->right = temp->left;
    temp->left->parent = parent;
  }
  delete temp;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::remove_r(Node *&parent, Node *&temp) {
  if (parent->left == temp) {
    parent->left = temp->right;
    temp->right->parent = parent;
  } else if (parent->right == temp) {
    parent->right = temp->right;
    temp->right->parent = parent;
  }
  delete temp;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::remove_all(Node *&parent, Node *&temp) {
  Node *new_root = temp;
  parent = temp;
  temp = temp->right;
  while (temp->left != nullptr) {
    parent = temp;
    temp = temp->left;
  }
  new_root->key = temp->key;
  new_root->data = temp->data;
  if (temp->right == nullptr) {
    if (parent->left == temp) {
      parent->left = nullptr;
    } else if (parent->right == temp) {
      parent->right = temp->right;
    }
  } else {
    if (parent->left == temp) {
      parent->left = temp->right;
    } else if (parent->right == temp) {
      parent->right = temp->right;
    }
  }
  delete temp;
}

template <typename Tk, typename Td>
bool Tree<Tk, Td>::remove(Tk key) {
  Node *temp = root, *parent = root;
  bool flag = false;
  find(temp, parent, key);
  if (temp != nullptr) {
    flag = true;
    if (temp->left == nullptr && temp->right == nullptr) {
      if (temp == root) {
        delete root;
        root = nullptr;
      } else
        remove_no(temp->parent, temp);
    } else if (temp->left != nullptr && temp->right != nullptr) {
      remove_all(temp->parent, temp);
    } else if (temp->left != nullptr) {
      if (temp == root) {
        root = temp->left;
        delete temp;
      } else
        remove_l(temp->parent, temp);
    } else if (temp->right != nullptr) {
      if (temp == root) {
        root = temp->right;
        delete temp;
      } else
        remove_r(temp->parent, temp);
    }
  }
  return flag;
}

template <typename Tk, typename Td>
inline bool Tree<Tk, Td>::finder(Tk key) {
  Node *node = Tree<Tk, Td>::root, *parent = nullptr;
  find(node, parent, key);
  if (node) return true;
  return false;
}

template <typename Tk, typename Td>
inline typename Tree<Tk, Td>::Node *Tree<Tk, Td>::search(Tk key) {
  Node *temp = root, *find = nullptr;
  while (temp != nullptr) {
    if (key == temp->key) {
      find = temp;
      break;
    }
    if (key < temp->key) {
      temp = temp->left;
    } else if (key > temp->key) {
      temp = temp->right;
    }
  }
  return find;
}

template <typename Tk, typename Td>
inline typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::find(Tk key) {
  typename Tree<Tk, Td>::Iterator it = Tree<Tk, Td>::begin();
  for (; it != end(); ++it)
    if ((*it).first == key) return it;
  return end();
}

template <typename Tk, typename Td>
inline void Tree<Tk, Td>::swap(Tree &other) {
  std::swap(root, other.root);
  int temp = sizeofTree();
  set_size(other.sizeofTree());
  other.set_size(temp);
}

template <typename Tk, typename Td>
inline void Tree<Tk, Td>::clear() {
  while (root != nullptr) remove(root->key);
  set_size(0);
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::begin() {
  if (root == nullptr) return end();
  Node *cur = root;
  while (cur->left != nullptr) {
    cur = cur->left;
  }
  Iterator it(this, cur);
  return it;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::end() {
  return Iterator(this, nullptr);
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::max(Node *cur) {
  if (cur == nullptr) return nullptr;
  while (cur->right != nullptr) {
    cur = cur->right;
  }
  return cur;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::pred_add(Node *cur) {
  Node *predecessor = cur->parent;
  while (predecessor != nullptr && cur == predecessor->right) {
    cur = predecessor;
    predecessor = predecessor->parent;
  }
  return predecessor;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::pred_sub(Node *cur) {
  Node *predecessor = cur->parent;
  while (predecessor != nullptr && cur == predecessor->left) {
    cur = predecessor;
    predecessor = predecessor->parent;
  }
  return predecessor;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::predecessor(Node *cur) {
  if (cur == nullptr) return cur;
  if (cur->left != nullptr) {
    return max(cur->left);
  } else
    return pred_sub(cur);
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::min(Node *cur) {
  if (cur == nullptr) return nullptr;
  while (cur->left != nullptr) cur = cur->left;
  return cur;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Node *Tree<Tk, Td>::successor(Node *cur) {
  if (cur == nullptr) return cur;
  if (cur->right != nullptr)
    return min(cur->right);
  else
    return pred_add(cur);
}

template <typename Tk, typename Td>
inline int Tree<Tk, Td>::sizeofTree() const {
  return (const int)this->size;
}

template <typename Tk, typename Td>
inline bool Tree<Tk, Td>::isempty() {
  if (this->root != nullptr) return false;
  return true;
}

template <typename Tk, typename Td>
inline typename Tree<Tk, Td>::value_type Tree<Tk, Td>::Iterator::operator*() {
  std::pair<const key_type, mapped_type> ret =
      std::make_pair(cur->key, cur->data);
  return ret;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::Iterator::operator--() {
  cur = tree->predecessor(cur);
  return *this;
}

template <typename Tk, typename Td>
typename Tree<Tk, Td>::Iterator Tree<Tk, Td>::Iterator::operator++() {
  cur = tree->successor(cur);
  return *this;
}

template <typename Tk, typename Td>
inline bool Tree<Tk, Td>::Iterator::operator==(const Iterator &a) {
  if (this->tree == a.tree && this->cur == a.cur)
    return true;
  else
    return false;
}

template <typename Tk, typename Td>
inline bool Tree<Tk, Td>::Iterator::operator!=(const Iterator &a) {
  return !(*this == a);
}

}  // namespace s21

#endif  // S21_CONTAINERS_BSTREE_H
