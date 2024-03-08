#include "central_auth.h"
#include "myconfig.h"

#include "abecontext.h"


/*
*@CA初始化算法
*@
*@param:                       Param Description
*@param:                       Param Description
*@
*@return:                                         
*@return:                                         
*/
void CentralAuth::CASetup()
{
    TimeVar t_CASetup;
    ABEContext<Poly> mabe;
    TIC(t_CASetup);
    mabe.GenerateCPABEContext(numAttributes, ringSize, base);
    double duration = TOC(t_CASetup);
    std::cout << "generate ABE context:" << duration << std::endl;
}