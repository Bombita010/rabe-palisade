#include <iostream>

//#include "palisade/core/lattice/trapdoor.h"
#include "palisade/core/math/backend.h"
#include "palisade.h"
#include "palisadecore.h"
#include "palisade-abe/abecontext.h"

using namespace lbcrypto;

int main(int argc, char *argv[]){
  //???根据给定的环size和基创建context???
  //根据安全level和属性数量创建context

  //环size
  usint ringsize = 1024;
  //属性数量
  usint numAttributes = 6;
  //基
  usint base = 64;

  //时间记录1
  TimeVar t1;

  //打印参数
  std::cout << "参数:" << std::endl;
  std::cout << "环size:" << ringsize << std::endl;
  std::cout << "属性数量:" << numAttributes << std::endl;
  std::cout << "基:" << base <<std::endl;


  ABEContext<NativePoly> context;
  std::cout << "根据以上参数生成context" << std::endl
            << std::endl;
  context.GenerateCPABEContext(numAttributes, ringsize, base);

  //生成主公私钥对
  std::cout << "生成主私钥、主公钥" << std::endl;
  TIC(t1);
  CPABEMasterPublicKey<NativePoly> mpk;
  CPABEMasterSecretKey<NativePoly> msk;
  context.Setup(&mpk, &msk);
  double duration = TOC(t1);
  std::cout << "初始化: " << duration << " ms" << std::endl
            << std::endl;
  

  //创建随机的访问结构和用户属性集
  std::cout << "创建访问结构和用户属性集" << std::endl;
  std::vector<usint> s(6);
  std::vector<int> w(6);

  for (usint j = 0; j < 6; j++)
    s[j] = rand() % 2;
  
  for (usint j = 0; j < 6; j++)
    w[j] = s[j];
  
  for (usint j = 0; j < 6; j++)
    if (w[j] == 1)
    {
      w[j] = 0;
      break;
    }

  for (usint j = 0; j < 6; j++)
    if (s[j] == 0)
    {
      w[j] = -1;
      break;
    }

  std::cout << "用户属性集" << s << std::endl;
  std::cout << "定义的访问策略" << w << std::endl
            << std::endl;
  CPABEUserAccess<NativePoly> ua(s);
  CPABEAccessPolicy<NativePoly> ap(w);

  //生成和属性集匹配的私钥
  CPABESecretKey<NativePoly> sk;
  std::cout << "为属性集生成私钥" << std::endl;
  TIC(t1);
  context.KeyGen(msk, mpk, ua, &sk);
  duration = TOC(t1);
  std::cout << "私钥生成：" << duration << " ms" << std::endl
            << std::endl;
  
  //生成明文
  std::vector<int64_t> vectorOfInts = {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1};
  Plaintext pt = context.MakeCoefPackedPlaintext(vectorOfInts);
  std::cout << "明文向量bits" << vectorOfInts << std::endl
            << std::endl;
  
  //加密阶段
  std::cout << "依据访问策略加密明文" << std::endl;
  TIC(t1);
  CPABECiphertext<NativePoly> ct;
  context.Encrypt(mpk, ap, pt, &ct);
  duration = TOC(t1);
  std::cout << "加密：" << duration << " ms" << std::endl
            << std::endl;

  //解密阶段
  std::cout << "解密密文" << std::endl;
  TIC(t1);
  Plaintext dt = context.Decrypt(ap, ua, sk, ct);
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
