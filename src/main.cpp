#include <iostream>
#include "palisade.h"
#include "palisadecore.h"
#include "palisade-abe/abecore.h"


using namespace std;
using namespace lbcrypto;


int main(){
    printf("ad");

    // Set the main parameters
  int plaintextModulus = 65537;
  double sigma = 3.2;
  SecurityLevel securityLevel = HEStd_128_classic;
  uint32_t depth = 2;

  // Instantiate the crypto context
  CryptoContext<DCRTPoly> cryptoContext =
      CryptoContextFactory<DCRTPoly>::genCryptoContextBFVrns(
          plaintextModulus, securityLevel, sigma, 0, depth, 0, OPTIMIZED);

  // Enable features that you wish to use
  cryptoContext->Enable(ENCRYPTION);
  cryptoContext->Enable(SHE);
}
