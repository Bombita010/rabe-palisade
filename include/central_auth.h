/*  @file central_auth.h - 中央权威  */ 

#ifndef CENTRAL_AUTH_H
#define CENTRAL_AUTH_H

#include "palisade.h"
#include "abecontext.h"

using namespace lbcrypto;
class CentralAuth
{
private:
    /* data */
public:
    //安全参数
    SecurityLevel level;
    //
    usint ringSize;
    //
    usint base;
    //
    usint numAttributes;
    //
    usint numAAs;

    ABEContext<NativePoly> rabe;

    /*
    *@
    *@
    *@param:                       Param Description
    *@param:                       Param Description
    *@
    *@return:                                         
    *@return:                                         
    */
    CentralAuth();
    ~CentralAuth();


    /*
    *@CA初始化算法
    *@
    *@param:                       Param Description
    *@param:                       Param Description
    *@
    *@return:                                         
    *@return:                                         
    */
    void CASetup(usint numOfAttr, usint ringSize, usint base);

    void CASetup(SecurityLevel lambda, usint numOfAttr, int numOfAA);
};


#endif //CENTRAL_AUTH_H