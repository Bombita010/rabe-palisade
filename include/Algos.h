#ifndef ALGOS_H
#define ALGOS_H

#include <vector>

#include "node.h"
#include "BTtree.h"
#include "palisade.h"

class Algos
{
private:
    /* data */
public:
    Algos(/* args */);
    ~Algos();

    /*
    *@description:  KUNodes算法               
    *@
    *@param: BT树                      
    *@param: 非空的撤销列表 
    *@param: 时间t：是环元素R^q                     
    *@
    *@return:                      
    *@return:                      
    */
    std::vector<Node *> kUNodes(const BTtree &BTtree, const std::vector<int> &revList, int t);
};

Algos::Algos(/* args */)
{
}

Algos::~Algos()
{
}






#endif //ALGOS_H