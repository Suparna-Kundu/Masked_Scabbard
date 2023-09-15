#include <stdint.h>
#include "poly_mul.h"
#include <string.h>

void poly_mul(uint16_t* a, uint16_t* b, uint16_t* res)
{ 
	uint32_t i;

	uint16_t c[2*SABER_N];
	memset(c,0,2*SABER_N*sizeof(uint16_t));

	//toom_cook_3way(a, b, c);
	polymul_asm(c, a, b);

	//---------------reduction-------
	for(i=0;i<((SABER_N/2)-1);i++){
		res[i]=(c[i]-c[i+SABER_N]-c[i+SABER_N+(SABER_N/2)]);
	}
	res[(SABER_N/2)-1]=(c[(SABER_N/2)-1]-c[(SABER_N/2)-1+SABER_N]);
	for(i=(SABER_N/2);i<SABER_N;i++){
		res[i]=(c[i]+c[i+(SABER_N/2)]);
	}

}