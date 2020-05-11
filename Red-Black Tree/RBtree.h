#ifndef RBTREE_H
#define RBTREE_H


#include <cstdlib>

template<typename  T>
class RBtree {
    class Node
    {
    public:
        Node(const std::size_t key, const T value) : key_(key), value_(value) {};

        const std::size_t key_;
        T value_;
        Node *left_ = nullptr, *right_ = nullptr;
    };

public:
    RBtree() : _size(0) {};
    RBtree(const RBtree& copyRBtree);
    RBtree(RBtree&& copyRBtree) noexcept;

    RBtree& operator=(const RBtree& otherRBtree);
    RBtree& operator=(RBtree&& otherRBtree) noexcept;

    ~RBtree();

    void addNode(std::size_t key, T value);

    void deleteFirstNodeByKey(std::size_t key);
    void deleteAllNodesByKey(std::size_t key);

    Node& find(std::size_t key);
    Node& findNodeWithMaxKey();
    Node& findNodeWithMinKey();

    [[nodiscard]] std::size_t key() const { return Node::key_; };
    T value() const { return Node::value_; };
    Node* left() const { return Node::left_; };
    Node* right() const { return Node::right_; };

    [[nodiscard]] std::size_t  size() const;
    bool isEmpty();

private:
    std::size_t  _size = 0;
};

template<typename  T>
RBtree<T>::RBtree(const RBtree &copyRBtree)
    : Node::key_(copyRBtree.key()), Node::value_(copyRBtree.value()),
      Node::right_(copyRBtree.right()), Node::left_(copyRBtree.left()),
      _size(copyRBtree._size) {}

template<typename  T>
RBtree<T>::RBtree(RBtree &&copyRBtree) noexcept : RBtree(copyRBtree) {
    copyRBtree.left() = nullptr;
    copyRBtree.right() = nullptr;
}

template<typename  T>
RBtree<T> &RBtree<T>::operator=(const RBtree &otherRBtree) {
    return;
}

template<typename  T>
RBtree<T> &RBtree<T>::operator=(RBtree &&otherRBtree) noexcept {
    return;
}

template<typename  T>
RBtree<T>::~RBtree() {
    left() = nullptr;
    right() = nullptr;
}

template<typename  T>
void RBtree<T>::addNode(const std::size_t key, const T value) {

}

template<typename  T>
void RBtree<T>::deleteFirstNodeByKey(const std::size_t key) {

}

template<typename  T>
void RBtree<T>::deleteAllNodesByKey(const std::size_t key) {

}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::find(std::size_t key) {

}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMaxKey() {
    return ;
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMinKey() {
    return ;
}

template<typename  T>
std::size_t RBtree<T>::size() const {
    return 0;
}

template<typename  T>
bool RBtree<T>::isEmpty() {
    return false;
}


#endif //RBTREE_H
