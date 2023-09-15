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
        for (i = 0; i < 2; i++) {
            byte |= ((data[j * 2 + i] & 0x0f) << (4*i));
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
    
    for (i = 0; i < SABER_N/8; i++) {
        out[0] = (uint8_t) (in[0]);
        out[1] = (uint8_t) (((in[0] >> 8) & 0x1f) | (in[1] << 5));
        out[2] = (uint8_t) (in[1] >> 3);
        out[3] = (uint8_t) (((in[1] >> 11) & 0x03) | (in[2] << 2));
        out[4] = (uint8_t) (((in[2] >> 6) & 0x7f) | (in[3] << 7));
        out[5] = (uint8_t) (in[3] >> 1);
        out[6] = (uint8_t) (((in[3] >> 9) & 0x0f) | (in[4] << 4));
        out[7] = (uint8_t) (in[4] >> 4);
        out[8] = (uint8_t) (((in[4] >> 12) & 0x01) | (in[5] << 1));
        out[9] = (uint8_t) (((in[5] >> 7) & 0x3f) | (in[6] << 6));
        out[10] = (uint8_t) (in[6] >> 2);
        out[11] = (uint8_t) (((in[6] >> 10) & 0x07) | (in[7] << 3));
        out[12] = (uint8_t) (in[7] >> 5);
        in += 8;
        out += 13;
    }
}


/* This function reduces its input mod p */
uint32_t POLp2BS_cmp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    const uint8_t *out = bytes;
    uint32_t fail = 0;

    for (i = 0; i < SABER_N/8; i++) {
        fail |= out[0] ^ (uint8_t) (in[0]);
        fail |= out[1] ^ (uint8_t) (((in[0] >> 8) & 0x1f) | (in[1] << 5));
        fail |= out[2] ^ (uint8_t) (in[1] >> 3);
        fail |= out[3] ^ (uint8_t) (((in[1] >> 11) & 0x03) | (in[2] << 2));
        fail |= out[4] ^ (uint8_t) (((in[2] >> 6) & 0x7f) | (in[3] << 7));
        fail |= out[5] ^ (uint8_t) (in[3] >> 1);
        fail |= out[6] ^ (uint8_t) (((in[3] >> 9) & 0x0f) | (in[4] << 4));
        fail |= out[7] ^ (uint8_t) (in[4] >> 4);
        fail |= out[8] ^ (uint8_t) (((in[4] >> 12) & 0x01) | (in[5] << 1));
        fail |= out[9] ^ (uint8_t) (((in[5] >> 7) & 0x3f) | (in[6] << 6));
        fail |= out[10] ^ (uint8_t) (in[6] >> 2);
        fail |= out[11] ^ (uint8_t) (((in[6] >> 10) & 0x07) | (in[7] << 3));
        fail |= out[12] ^ (uint8_t) (in[7] >> 5);

        in += 8;
        out += 13;
    }
    return fail;
}

/* This function reduces its input mod q */
void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    uint8_t *out = bytes;
    for (i = 0; i < SABER_N/8; i++) {

        out[0]= (uint8_t) (in[0]);
        out[1]= (uint8_t) (((in[0] >>8) & 0x7f ) | (in[1] << 7));
        out[2]= (uint8_t) ((in[1] >>1) & 0xff );
        out[3]= (uint8_t) (((in[1] >>9) & 0x3f ) | (in[2] << 6));
        out[4]= (uint8_t) ((in[2] >>2) & 0xff );
        out[5]= (uint8_t) (((in[2] >>10) & 0x1f ) | (in[3] << 5));
        out[6]= (uint8_t) ((in[3] >>3) & 0xff );
        out[7]= (uint8_t) (((in[3] >>11) & 0x0f ) | (in[4] << 4 ));
        out[8]= (uint8_t) ((in[4] >>4) & 0xff );
        out[9]= (uint8_t) (((in[4] >>12) & 0x07 ) | (in[5] << 3 ));
        out[10]= (uint8_t) ((in[5] >>5) & 0xff );
        out[11]= (uint8_t) (((in[5] >>13) & 0x03 ) | (in[6] << 2 ));
        out[12]= (uint8_t) ((in[6] >>6) & 0xff );
        out[13]= (uint8_t) (((in[6] >>14) & 0x01 ) | (in[7] << 1 ));
        out[14]= (uint8_t) ((in[7] >>7) & 0xff );
        
        in += 8;
        out += 15;
    }
}


/* This function reduces its input mod T */
void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    uint8_t *out = bytes;
    
    for(i=0;i<SABER_N/8;i++){

		out[0] = (uint8_t) (( in[0] & (0x7f)) | (in[1] << 7));
		out[1] = (uint8_t) ( ((in[1] >>1) & 0x3f ) | (in[2] << 6));
		out[2] = (uint8_t) ( ((in[2] >>2) & 0x1f ) | (in[3] << 5));
		out[3] = (uint8_t) ( ((in[3] >>3) & 0x0f ) | (in[4] << 4));
		out[4] = (uint8_t) ( ((in[4] >>4) & 0x07 ) | (in[5] << 3));
		out[5] = (uint8_t) ( ((in[5] >>5) & 0x03 ) | (in[6] << 2));
		out[6] = (uint8_t) ( ((in[6] >>6) & 0x01 ) | (in[7] << 1));

        in += 8;
        out += 7;
	}
}

/* This function reduces its input mod T */
uint32_t POLT2BS_cmp(const uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N])
{
    size_t i;
    const uint16_t *in = data;
    const uint8_t *out = bytes;
    uint32_t fail = 0;

    for(i=0;i<SABER_N/8;i++){

		fail |= out[0] ^ (uint8_t) (( in[0] & (0x7f)) | (in[1] << 7));
		fail |= out[1] ^ (uint8_t) ( ((in[1] >>1) & 0x3f ) | (in[2] << 6));
		fail |= out[2] ^ (uint8_t) ( ((in[2] >>2) & 0x1f ) | (in[3] << 5));
		fail |= out[3] ^ (uint8_t) ( ((in[3] >>3) & 0x0f ) | (in[4] << 4));
		fail |= out[4] ^ (uint8_t) ( ((in[4] >>4) & 0x07 ) | (in[5] << 3));
		fail |= out[5] ^ (uint8_t) ( ((in[5] >>5) & 0x03 ) | (in[6] << 2));
		fail |= out[6] ^ (uint8_t) ( ((in[6] >>6) & 0x01 ) | (in[7] << 1));

        in += 8;
        out += 7;
	}
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
        for (i = 0; i < 2; i++) {
            data[j * 2 + i] = (byte >> (4*i)) & 0x0f;
        }
    }
}

/* This function does NOT reduce its output mod p */
void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[SABER_N]){
    
    size_t i;
    const uint8_t *in = bytes;
    uint16_t *out = data;//int16_t *out = (int16_t *)data;

    for (i = 0; i < SABER_N/8; i++) {
        out[0] = (in[0]) | (in[1] << 8);
        out[1] = (in[1] >> 5) | (in[2] << 3) | (in[3] << 11);
        out[2] = (in[3] >> 2) | (in[4] << 6);
        out[3] = (in[4] >> 7) | (in[5] << 1) | (in[6] << 9);
        out[4] = (in[6] >> 4) | (in[7] << 4) | (in[8] << 12);
        out[5] = (in[8] >> 1) | (in[9] << 7);
        out[6] = (in[9] >> 6) | (in[10] << 2) | (in[11] << 10);
        out[7] = (in[11] >> 3) | (in[12] << 5);
        in += 13;
        out += 8;
    }
}


/* This function does NOT reduce its output mod q */
void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[SABER_N]){
    uint32_t j;
	uint32_t offset_data,offset_byte;	

	for(j=0;j<SABER_N/8;j++){
		offset_byte = 15*j;
        offset_data = 8*j;
        data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x7f)<<8);
        data[offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>7) & (0x01)) | ((bytes[offset_byte + 2] & 0xff)<<1) | ((bytes[offset_byte + 3] & 0x3f)<<9);
        data[offset_data + 2]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) | ((bytes[offset_byte + 4] & 0xff)<<2) | ((bytes[offset_byte + 5] & 0x1f)<<10);;
        data[offset_data + 3]= ( (bytes[ offset_byte + 5 ]>>5) & (0x07)) | ((bytes[offset_byte + 6] & 0xff)<<3) | ((bytes[offset_byte + 7] & 0x0f)<<11);
        data[offset_data + 4]= ( (bytes[ offset_byte + 7 ]>>4) & (0x0f)) | ((bytes[offset_byte + 8] & 0xff)<<4) | ((bytes[offset_byte + 9] & 0x07)<<12);
        data[offset_data + 5]= ( (bytes[ offset_byte + 9 ]>>3) & (0x1f)) | ((bytes[offset_byte + 10] & 0xff)<<5) | ((bytes[offset_byte + 11] & 0x03)<<13);
        data[offset_data + 6]= ( (bytes[ offset_byte + 11]>>2) & (0x3f)) | ((bytes[offset_byte + 12] & 0xff)<<6) | ((bytes[offset_byte + 13] & 0x01)<<14);
        data[offset_data + 7]= ( (bytes[ offset_byte + 13]>>1) & (0x7f)) | ((bytes[offset_byte + 14] & 0xff)<<7);
			
    }

}

/* This function does NOT reduce its output mod T */
void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N]){
    uint32_t i;
	uint32_t offset_data,offset_byte;

	for(i=0;i<SABER_N/8;i++){

        offset_byte = 7*i;
		offset_data = 8*i;
		data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0x7f));
		data[offset_data + 1]= ( (bytes[ offset_byte + 0 ]>>7) & (0x01)) |  ((bytes[ offset_byte + 1 ] & 0x3f)<<1);		
		data[offset_data + 2]= ( (bytes[ offset_byte + 1 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 2 ] & 0x1f)<<2);
		data[offset_data + 3]= ( (bytes[ offset_byte + 2 ]>>5) & (0x07)) |  ((bytes[ offset_byte + 3 ] & 0x0f)<<3);
		data[offset_data + 4]= ( (bytes[ offset_byte + 3 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 4 ] & 0x07)<<4);
		data[offset_data + 5]= ( (bytes[ offset_byte + 4 ]>>3) & (0x1f)) |  ((bytes[ offset_byte + 5 ] & 0x03)<<5);		
		data[offset_data + 6]= ( (bytes[ offset_byte + 5 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 6 ] & 0x01)<<6);
		data[offset_data + 7]= ( (bytes[ offset_byte + 6 ]>>1) & (0x7f));				
	
		}
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
