#ifndef RBTREE_H
#define RBTREE_H


#include <cstdlib>

class RBtree {
    template<typename  T>
    struct Node
    {
        Node(const std::size_t key, const T value) : key(key), value(value) {};
        const std::size_t key;
        T value;
        Node *left = nullptr, *right = nullptr;
    };

public:
    RBtree() = default;
    RBtree(const RBtree& copyRBtree);
    RBtree(RBtree&& copyRBtree) noexcept;

    RBtree& operator=(const RBtree& otherRBtree);
    RBtree& operator=(RBtree&& otherRBtree) noexcept;

    ~RBtree();

    template<typename  T>
    void addNode(std::size_t key, T value);

    void deleteFirstNodeByKey(std::size_t key);
    void deleteAllNodesByKey(std::size_t key);

    template<typename  T>
    Node<T>& find(std::size_t key);

    template<typename  T>
    Node<T>& findNodeWithMaxKey();

    template<typename  T>
    Node<T>& findNodeWithMinKey();

    std::size_t  size() const;
    bool isEmpty();

private:
    std::size_t  _size;
};

RBtree::RBtree(const RBtree &copyRBtree) {

}

RBtree::RBtree(RBtree &&copyRBtree) noexcept {

}

RBtree &RBtree::operator=(const RBtree &otherRBtree) {
    return <#initializer#>;
}

RBtree &RBtree::operator=(RBtree &&otherRBtree) noexcept {
    return <#initializer#>;
}

RBtree::~RBtree() {

}

template<typename  T>
void RBtree::addNode(const std::size_t key, const T value) {

}

void RBtree::deleteFirstNodeByKey(const std::size_t key) {

}

void RBtree::deleteAllNodesByKey(const std::size_t key) {

}

template<typename T>
RBtree::Node<T> &RBtree::find(std::size_t key) {

}

template<typename T>
RBtree::Node<T> &RBtree::findNodeWithMaxKey() {
    return <#initializer#>;
}

template<typename T>
RBtree::Node<T> &RBtree::findNodeWithMinKey() {
    return <#initializer#>;
}

std::size_t RBtree::size() const {
    return 0;
}

bool RBtree::isEmpty() {
    return false;
}


#endif //RBTREE_H
