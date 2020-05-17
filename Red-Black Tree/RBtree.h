#ifndef RBTREE_H
#define RBTREE_H


#include <cstdlib>

template<typename T>
class RBtree {
    class Node {
    public:
        Node(const std::size_t key, const T value) : key(key), value(value) {};

        const std::size_t key;
        T value;
        Node *left = nullptr, *right = nullptr;
    };

public:
    RBtree();
    RBtree(const RBtree &copyRBtree);
    RBtree(RBtree &&copyRBtree) noexcept;

    RBtree &operator=(const RBtree &otherRBtree);
    RBtree &operator=(RBtree &&otherRBtree) noexcept;

    ~RBtree();

    void add(std::size_t key, T value);

    void deleteFirstNodeByKey(std::size_t key);
    void deleteAllNodesByKey(std::size_t key);

    Node &find(std::size_t key);
    Node &findNodeWithMaxKey();
    Node &findNodeWithMinKey();

    [[nodiscard]] std::size_t size() const;

    Node *node();
    const Node *node() const;

    bool isEmpty();

private:
    std::size_t _size;
    Node *_node;
};

template<typename T>
RBtree<T>::RBtree() : _size(0), _node(nullptr) {}

template<typename T>
RBtree<T>::RBtree(const RBtree &copyRBtree) :
        _node(copyRBtree._node),
        _size(copyRBtree._size) {}

template<typename T>
RBtree<T>::RBtree(RBtree &&copyRBtree) noexcept : RBtree(copyRBtree) {
    if (_node != nullptr) {
        copyRBtree._node->left = nullptr;
        copyRBtree._node->right = nullptr;
    }
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(const RBtree &otherRBtree) {
    if (this == &otherRBtree) {
        return *this;
    }

    _node = otherRBtree._node;
    _size = otherRBtree._size;

    return *this;
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(RBtree &&otherRBtree) noexcept {
    if (this == &otherRBtree) {
        return *this;
    }

    _node = otherRBtree._node;
    _size = otherRBtree._size;

    otherRBtree._node = nullptr;

    return *this;
}

template<typename T>
RBtree<T>::~RBtree() {
    delete _node;
    _node = nullptr;
};

template<typename T>
typename RBtree<T>::Node &RBtree<T>::find(std::size_t key) {
    if (_node == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }
    else if (_node->key == key) {
        return *_node;
    }
    else if (_node->key < key) {
        find(_node->left->key);
    }
    else if (_node->key < key) {
        find(_node->right->key);
    }
    else throw std::invalid_argument("Key not found");
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMaxKey() {
    if (_node == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = _node->left;
    while (bufNode->left != nullptr) {
        bufNode = bufNode->left;
    }
    return bufNode;
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMinKey() {
    if (_node == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = _node->right;
    while (bufNode->right != nullptr) {
        bufNode = bufNode->right;
    }
    return bufNode;
}

template<typename T>
void RBtree<T>::add(const std::size_t key, const T value) {
    if (_size == 0) {
        _node = new Node(key, value);
    } else {
        Node *bufNode(_node);
        while (true) {
            if (key < bufNode->key) {
                if (bufNode->left == nullptr) {
                    bufNode->left = new Node(key, value);
                    break;
                } else {
                    bufNode = bufNode->left;
                }
            } else {
                if (bufNode->right == nullptr) {
                    bufNode->right = new Node(key, value); // TODO: проверка на утечку памяти
                    break;
                } else {
                    bufNode = bufNode->right;
                }
            }
        }
        _node = bufNode;
    }
    _size++;
}

template<typename T>
void RBtree<T>::deleteFirstNodeByKey(const std::size_t key) {
    Node *bufNode = find(key);
    delete bufNode;
    // TODO: проверка корректности
}

template<typename T>
void RBtree<T>::deleteAllNodesByKey(const std::size_t key) {
    try {
        Node *bufNode;
        while (true) {
            bufNode = find(key);
            delete bufNode;
        }
    }
    catch (...) {
        // TODO: добавить exception и обдумать конструкцию
    }
}

template<typename T>
std::size_t RBtree<T>::size() const {
    return _size;
}

template<typename T>
typename RBtree<T>::Node *RBtree<T>::node() {
    return _node;
}

template<typename T>
const typename RBtree<T>::Node *RBtree<T>::node() const {
    return _node;
}

template<typename T>
bool RBtree<T>::isEmpty() {
    return !_size;
}


#endif //RBTREE_H
