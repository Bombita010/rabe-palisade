#include <iostream>

#include "myconfig.h"
#include "central_auth.h"
#include "attr_auth.h"
#include "user.h"
#include "node.h"
#include "BTtree.h"
#include "Algos.h"

#include "palisade/core/lattice/trapdoor.h"
#include "palisade/core/math/backend.h"
#include "palisade.h"
#include "palisadecore.h"
#include "palisade-abe/abecontext.h"

using namespace lbcrypto;

int main(){
  //参数配置类
  MyConfig &config = MyConfig::getConfig();

  usint ringSize = config.getUsintValue("ringSize");
  std::cout << "Value for 'ringSize': " << ringSize << std::endl;


  // CentralAuth ca(config);
  // ca.CASetup();

  //???根据给定的环size和基创建context???
  // 根据安全level和属性数量创建context

  //AA数量
  int numAAs = 3;
  // 属性数量
  usint numAttributes = 6;
  // 环size
  usint ringsize = 1024;
  // 基
  usint base = 64;

  // 时间记录1
  TimeVar t1;

  // 打印参数
  std::cout << "----------参数-----------" << std::endl;
  std::cout << "属性数量:" << numAttributes << std::endl;
  std::cout << "环size:" << ringsize << std::endl;
  std::cout << "基:" << base << std::endl;

  /*----------------------------CA初始化----------------------------*/
  // ABEContext<NativePoly> context;
  // std::cout << "根据以上参数生成context" << std::endl
  //           << std::endl;
  // context.GenerateCPABEContext(numAttributes, ringsize, base);

  SecurityLevel level = HEStd_192_classic;
  CentralAuth CA;
  CA.CASetup(level, numAttributes, numAAs);
  //CA.CASetup(numAttributes, ringsize, base);

  /*--------------------------主公私钥对--------------------------*/
  std::cout << "生成主私钥、主公钥" << std::endl;
  TIC(t1);
  CPABEMasterPublicKey<NativePoly> mpk;
  CPABEMasterSecretKey<NativePoly> msk;
  CA.rabe.Setup(&mpk, &msk);
  double duration = TOC(t1);
  std::cout << "初始化: " << duration << " ms" << std::endl
            << std::endl;

  /*-----------------------访问结构&户属性集----------------------*/
  std::cout << "创建访问结构和用户属性集" << std::endl;
  std::vector<usint> s(6);
  std::vector<int> w(6);

  for (usint j = 0; j < 6; j++)
    s[j] = rand() % 2;

  for (usint j = 0; j < 6; j++)
    w[j] = s[j];

  for (usint j = 0; j < 6; j++)
  {
    if (w[j] == 1)
    {
      w[j] = 0;
      break;
    }
  }

    for (usint j = 0; j < 6; j++)
    {
      if (s[j] == 0)
      {
        w[j] = -1;
        break;
      }
    }

    std::cout << "用户属性集" << s << std::endl;
    std::cout << "定义的访问策略" << w << std::endl
              << std::endl;
    CPABEUserAccess<NativePoly> ua(s);
    CPABEAccessPolicy<NativePoly> ap(w);

    /*--------------------------用户私钥--------------------------*/
    CPABESecretKey<NativePoly> sk;
    std::cout << "为属性集生成私钥" << std::endl;
    TIC(t1);
    CA.rabe.KeyGen(msk, mpk, ua, &sk);
    duration = TOC(t1);
    std::cout << "私钥生成：" << duration << " ms" << std::endl
              << std::endl;

    //生成明文
    std::vector<int64_t> vectorOfInts = {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1};
    Plaintext pt = CA.rabe.MakeCoefPackedPlaintext(vectorOfInts);
    std::cout << "明文向量bits" << vectorOfInts << std::endl
              << std::endl;

    /*-----------------------------加密-----------------------------*/
    std::cout << "依据访问策略加密明文" << std::endl;
    TIC(t1);
    CPABECiphertext<NativePoly> ct;
    CA.rabe.Encrypt(mpk, ap, pt, &ct);
    duration = TOC(t1);
    std::cout << "加密：" << duration << " ms" << std::endl
              << std::endl;

    /*-----------------------------解密-----------------------------*/
    std::cout << "解密密文" << std::endl;
    TIC(t1);
    Plaintext dt = CA.rabe.Decrypt(ap, ua, sk, ct);
    duration = TOC(t1);
    std::cout << "解密：" << duration << " ms" << std::endl
              << std::endl;

    //检查明文与密文是否匹配
    std::cout << "检查明文与密文是否匹配" << std::endl;
    if ( pt->GetElement<NativePoly>() == dt->GetElement<NativePoly>() )
    {
      std::cout << "加密&解密成功" << std::endl;
    }
    else
    {
      std::cout << "加密&解密失败" << std::endl;
    }
 
}
