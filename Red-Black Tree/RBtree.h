#ifndef RBTREE_H
#define RBTREE_H


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
    Node* _find(std::size_t key, Node* ptr);

    std::size_t _size;
    Node *_root;
};

template<typename T>
RBtree<T>::RBtree() : _size(0), _root(nullptr) {}

template<typename T>
RBtree<T>::RBtree(const RBtree &copyRBtree) :
        _root(new Node(copyRBtree._root)),
        _size(copyRBtree._size) {}

template<typename T>
RBtree<T>::RBtree(RBtree &&copyRBtree) noexcept {
    _root = copyRBtree._root;
    _size = copyRBtree._size;

    copyRBtree._root = nullptr;
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(const RBtree &otherRBtree) {
    if (this == &otherRBtree) {
        return *this;
    }

    _root = new Node(otherRBtree._root);
    _size = otherRBtree._size;

    return *this;
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(RBtree &&otherRBtree) noexcept {
    if (this == &otherRBtree) {
        return *this;
    }

    _root = otherRBtree._root;
    _size = otherRBtree._size;

    otherRBtree._root = nullptr;

    return *this;
}

template<typename T>
RBtree<T>::~RBtree() {
    delete _root;
    _root = nullptr;
};

template<typename T>
typename RBtree<T>::Node &RBtree<T>::find(std::size_t key) {
    if (_root == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    } else {
        return *_find(key, _root);
    }
}

template<typename T>
typename RBtree<T>::Node *RBtree<T>::_find(std::size_t key, Node *ptr) {
    if (ptr == nullptr) {
        throw std::invalid_argument("Key not found");
    } else if (ptr->key == key) {
        return ptr;
    } else if (ptr->key > key) {
        return _find(key, ptr->left);
    } else {
        return _find(key, ptr->right);
    }
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMaxKey() {
    if (_root == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = _root;
    while (bufNode->right != nullptr) {
        bufNode = bufNode->right;
    }

    return *bufNode;
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMinKey() {
    if (_root == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = _root;
    while (bufNode->left != nullptr) {
        bufNode = bufNode->left;
    }
    return *bufNode;
}

template<typename T>
void RBtree<T>::add(const std::size_t key, const T value) {
    if (_size == 0) {
        _root = new Node(key, value);
    } else {
        Node* bufNode = _root;
        while(true) {
            if (key < bufNode->key) {
                if (bufNode->left == nullptr) {
                    bufNode->left = new Node(key, value);
                    break;
                } else {
                    bufNode = bufNode->left;
                    continue;
                }
            } else {
                if (bufNode->right == nullptr) {
                    bufNode->right = new Node(key, value);
                    break;
                } else {
                    bufNode = bufNode->right;
                    continue;
                }
            }
        }
    }
    _size++;
}

template<typename T>
void RBtree<T>::deleteFirstNodeByKey(const std::size_t key) {
    Node *bufNode = find(key);
    //delete bufNode;
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
    return _root;
}

template<typename T>
const typename RBtree<T>::Node *RBtree<T>::node() const {
    return _root;
}

template<typename T>
bool RBtree<T>::isEmpty() {
    return !_size;
}


#endif //RBTREE_H
