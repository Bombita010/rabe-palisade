// Node.cpp
#include "node.h"

// 构造函数定义
Node::Node(int id, Node* parent, Node* lchild, Node* rchild, bool isleaf, int u) 
    : id(id), parent(nullptr), lchild(nullptr), rchild(nullptr), isleaf(false), u(0) {}

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

Node::~Node()
{
    delete parent;
    delete lchild;
    delete rchild;
}
