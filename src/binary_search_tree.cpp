#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
      clear(root_);
      root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    return Find(key) != std::nullopt;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    return find_min(root_)->key;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    return find_max(root_)->key;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      Node *newNode = new Node(key, value);
      node = newNode;
      (*node).key = key;
    }
    if (key == node->key) {
      (*node).value = value;
    } else if (key < node->key) {
      insert(key, value, node->left);
    } else if (key > node->key) {
      insert(key, value, node->right);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (!Contains(key)) {
      return false;
    }
    if (key == node->key) {
      if (node->right != nullptr && node->left != nullptr) {
        Node *minNode = find_min(node->right);
        node->key = minNode->key;
        node->value = minNode->value;
        return remove(minNode->key, node->right);
      }
      if (node->right != nullptr) {
        Node *rightNode = node->right;
        delete node;
        node = rightNode;
        return true;
      }
      Node *leftNode = node->left;
      delete node;
      node = leftNode;
      return true;
    }
    if (key < node->key) {
      return remove(key, node->left);
    }
    return remove(key, node->right);
  }

  void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (key < node->key) {
      return find(key, node->left);
    }
    if (key > node->key) {
      return find(key, node->right);
    }
    return node;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    Node *minNode = node;
    while (node != nullptr) {
      minNode = node;
      node = node->left;
    }
    return minNode;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    Node *maxNode = node;
    while (node != nullptr) {
      maxNode = node;
      node = node->right;
    }
    return maxNode;
  }

}  // namespace assignment
