/*  @file central_auth.h - 中央权威  */ 

#ifndef CENTRAL_AUTH_H
#define CENTRAL_AUTH_H

#include "palisade.h"

using namespace lbcrypto;
class CentralAuth
{
private:
    /* data */
public:
    //安全参数lambda
    usint level;
    //
    usint ringSize;
    //
    usint base;
    //
    usint numAttributes;

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
    void CASetup();
};

CentralAuth::~CentralAuth()
{
}

#endif //CENTRAL_AUTH_H