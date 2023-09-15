#include "cbd.h"

void cbd(uint16_t s[SABER_N], const unsigned char buf[SABER_POLYCOINBYTES])
{
	uint8_t d;
	uint16_t  a[4], b[4];
	int i;

	for(i=0;i<SABER_N/4;i++)
	{
	    	d = buf[i];
	    	a[0] =  d & 0x1;
	    	b[0] = (d >> 1) & 0x1;
	    	a[1] = (d >> 2) & 0x1;
	    	b[1] = (d >> 3) & 0x1;
	    	a[2] = (d >> 4) & 0x1;
	    	b[2] = (d >> 5) & 0x1;
	    	a[3] = (d >> 6) & 0x1;
	    	b[3] = (d >> 7) & 0x1;

	    	s[4*i+0] = (uint16_t)(a[0]  - b[0]);
	    	s[4*i+1] = (uint16_t)(a[1]  - b[1]);
	    	s[4*i+2] = (uint16_t)(a[2]  - b[2]);
	    	s[4*i+3] = (uint16_t)(a[3]  - b[3]);

	  }

}
