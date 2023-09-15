#include <stdint.h>

extern int jump128divsteps_mod3(int minusdelta, int* M, int* f, int* g);
int jump256divsteps_mod3(int minusdelta, int* M, int* f, int* g);
extern void __gf_polymul_128x128_2x2_x2p2_mod3(int* V,int* M,int *fh, int* gh);
extern void __gf_polymul_128x128_2x2_x_2x2_mod3(int* M,int* M1,int* M2);

int jump256divsteps_mod3(int minusdelta, int* M, int* f, int* g){
  int M1[192], M2[192], fg[128];
  minusdelta = jump128divsteps_mod3(minusdelta, M1, f, g);
  __gf_polymul_128x128_2x2_x2p2_mod3(fg, M1, f+32, g+32);
  minusdelta = jump128divsteps_mod3(minusdelta, M2, fg, fg+64);
  // __gf_polymul_128x128_2x2_x2p2_mod3(M, M2, fg+32, fg+96);
  __gf_polymul_128x128_2x2_x_2x2_mod3(M+128, M1+64, M2+64);
  return minusdelta;
}
