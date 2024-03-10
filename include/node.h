/*  @file node.h - 节点Node类  */ 

#ifndef NODE_H
#define NODE_H

#include <ctime>

class Node {
private:

public:
    int id; // 节点的唯一标识符
    Node* parent; // 指向父节点的指针
    Node* lchild; // 指向左子节点的指针
    Node* rchild; // 指向右子节点的指针
    bool isleaf; // 节点是否为叶子节点
    int u; // 用户相关字段，如果是叶子节点，则会存储用户userList里的相关信息

    // 构造函数声明
    Node();
    Node(int id, Node* parent, Node* lchild, Node* rchild, bool isleaf, int u);

    ~Node();

    // 成员函数声明
    int getId() const;
    Node* getParent() const;
    Node* getLchild() const;
    Node* getRchild() const;
};


#endif // NODE_H
