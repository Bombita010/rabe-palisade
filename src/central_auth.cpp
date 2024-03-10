#include "central_auth.h"
#include "myconfig.h"

#include "abecontext.h"

CentralAuth::CentralAuth()
{
    
}

/*
*@CA初始化算法
*@
*@param:                       Param Description
*@param:                       Param Description
*@
*@return:                                         
*@return:                                         
*/
void CentralAuth::CASetup(usint numOfAttr, usint ringSize, usint base)
{
    TimeVar t_CASetup;
    TIC(t_CASetup);
    rabe.GenerateCPABEContext(numAttributes, ringSize, base);
    
    double duration = TOC(t_CASetup);
    std::cout << "CASetup by ring&base: " << ringSize << " &" << base << std::endl 
    <<"时间： " << duration << "ms" 
    << std::endl
    << std::endl;
}

void CentralAuth::CASetup(SecurityLevel lambda, usint numOfAttr, int numOfAA)
{
    TimeVar t_CASetup;
    TIC(t_CASetup);
    rabe.GenerateCPABEContext(lambda,numOfAttr);
    double duration = TOC(t_CASetup);
    std::cout << "CASetup by level: " << lambda << std::endl 
    <<"时间： "<< duration << "ms" 
    << std::endl
    << std::endl;
}





CentralAuth::~CentralAuth()
{
    std::cout << "End CentralAuth" << std::endl;
}