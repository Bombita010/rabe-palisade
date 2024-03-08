#ifndef BTTREE_H
#define BTTREE_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>

#include "node.h" 

class BTtree {
public:
    BTtree(Node* root = nullptr);

    /*
    *@description: 创建完全二叉树             
    *@
    *@param:  用户集 userList         
    *@param:                       
    *@
    *@return: 完全二叉树的根节点                     
    *@return: 对应用户集的叶子节点列表                     
    */
    std::pair<Node*, std::vector<int>> createTree(const std::vector<int>& U);
    
    std::map<int, int> createTree2(const std::vector<int>& U);

    std::vector<int> getPath(Node* leaf);
    std::vector<Node*> getPath2(Node* leaf);
    void preOrderTraversal(Node* root);
    std::pair<int, Node*> searchU(Node* root, int u);

private:
    Node* root;
};

#endif // BTTREE_H
