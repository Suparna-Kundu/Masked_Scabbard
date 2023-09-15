#include "cbd-masked.h"
#include "masksONOFF.h"
#include <string.h>

/*
-------------------------------------------
       Higher order masking functions
-------------------------------------------
*/


static void b2a_qbitn(uint16_t x[2][SABER_SHARES], uint32_t n, uint16_t xn[2], uint16_t x_bit[2][SABER_SHARES])
{
    uint32_t j, rand;
    uint16_t temp[2][SABER_SHARES];

    rand=random_uint32();
    temp[0][n-1] = (uint16_t) rand;
    temp[0][0] = x_bit[0][0] - temp[0][n-1]; 
    temp[1][n-1] = (uint16_t) (rand>>16);
    temp[1][0] = x_bit[1][0] - temp[1][n-1]; 

    for(j=1;j<(n-1);j++) {
        temp[0][j] = x_bit[0][j]-(rand & 0xffff);
        temp[0][n-1] += (rand & 0xffff);
        temp[1][j] = x_bit[1][j]-((rand>>16) & 0xffff);
        temp[1][n-1] += ((rand>>16) & 0xffff);
    }
    for(j=0;j<n;j++) {
        x[0][j] = temp[0][j] - (2*(temp[0][j]*xn[0]));
        x[1][j] = temp[1][j] - (2*(temp[1][j]*xn[1]));
    }    
    x[0][0] += xn[0];
    x[1][0] += xn[1];
}


static void Refreshadd(uint16_t x[2][SABER_SHARES])
{
    uint32_t i, j, rand;
    
    for(i=0;i<(SABER_SHARES-1);i++)
    {
    	for(j=(i+1);j<SABER_SHARES;j++)
    	{
            rand = random_uint32();
            x[0][i] += (rand & 0xffff);
            x[0][j] -= (rand & 0xffff);
            x[1][i] += ((rand >> 16) & 0xffff);
            x[1][j] -= ((rand >> 16) & 0xffff);
    	}
    }

}

static void b2a_qbit(uint16_t x[2][SABER_SHARES], uint16_t x_bit[2][SABER_SHARES])
{
    uint32_t i;
    uint16_t xn[2];

    x[0][0] = x_bit[0][0];
    x[1][0] = x_bit[1][0];
    for(i=1;i<SABER_SHARES;i++) {
        xn[0] = x_bit[0][i];
        xn[1] = x_bit[1][i];
        b2a_qbitn(x, (i+1), xn, x);
    }
    Refreshadd(x);
}

void cbd_masked_HO(uint16_t s[SABER_SHARES][SABER_N], const uint8_t coins[SABER_SHARES][SABER_POLYCOINBYTES])
{
    uint32_t i,k,l;
    uint16_t x_bit[4][SABER_SHARES], y_bit[4][SABER_SHARES], z_bit[2][SABER_SHARES];
    uint16_t temp1[2][SABER_SHARES],temp2[2][SABER_SHARES];
    uint8_t d;
    
    for(i=0;i<SABER_N/4;i++) {
        for(k=0;k<SABER_SHARES;k++) {
            d = coins[k][i];
            x_bit[0][k] =  d & 0x1;
            y_bit[0][k] =  (d >> 1) & 0x1;
            x_bit[1][k] =  (d >> 2) & 0x1;
            y_bit[1][k] =  (d >> 3) & 0x1;
            x_bit[2][k] =  (d >> 4) & 0x1;
            y_bit[2][k] =  (d >> 5) & 0x1;
            x_bit[3][k] =  (d >> 6) & 0x1;
            y_bit[3][k] =  (d >> 7) & 0x1;
        }
        for(l=0;l<4;l+=2) {
            b2a_qbit(temp1, &x_bit[l]);
            b2a_qbit(temp2, &y_bit[l]);
            for(k=0;k<SABER_SHARES;k++) {
                z_bit[0][k] = (uint16_t)(temp1[0][k]-temp2[0][k]);
                s[k][4*i+l] = z_bit[0][k];
                z_bit[1][k] = (uint16_t)(temp1[1][k]-temp2[1][k]);
                s[k][4*i+l+1] = z_bit[1][k];
            }
        }
    }   
}