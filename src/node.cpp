// Node.cpp
#include "node.h"

// 构造函数定义
Node::Node(int id, Node* parent, Node* lchild, Node* rchild, bool isleaf) 
    : id(id), parent(parent), lchild(lchild), rchild(rchild), isleaf(isleaf), u(nullptr) {}

// 获取节点ID
int Node::getId() const {
    return id;
}

// 获取父节点
Node* Node::getParent() const {
    return parent;
}

// 获取左子节点
Node* Node::getLchild() const {
    return lchild;
}

// 获取右子节点
Node* Node::getRchild() const {
    return rchild;
}
