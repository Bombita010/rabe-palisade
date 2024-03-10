#include "Algos.h"

Algos::Algos(/* args */)
{
}

/*
*@description:  KUNodes算法               
*@
*@param: BT树                      
*@param: 非空的撤销列表                   
*@
*@return: 撤销列表的最小覆盖集                                        
*/
std::vector<int> Algos::kUNodes(BTtree &BTtree, const std::vector<Node*> revList)
{
    std::vector<int> minCover;
    std::vector<Node *> revoke;

    for(auto node : revList)
    {
        std::vector<Node *> tmpList(BTtree.getPathNode(node));
        for(auto i : tmpList)
        {
            //如果不在撤销列表中，则加入撤销列表？？？
            if( std::find(revoke.begin(), revoke.end(), i) == revoke.end() )
            {
                revoke.push_back(i);
            }
        }
    }

    for(auto node : revoke)
    {
        if(node->isleaf)
        {
            std::cout << "isleaf" << std::endl;
            continue;
        }
        if( std::find(revoke.begin(), revoke.end(), node->lchild) == revoke.end() )
        {
            std::cout << "node->lchild->id" << node->lchild->id << std::endl;
            minCover.push_back(node->lchild->id);
        }
        if( std::find(revoke.begin(), revoke.end(), node->rchild) == revoke.end() )
        {
            std::cout << "node->rchild->id" << node->rchild->id << std::endl;
            minCover.push_back(node->rchild->id);
        }
    }
    //RL非空，如果为空则加入根节点，根节点id为1
    if(revoke.size() == 0)
    {
        minCover.push_back(1);
    }

    return minCover;
}


/*
*@description:  KUNodes算法               
*@
*@param: BT树                      
*@param: 非空的撤销列表 
*@param: 时间t：是环元素R^q                     
*@
*@return: 撤销列表的最小覆盖集                                         
*/
std::vector<int> Algos::kUNodes(BTtree &BTtree, const std::vector<RLuser> revList, time_t t)
{
    std::vector<int> minCover;
    std::vector<Node *> revoke;

    for(auto revlist : revList)
    {
        if(revlist.t < t)
        {
            std::vector<Node *> tmpList(BTtree.getPathNode(revlist.user));
            for(auto i : tmpList)
            {
                //如果不在撤销列表中，则加入撤销列表？？？
                if( std::find(revoke.begin(), revoke.end(), i) == revoke.end() )
                {
                    revoke.push_back(i);
                }
            }
        }
    }

    for(auto node : revoke)
    {
        if(node->isleaf)
        {
            std::cout << "isleaf" << std::endl;
            continue;
        }
        if( std::find(revoke.begin(), revoke.end(), node->lchild) == revoke.end() )
        {
            std::cout << "node->lchild->id" << node->lchild->id << std::endl;
            minCover.push_back(node->lchild->id);
        }
        if( std::find(revoke.begin(), revoke.end(), node->rchild) == revoke.end() )
        {
            std::cout << "node->rchild->id" << node->rchild->id << std::endl;
            minCover.push_back(node->rchild->id);
        }
    }
    //RL非空，如果为空则加入根节点，根节点id为1
    if(revoke.size() == 0)
    {
        minCover.push_back(1);
    }

    return minCover;

}


Algos::~Algos()
{
}