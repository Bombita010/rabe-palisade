#include "BTtree.h"

BTtree::BTtree(Node* root) : root(root) {}

/*
*@description: 创建完全二叉树             
*@
*@param:  用户集 userList         
*@param:                       
*@
*@return: 完全二叉树的根节点                     
*@return: 对应用户集的叶子节点列表                     
*/
std::pair<Node*, std::vector<int>> BTtree::createTree(const std::vector<int>& userList) {
    // 

    int userNum = userList.size();
    //节点数?
    int nodeNum = 2 * userNum - 1;

    //存储节点的列表
    std::vector<Node*> nodeList;
    //存储用户identity的列表 ？？
    std::vector<int> identityList;
    //初始化所有节点id
    for (int i = 0; ++i; i < nodeNum + 1)
    {
        Node* node = new Node(i,nullptr,nullptr,nullptr,false);
        nodeList.push_back(node);
    }
    //初始化所有节点的child-parent关系 
    for (int i = 1; ++i; i < nodeNum + 1)
    {
        //根节点
        if (i == 1)
        {
            nodeList[i]->lchild = nodeList[2 * i];
            nodeList[i]->rchild = nodeList[2 * i + 1];
        }
        //非根非叶节点
        if (i != 1 && 2 * i + 1 <= nodeNum)
        {
            nodeList[i]->lchild = nodeList[2 * i];
            nodeList[i]->rchild = nodeList[2 * i + 1];
            nodeList[i]->parent = nodeList[(int)(i / 2)];
        }
        //叶节点
        if (i != 1 && 2 * i > nodeNum)
        {
            nodeList[i]->parent = nodeList[(int)(i / 2)];
            nodeList[i]->isleaf = true;
            //第一个叶子节点的u是userList[0]
            nodeList[i]->u = userList[i - userNum];
            //用户identity的列表 ？？什么作用 identityList[userList[0]=1] = i=8?
            identityList[userList[i - userNum]] = i;
        }
    }
    root = nodeList[1];
    //返回 根节点root和用户id列表
    std::pair<Node*, std::vector<int>> bTroot_idList(root, identityList);
    return bTroot_idList;
}

std::map<int, int> BTtree::createTree2(const std::vector<int>& U) {
    // 请参考Python中的createTree2方法来实现相应的逻辑
}

/*
*@description:  叶子节点到根节点的路径                 
*@
*@param: 对应一个用户的叶子节点                       
*@param:                       
*@
*@return: 路径节点id列表                                          
*/
std::vector<int> BTtree::getPath(Node* leaf) {
    //是否叶子节点
    if(leaf == nullptr)
        return {};

    std::vector<int> path;
    Node *tmp = leaf;
    while( tmp->parent != nullptr)
    {
        path.push_back(tmp->id);
        tmp = tmp->parent;
    }
    path.push_back(tmp->id);
    return path;
}

/*
*@description:  叶子节点到根节点的路径                 
*@
*@param: 对应一个用户的叶子节点                       
*@param:                       
*@
*@return: 路径节点列表                                          
*/
std::vector<Node*> BTtree::getPath2(Node* leaf) {
    //是否叶子节点
    if(leaf == nullptr)
        return {};

    std::vector<Node*> path;
    Node *tmp = leaf;
    while( tmp->parent != nullptr)
    {
        path.push_back(tmp);
        tmp = tmp->parent;
    }
    path.push_back(tmp);
    return path;
}
/*
*@description: 先序遍历完全二叉树并打印所有节点id               
*@
*@param:  根节点                                         
*@
*@return:                                          
*/
void BTtree::preOrderTraversal(Node* root) {
    if(root == nullptr)
        return;
    std::cout << root->id << std::endl;
    this->preOrderTraversal(root->lchild);
    this->preOrderTraversal(root->rchild);
}

/*
*@description: 找完全二叉树里一个用户u对应的叶子节点 的节点id和Node               
*@
*@param:  Node* root                     
*@param:  u（userLists里来的）                     
*@
*@return: pair<叶子节点的节点id, Node*>                                          
*/
std::pair<int, Node*> BTtree::searchU(Node* root, int u) {
    std::pair<int, Node*> res =std::make_pair(0,nullptr);
    if(root == nullptr)
        return res;
    if(root->isleaf)
    {
        if(root->u == u)
        {
            int leafId = root->id;
            res = std::make_pair(leafId, root);
            return res;
        }
    }
    if(this->searchU(root->lchild,u).second == nullptr)
        return this->searchU(root->rchild, u);
    else
        return this->searchU(root->lchild, u);
}
