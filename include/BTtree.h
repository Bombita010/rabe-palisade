/*  @file BTtree.h - 完全二叉树BTtree类  */ 
/*  时间t的撤销列表RL元素struct RLuser */ 
#ifndef BTTREE_H
#define BTTREE_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>

#include "node.h" 

/*  含时间t的撤销列表RL元素：（v,t）  */
struct RLuser
{
    Node* user;
    time_t t;
};

class BTtree {
public:
    BTtree(Node* root = nullptr);

    /*
    *@description: 创建完全二叉树             
    *@
    *@param:  用户集 userList                     
    *@
    *@return: 完全二叉树的根节点                     
    *@return: 对应用户集的叶子节点列表                     
    */
    std::pair<Node*, std::vector<int>> createTree(const std::vector<int>& U);
    
    std::map<int, int> createTree2(const std::vector<int>& U);

    /*
    *@description:  叶子节点到根节点的路径                 
    *@
    *@param: 对应一个用户的叶子节点                                          
    *@
    *@return: 路径节点id列表                                          
    */
    std::vector<int> getPathId(Node* leaf);

    /*
    *@description:  叶子节点到根节点的路径                 
    *@
    *@param: 对应一个用户的叶子节点                                           
    *@
    *@return: 路径节点列表                                          
    */
    std::vector<Node*> getPathNode(Node* leaf);

    /*
    *@description: 先序遍历完全二叉树并打印所有节点id               
    *@
    *@param:  根节点                                         
    *@
    *@return:                                          
    */
    void preOrderTraversal(Node* root);

    /*
    *@description: 找完全二叉树里一个用户u对应的叶子节点 的节点id和Node               
    *@
    *@param:  Node* root                     
    *@param:  u（userLists里来的）                     
    *@
    *@return: pair<叶子节点的节点id, Node*>                                          
    */
    std::pair<int, Node*> searchUser(Node* root, int u);

private:
    Node* root;
};

#endif // BTTREE_H
