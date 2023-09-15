#include <stdint.h>
#include "poly_mul.h"
#include <string.h>


// static void myschool_book(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[2*SABER_N]) //simple school book
// { // Polynomial multiplication using the schoolbook method, c[x] = a[x]*b[x] 
// 	// SECURITY NOTE: TO BE USED FOR TESTING ONLY.  


// 	uint32_t i, j;
	
// 	for (i = 0; i < SABER_N; i++) {
// 		for (j = 0; j < SABER_N; j++) {
// 			res[i+j] += (a[i] * b[j]);
// 		}
// 	}
// }

void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
    uint32_t i;
    uint16_t c[2*SABER_N]={0};

    // memset(c, 0, (4*SABER_N));
    // for(i=0;i<(2*SABER_N);i++){
	// 	c[i]=0;
	// }
    // toom_cook_4way_mem_asm(a, b, res);
    polymul_asm( c, a, b );
    // myschool_book(a,b,c);
	//---------------reduction-------
	for(i=SABER_N;i<(2*SABER_N);i++){
		res[i-SABER_N]=(c[i-SABER_N]-c[i]);
	}

    // for(i=0;i<SABER_N;i++){
	// 	res[i]=res[i]&(SABER_Q-1);
	// }

}

void poly_mul_acc(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
    uint32_t i;
    uint16_t c[2*SABER_N]={0};

    // memset(c, 0, (4*SABER_N));
    // for(i=0;i<(2*SABER_N);i++){
	// 	c[i]=0;
	// }
    polymul_asm( c, a, b );
    // myschool_book(a,b,c);
	//---------------reduction-------
	for(i=SABER_N;i<(2*SABER_N);i++){
		res[i-SABER_N] += (c[i-SABER_N]-c[i]);
	}
    // toom_cook_4way_mem_asm(a, b, res);

    // for(i=0;i<SABER_N;i++){
	// 	res[i]=res[i]&(SABER_Q-1);
	// }
}


//------------------------------------------------
void pol_mul_64_sch(uint16_t* a, uint8_t* b, uint16_t* res, uint16_t p)
{ 
	uint32_t i,j;
	uint16_t temp1,d[SABER_N];
	uint16_t temp2;
	
//-------------------normal multiplication-----------------

	uint16_t c[128];

	for (i = 0; i < 128; i++) c[i] = 0;
	
	for (i = 0; i < (SABER_N/2); i++)
	{
		d[2*i] = ((b[i]& 0x0f) ^ 0x8 ) - 0x8;
		d[2*i+1] = (((b[i] & 0xf0)>>4) ^ 0x8 ) - 0x8;
	}	
	
	polymul_asm( c, a, d );
	
	//---------------reduction-------
	for(i=64;i<128;i++){
		res[i-64]=(c[i-64]-c[i])&p;
	}
	
}