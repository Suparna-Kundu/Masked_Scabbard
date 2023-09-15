#include "pack_unpack.h"



////////////////////////////////////////////////////////////////////////////////////////////////
///                                 Polynomial to bit-string                                 ///
////////////////////////////////////////////////////////////////////////////////////////////////


/* This function reduces its input mod 2 */
void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[SABER_N])
{
    size_t i, j;
    uint8_t byte;
    for (j = 0; j < SABER_KEYBYTES; j++) {
        byte = 0;
        for (i = 0; i < 8; i++) {
            byte |= ((data[j * 8 + i] & 0x01) << i);
        }
        bytes[j] = byte;
    }
}

/* This function reduces its input mod p */
void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    uint8_t *out = bytes;

#if SABER_EP == 10    
    for (i = 0; i < SABER_N / 4; i++) {
        out[0] = (uint8_t) (in[0]);
        out[1] = (uint8_t) (((in[0] >> 8) & 0x03) | (in[1] << 2));
        out[2] = (uint8_t) (((in[1] >> 6) & 0x0f) | (in[2] << 4));
        out[3] = (uint8_t) (((in[2] >> 4) & 0x3f) | (in[3] << 6));
        out[4] = (uint8_t) (in[3] >> 2);
        in += 4;
        out += 5;
    }
#elif SABER_EP == 9
    for (i = 0; i < SABER_N / 8; i++) {
        out[0] = (uint8_t) (in[0]);
        out[1] = (uint8_t) (((in[0] >> 8) & 0x01) | (in[1] << 1));
        out[2] = (uint8_t) (((in[1] >> 7) & 0x03) | (in[2] << 2));
        out[3] = (uint8_t) (((in[2] >> 6) & 0x07) | (in[3] << 3));
        out[4] = (uint8_t) (((in[3] >> 5) & 0x0f) | (in[4] << 4));
        out[5] = (uint8_t) (((in[4] >> 4) & 0x1f) | (in[5] << 5));
        out[6] = (uint8_t) (((in[5] >> 3) & 0x3f) | (in[6] << 6));
        out[7] = (uint8_t) (((in[6] >> 2) & 0x7f) | (in[7] << 7));
        out[8] = (uint8_t) (in[7] >> 1);
        in += 8;
        out += 9;
    }
#else
#error "Unsupported SABER parameter."
#endif    
}


/* This function reduces its input mod p */
uint32_t POLp2BS_cmp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N])
{
    size_t j;
    const uint16_t *in = data;
    const uint8_t *out = bytes;
    uint32_t fail = 0;

#if SABER_EP == 10
    for (j = 0; j < SABER_N / 4; j++) {
        fail |= out[0] ^ (uint8_t) (in[0]);
        fail |= out[1] ^ (uint8_t) (((in[0] >> 8) & 0x03) | (in[1] << 2));
        fail |= out[2] ^ (uint8_t) (((in[1] >> 6) & 0x0f) | (in[2] << 4));
        fail |= out[3] ^ (uint8_t) (((in[2] >> 4) & 0x3f) | (in[3] << 6));
        fail |= out[4] ^ (uint8_t) (in[3] >> 2);
        in += 4;
        out += 5;
    }
#elif SABER_EP == 9
    for (j = 0; j < SABER_N / 8; j++) {
        fail |= out[0] ^ (uint8_t) (in[0]);
        fail |= out[1] ^ (uint8_t) (((in[0] >> 8) & 0x01) | (in[1] << 1));
        fail |= out[2] ^ (uint8_t) (((in[1] >> 7) & 0x03) | (in[2] << 2));
        fail |= out[3] ^ (uint8_t) (((in[2] >> 6) & 0x07) | (in[3] << 3));
        fail |= out[4] ^ (uint8_t) (((in[3] >> 5) & 0x0f) | (in[4] << 4));
        fail |= out[5] ^ (uint8_t) (((in[4] >> 4) & 0x1f) | (in[5] << 5));
        fail |= out[6] ^ (uint8_t) (((in[5] >> 3) & 0x3f) | (in[6] << 6));
        fail |= out[7] ^ (uint8_t) (((in[6] >> 2) & 0x7f) | (in[7] << 7));
        fail |= out[8] ^ (uint8_t) (in[7] >> 1);
        in += 8;
        out += 9;
    }
#else
#error "Unsupported SABER parameter."
#endif
    return fail;
}

/* This function reduces its input mod q */
void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    uint8_t *out = bytes;
    for (i = 0; i < SABER_N / 8; i++) {
        out[0] = (uint8_t) (in[0]);
        out[1] = (uint8_t) (((in[0] >> 8) & 0x07) | (in[1] << 3));
        out[2] = (uint8_t) (((in[1] >> 5) & 0x3f) | (in[2] << 6));
        out[3] = (uint8_t) (in[2] >> 2);
        out[4] = (uint8_t) (((in[2] >> 10) & 0x01) | (in[3] << 1));
        out[5] = (uint8_t) (((in[3] >> 7) & 0x0f) | (in[4] << 4));
        out[6] = (uint8_t) (((in[4] >> 4) & 0x7f) | (in[5] << 7));
        out[7] = (uint8_t) (in[5] >> 1);
        out[8] = (uint8_t) (((in[5] >> 9) & 0x03) | (in[6] << 2));
        out[9] = (uint8_t) (((in[6] >> 6) & 0x1f) | (in[7] << 5));
        out[10] = (uint8_t) (in[7] >> 3);
        in += 8;
        out += 11;
    }
}


/* This function reduces its input mod T */
void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N])
{
    size_t j;
    const uint16_t *in = data;
    uint8_t *out = bytes;
#if SABER_ET == 3 // LightSaber and FireSaber
    for (j = 0; j < SABER_N / 8; j++) {
        out[0] = (uint8_t) ((in[0] & 0x7) | ((in[1] & 0x07) << 3) | (in[2] << 6));
        out[1] = (uint8_t) (((in[2] >> 2) & 0x01) | ((in[3] & 0x07) << 1) | ((in[4] & 0x07) << 4) | (in[5] << 7));
        out[2] = (uint8_t) (((in[5] >> 1) & 0x03) | ((in[6] & 0x07) << 2) | (in[7] << 5));
        in += 8;
        out += 3;
    }
#elif SABER_ET == 5 // Saber
    for (j = 0; j < SABER_N / 8; j++) {
        out[0] = (uint8_t) ((in[0] & 0x1f) | (in[1] << 5));
        out[1] = (uint8_t) (((in[1] >> 3) & 0x03) | ((in[2] & 0x1f) << 2) | (in[3] << 7));
        out[2] = (uint8_t) (((in[3] >> 1) & 0x0f) | (in[4] << 4));
        out[3] = (uint8_t) (((in[4] >> 4) & 0x01) | ((in[5] & 0x1f) << 1) | (in[6] << 6));
        out[4] = (uint8_t) (((in[6] >> 2) & 0x07) | (in[7] << 3));
        in += 8;
        out += 5;
    }
#else
#error "Unsupported SABER parameter."
#endif
}

/* This function reduces its input mod T */
uint32_t POLT2BS_cmp(const uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N])
{
    size_t j;
    const uint16_t *in = data;
    const uint8_t *out = bytes;
    uint32_t fail = 0;
#if SABER_ET == 3 // LightSaber and FireSaber
    for (j = 0; j < SABER_N / 8; j++) {
        fail |= out[0] ^ (uint8_t) ((in[0] & 0x7) | ((in[1] & 0x07) << 3) | (in[2] << 6));
        fail |= out[1] ^ (uint8_t) (((in[2] >> 2) & 0x01) | ((in[3] & 0x07) << 1) | ((in[4] & 0x07) << 4) | (in[5] << 7));
        fail |= out[2] ^ (uint8_t) (((in[5] >> 1) & 0x03) | ((in[6] & 0x07) << 2) | (in[7] << 5));
        in += 8;
        out += 3;
    }
#elif SABER_ET == 5 // Saber
    for (j = 0; j < SABER_N / 8; j++) {
        fail |= out[0] ^ (uint8_t) ((in[0] & 0x1f) | (in[1] << 5));
        fail |= out[1] ^ (uint8_t) (((in[1] >> 3) & 0x03) | ((in[2] & 0x1f) << 2) | (in[3] << 7));
        fail |= out[2] ^ (uint8_t) (((in[3] >> 1) & 0x0f) | (in[4] << 4));
        fail |= out[3] ^ (uint8_t) (((in[4] >> 4) & 0x01) | ((in[5] & 0x1f) << 1) | (in[6] << 6));
        fail |= out[4] ^ (uint8_t) (((in[6] >> 2) & 0x07) | (in[7] << 3));
        in += 8;
        out += 5;
    }
#else
#error "Unsupported SABER parameter."
#endif
    return fail;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///                                 Bit-string to polynomial                                 ///
////////////////////////////////////////////////////////////////////////////////////////////////

/* This function does NOT reduce its output mod 2 */
void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[SABER_N])
{
    size_t i, j;
    uint8_t byte;
    for (j = 0; j < SABER_KEYBYTES; j++) {
        byte = bytes[j];
        for (i = 0; i < 8; i++) {
            data[j * 8 + i] = byte >> i;
        }
    }
}

/* This function does NOT reduce its output mod p */
void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[SABER_N]){
    uint32_t j;
	uint32_t offset_data,offset_byte;	

#if SABER_EP == 10
	for(j=0;j<SABER_N/4;j++){
		offset_byte=5*j;
		offset_data=4*j;
		data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x03)<<8);
		data[offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 2 ] & 0x0f)<<6);		
		data[offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 3 ] & 0x3f)<<4);
		data[offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 4 ] & 0xff)<<2);		
	}
    
#elif SABER_EP == 9
	for(j=0;j<SABER_N/8;j++){
		offset_byte=9*j;
		offset_data=8*j;	
		data[offset_data + 0]= (bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x01)<<8);
		data[offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>1) & (0x7f)) |  ((bytes[ offset_byte + 2 ] & 0x03)<<7);	
		data[offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 3 ] & 0x07)<<6);
		data[offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>3) & (0x1f)) |  ((bytes[ offset_byte + 4 ] & 0x0f)<<5);
		data[offset_data + 4]= ( (bytes[ offset_byte + 4 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 5 ] & 0x1f)<<4);
		data[offset_data + 5]= ( (bytes[ offset_byte + 5 ]>>5) & (0x07)) |  ((bytes[ offset_byte + 6 ] & 0x3f)<<3);
		data[offset_data + 6]= ( (bytes[ offset_byte + 6 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 7 ] & 0x7f)<<2);
		data[offset_data + 7]= ( (bytes[ offset_byte + 7 ]>>7) & (0x01)) |  ((bytes[ offset_byte + 8 ] & 0xff)<<1);	
	}

#else
#error "Unsupported SABER parameter."
#endif
}


/* This function does NOT reduce its output mod q */
void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[SABER_N]){
    uint32_t j;
	uint32_t offset_data,offset_byte;	

	for(j=0;j<SABER_N/8;j++){
		offset_byte=11*j;
		offset_data=8*j;
			
		data[offset_data + 0]= bytes[ offset_byte + 0 ] |  ((bytes[ offset_byte + 1 ] & 0x07)<<8);
		data[offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>3) & (0x1f)) |  ((bytes[ offset_byte + 2 ] & 0x3f)<<5);
		data[offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 3 ] & 0xff)<<2) |  ((bytes[ offset_byte + 4 ] & 0x01)<<10);
		data[offset_data + 3]= ( (bytes[ offset_byte + 4 ]>>1) & (0x7f)) |  ((bytes[ offset_byte + 5 ] & 0x0f)<<7);
		data[offset_data + 4]= ( (bytes[ offset_byte + 5 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 6 ] & 0x7f)<<4);
		data[offset_data + 5]= ( (bytes[ offset_byte + 6 ]>>7) & (0x01)) |  ((bytes[ offset_byte + 7 ] & 0xff)<<1) |  ((bytes[ offset_byte + 8 ] & 0x03)<<9);
		data[offset_data + 6]= ( (bytes[ offset_byte + 8 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 9 ] & 0x1f)<<6);
		data[offset_data + 7]= ( (bytes[ offset_byte + 9 ]>>5) & (0x07)) |  ((bytes[ offset_byte + 10 ] & 0xff)<<3);
	}

}

/* This function does NOT reduce its output mod T */
void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N]){
    uint32_t j;
	uint32_t offset_data,offset_byte;

#if SABER_ET == 3 // LightSaber and FireSaber
	for(j=0;j<SABER_N/8;j++){
		offset_byte=3*j;
		offset_data=8*j;
		data[offset_data + 0] = (bytes[offset_byte+0])&0x07;
		data[offset_data + 1] = ( (bytes[offset_byte+0])>>3 )&0x07;
		data[offset_data + 2] = ( ( (bytes[offset_byte+0])>>6 )&0x03) | ( ( (bytes[offset_byte+1])&0x01)<<2 );
		data[offset_data + 3] = ( (bytes[offset_byte+1])>>1 )&0x07;
		data[offset_data + 4] = ( (bytes[offset_byte+1])>>4 )&0x07;
		data[offset_data + 5] = ( ( (bytes[offset_byte+1])>>7 )&0x01) | ( ( (bytes[offset_byte+2])&0x03)<<1 );
		data[offset_data + 6] = ( (bytes[offset_byte+2]>>2)&0x07 );
		data[offset_data + 7] = ( (bytes[offset_byte+2]>>5)&0x07 );
	}

#elif SABER_ET == 5 // Saber
	for(j=0;j<SABER_N/8;j++){
		offset_byte=5*j;
		offset_data=8*j;
		data[offset_data + 0] = (bytes[offset_byte+0])&0x1f;
		data[offset_data + 1] = ( ( (bytes[offset_byte+0])>>5 )&0x07) | ( ( (bytes[offset_byte+1])&0x03)<<3 );
		data[offset_data + 2] = ( ( (bytes[offset_byte+1])>>2 )&0x1f);
		data[offset_data + 3] = ( ( (bytes[offset_byte+1])>>7 )&0x01) | ( ( (bytes[offset_byte+2])&0x0f)<<1 );
		data[offset_data + 4] = ( ( (bytes[offset_byte+2])>>4 )&0x0f) | ( ( (bytes[offset_byte+3])&0x01)<<4 );
		data[offset_data + 5] = ( ( (bytes[offset_byte+3])>>1 )&0x1f);
		data[offset_data + 6] = ( ( (bytes[offset_byte+3])>>6 )&0x03) | ( ( (bytes[offset_byte+4])&0x07)<<2 );
		data[offset_data + 7] = ( (bytes[offset_byte+4]>>3)&0x1f );
	}

#else
#error "Unsupported SABER parameter."
#endif
}


////////////////////////////////////////////////////////////////////////////////////////////////
///                             Polynomial vector to bit-string                              ///
////////////////////////////////////////////////////////////////////////////////////////////////


void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[SABER_L][SABER_N]) 
{
    size_t i;

    for (i = 0; i < SABER_L; i++) {
        /* This function reduces its input mod p */
        POLp2BS(&bytes[i * SABER_POLYCOMPRESSEDBYTES], data[i]);
    }
}

uint32_t POLVECp2BS_cmp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[SABER_L][SABER_N])
{
    size_t i;
    uint32_t fail = 0;

    for (i = 0; i < SABER_L; i++) {
        /* This function reduces its input mod p */
        fail |= POLp2BS_cmp(&bytes[i * SABER_POLYCOMPRESSEDBYTES], data[i]);
    }

    return fail;
}


void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[SABER_L][SABER_N]) 
{
    size_t i;

    for (i = 0; i < SABER_L; i++) {
        /* This function reduces its input mod q */
        POLq2BS(&bytes[i * SABER_POLYBYTES], data[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
///                             Bit-string to polynomial vector                              ///
////////////////////////////////////////////////////////////////////////////////////////////////

void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[SABER_L][SABER_N])
{
    size_t i;
    for (i = 0; i < SABER_L; i++) {
        BS2POLp(&bytes[i * SABER_POLYCOMPRESSEDBYTES], data[i]);
    }
}

void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[SABER_L][SABER_N])
{
    size_t i;
    for (i = 0; i < SABER_L; i++) {
        BS2POLq(&bytes[i * SABER_POLYBYTES], data[i]);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The following functions are for compressed secret. Secrets are stored with their 4-bit value in [-SABER_MU/2, SABER_MU/2]. ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef SABER_COMPRESS_SECRETKEY

/* This function reduces its input mod 2**4 */
void POLmu2BS(uint8_t bytes[SABER_N / 4], const uint16_t data[SABER_N])
{
    size_t j;
    const uint16_t *in = data;
    uint8_t *out = bytes;
    for (j = 0; j < SABER_N / 4; j++) {
        out[0] = (uint8_t) ((in[0] & 0x03) | ((in[1] & 0x03) << 2) | ((in[2] & 0x03) << 4) | (in[3] << 6));
        in += 4;
        out += 1;
    }
}

/* This function does NOT reduce its output mod q */
void BS2POLmu(const uint8_t bytes[SABER_POLYSECRETBYTES], uint16_t data[SABER_N]){
    uint32_t j;
	uint32_t offset_data,offset_byte;	
	
    for(j=0;j<SABER_N/4;j++){
        offset_byte=j;
        offset_data=4*j;
        data[offset_data]   = ( (bytes[offset_byte] & 0x03) ^ 0x2 ) - 0x2;
        data[offset_data+1] = ( ((bytes[offset_byte]>>2) & 0x03) ^ 0x2 ) - 0x2;
        data[offset_data+2] = ( ((bytes[offset_byte]>>4) & 0x03) ^ 0x2 ) - 0x2;
        data[offset_data+3] = ( ((bytes[offset_byte]>>6) & 0x03) ^ 0x2 ) - 0x2;

    }
}


void POLVECmu2BS(uint8_t bytes[SABER_INDCPA_SECRETKEYBYTES], const uint16_t data[SABER_L][SABER_N])
{
    size_t i;
    for (i = 0; i < SABER_L; i++) {
        POLmu2BS(bytes + i * SABER_POLYSECRETBYTES, data[i]);
    }
}

void BS2POLVECmu(const uint8_t bytes[SABER_INDCPA_SECRETKEYBYTES], uint16_t data[SABER_L][SABER_N])
{
    size_t i;
    for (i = 0; i < SABER_L; i++) {
        BS2POLmu(bytes + i * SABER_POLYSECRETBYTES, data[i]);
    }
}

#endif
