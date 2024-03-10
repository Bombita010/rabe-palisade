/*  @file Algos.h - 提供一些系统功能所需算法  */ 

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
    *@
    *@return: 撤销列表的最小覆盖集                                        
    */
    std::vector<int> kUNodes(BTtree &BTtree, const std::vector<Node*> revList);

    /*
    *@description:  KUNodes算法               
    *@
    *@param: BT树                      
    *@param: 非空的撤销列表 
    *@param: 时间t：是环元素R^q                     
    *@
    *@return: 撤销列表的最小覆盖集                                         
    */
    std::vector<int> kUNodes(BTtree &BTtree, const std::vector<RLuser> revList, time_t t);
};








#endif //ALGOS_H