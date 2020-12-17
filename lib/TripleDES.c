#include "TripleDES.h"

/* Initialize replacement IP */
int IP[64] = { 57,49,41,33,25,17,9, 1,
	       59,51,43,35,27,19,11,3,
	       61,53,45,37,29,21,13,5,
	       63,55,47,39,31,23,15,7,
	       56,48,40,32,24,16,8, 0,
	       58,50,42,34,26,18,10,2,
	       60,52,44,36,28,20,12,4,
	       62,54,46,38,30,22,14,6 };

/* Initialize inverse replacement IP */
int IP_1[64] = { 39,7,47,15,55,23,63,31,
		 38,6,46,14,54,22,62,30,
		 37,5,45,13,53,21,61,29,
		 36,4,44,12,52,20,60,28,
		 35,3,43,11,51,19,59,27,
		 34,2,42,10,50,18,58,26,
		 33,1,41,9, 49,17,57,25,
		 32,0,40,8, 48,16,56,24 };

/* Extend the operation */
int E[48] = { 31,0, 1, 2, 3, 4,
	      3, 4, 5, 6, 7, 8,
	      7, 8, 9, 10,11,12,
	      11,12,13,14,15,16,
	      15,16,17,18,19,20,
	      19,20,21,22,23,24,
	      23,24,25,26,27,28,
	      27,28,29,30,31,0 };

/* Replacement operation */
int P[32] = { 15,6, 19,20,28,11,27,16,
	      0, 14,22,25,4, 17,30,9,
	      1, 7, 23,13,31,26,2, 8,
	      18,12,29,5, 21,10,3, 24 };

/* S Box */
int S[8][4][16] =
{   //S1
   {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
	//S2
   {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
  	//S3
   {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
	//S4
   {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
	//S5
   {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
	//S6
   {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
	//S7
   {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
    {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
    {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
    {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
	//S8
   {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
    {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
    {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
    {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}} };

/* Replacement selection 1 */
int PC_1[56] = { 56,48,40,32,24,16,8,
                 0, 57,49,41,33,25,17,
	         9, 1, 58,50,42,34,26,
	         18,10,2, 59,51,43,35,
	         62,54,46,38,30,22,14,
		 6, 61,53,45,37,29,21,
	         13,5, 60,52,44,36,28,
                 20,12,4, 27,19,11,3 };

/* Replacement selection 2 */
int PC_2[48] = { 13,16,10,23,0, 4, 2, 27,
	         14,5, 20,9, 22,18,11,3,
	         25,7, 15,6, 26,19,12,1,
	         40,51,30,36,46,54,29,39,
		 50,44,32,46,43,48,38,55,
		 33,52,45,41,49,35,28,31 };

/* Left shift number of times */
int left[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

void byteToBit(uint8_t ch, uint8_t bit[8]) {
	int cnt;
	for (cnt = 0; cnt < 8; cnt++) {
		*(bit + cnt) = (ch >> cnt) & 1;
	}
}

void uchar8ToBit64(uint8_t* ch, uint8_t bit[64]) {
	int cnt;
	for (cnt = 0; cnt < 8; cnt++) {
		byteToBit(*(ch + cnt), bit + (cnt << 3));
	}
}

void bitToByte(uint8_t bit[8], uint8_t* ch) {
	int cnt;
	for (cnt = 0; cnt < 8; cnt++) {
		*ch |= *(bit + cnt) << cnt;
	}
}

void bit64ToUchar8(uint8_t bit[64], uint8_t ch[8]) {
	int cnt;
	memset(ch, 0, 8);
	for (cnt = 0; cnt < 8; cnt++) {
		bitToByte(bit + (cnt << 3), ch + cnt);
	}
}

void transformPC1(uint8_t key[64], uint8_t tempbts[56]) {
	int cnt;
	for (cnt = 0; cnt < 56; cnt++) {
		tempbts[cnt] = key[PC_1[cnt]];
	}
}

void ROL(uint8_t data[56], uint8_t time) {
	uint8_t temp[56];

	memcpy(temp, data, time);
	memcpy(temp + time, data + 28, time);	

	//Left 28 ROL
	memcpy(data, data + time, 28 - time);
	memcpy(data + 28 - time, temp, time);

	//Right 28 ROL
	memcpy(data + 28, data + 28 + time, 28 - time);
	memcpy(data + 56 - time, temp + time, time);
}

void transformPC2(uint8_t key[56], uint8_t tempbts[48]) {
	int cnt;
	for (cnt = 0; cnt < 48; cnt++) {
		tempbts[cnt] = key[PC_2[cnt]];
	}
}

void makeBitSubKeys(uint8_t key[64], uint8_t subKeys[16][48]) {
	uint8_t temp[56];
	int cnt;
	transformPC1(key, temp);
	for (cnt = 0; cnt < 16; cnt++) {
		ROL(temp, left[cnt]);
		transformPC2(temp, subKeys[cnt]);
	}
}

void transformIp(uint8_t data[64]) {
	int cnt;
	uint8_t temp[64];
	for (cnt = 0; cnt < 64; cnt++) {
		temp[cnt] = data[IP[cnt]];
	}
	memcpy(data, temp, 64);
}

void transformIp_1(uint8_t data[64]) {
	int cnt;
	uint8_t temp[64];
	for (cnt = 0; cnt < 64; cnt++) {
		temp[cnt] = data[IP_1[cnt]];
	}
	memcpy(data, temp, 64);
}

void transformE(uint8_t data[48]) {
	int cnt;
	uint8_t temp[48];
	for (cnt = 0; cnt < 48; cnt++) {
		temp[cnt] = data[E[cnt]];
	}
	memcpy(data, temp, 48);
}

void transformP(uint8_t data[32]) {
	int cnt;
	uint8_t temp[32];
	for (cnt = 0; cnt < 32; cnt++) {
		temp[cnt] = data[P[cnt]];
	}
	memcpy(data, temp, 32);
}

void XOR(uint8_t r[48], uint8_t l[48], int count) {
	int cnt;
	for (cnt = 0; cnt < count; cnt++) {
		r[cnt] ^= l[cnt];
	}
}

void Sbox(uint8_t data[48]) {
	int cnt;
	int line, row, output;
	int cur1, cur2;
	for (cnt = 0; cnt < 8; cnt++) {
		cur1 = cnt * 6;   
		cur2 = cnt << 2;

		line = (data[cur1] << 1) + data[cur1 + 5];
		row = (data[cur1 + 1] << 3) + (data[cur1 + 2] << 2) + (data[cur1 + 3] << 1) + data[cur1 + 4];
		output = S[cnt][line][row];

		data[cur2] = (output & 0X08) >> 3;
		data[cur2 + 1] = (output & 0X04) >> 2;
		data[cur2 + 2] = (output & 0X02) >> 1;
		data[cur2 + 3] = output & 0x01;
	}
}

void swap(uint8_t left[32], uint8_t right[32]) {
	uint8_t temp[32];
	memcpy(temp, left, 32);
	memcpy(left, right, 32);
	memcpy(right, temp, 32);
}

void encryptBlock(uint8_t plainBlock[8], uint8_t subKeys[16][48]) {
	uint8_t plainBits[64];
	uint8_t copyRight[48];
	int cnt;

	uchar8ToBit64(plainBlock, plainBits);
	transformIp(plainBits);

	for (cnt = 0; cnt < 16; cnt++) {
		memcpy(copyRight, plainBits + 32, 32);
		transformE(copyRight);
		XOR(copyRight, subKeys[cnt], 48);
		Sbox(copyRight);
		transformP(copyRight);
		XOR(plainBits, copyRight, 32);
		if (cnt != 15) {
			swap(plainBits, plainBits + 32);
		}
	}
	transformIp_1(plainBits);
	bit64ToUchar8(plainBits, plainBlock);
}

void decryptBlock(uint8_t cipherBlock[8], uint8_t subKeys[16][48]) {
	uint8_t cipherBits[64];
	uint8_t copyRight[48];
	int cnt;

	uchar8ToBit64(cipherBlock, cipherBits);
	transformIp(cipherBits);

	for (cnt = 15; cnt >= 0; cnt--) {
		memcpy(copyRight, cipherBits + 32, 32);
		transformE(copyRight);
		XOR(copyRight, subKeys[cnt], 48);
		Sbox(copyRight);
		transformP(copyRight);
		XOR(cipherBits, copyRight, 32);
		if (cnt != 0) {
			swap(cipherBits, cipherBits + 32);
		}
	}
	transformIp_1(cipherBits);
	bit64ToUchar8(cipherBits, cipherBlock);
}

void encryptionTripleDes(uint8_t* plaintext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3) {
	uint8_t bitKey1[64];
	uint8_t bitKey2[64];
	uint8_t bitKey3[64];
	uint8_t subBitKey1[16][48];
	uint8_t subBitKey2[16][48];
	uint8_t subBitKey3[16][48];

	int i;
	int times = len / 8;

	uchar8ToBit64(key1, bitKey1);
	uchar8ToBit64(key2, bitKey2);
	uchar8ToBit64(key2, bitKey3);

	makeBitSubKeys(bitKey1, subBitKey1);
	makeBitSubKeys(bitKey2, subBitKey2);
	makeBitSubKeys(bitKey3, subBitKey3);

	for (i = 0; i < times; i++) {
		encryptBlock(plaintext + i * 8, subBitKey1);
		decryptBlock(plaintext + i * 8, subBitKey2);
		encryptBlock(plaintext + i * 8, subBitKey3);
	}
}

void decryptionTripleDes(uint8_t* ciphertext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3) {
	uint8_t bitKey1[64];
	uint8_t bitKey2[64];
	uint8_t bitKey3[64];
	uint8_t subBitKey1[16][48];
	uint8_t subBitKey2[16][48];
	uint8_t subBitKey3[16][48];

	int i;
	int times = len / 8;

	uchar8ToBit64(key1, bitKey1);
	uchar8ToBit64(key2, bitKey2);
	uchar8ToBit64(key2, bitKey3);

	makeBitSubKeys(bitKey1, subBitKey1);
	makeBitSubKeys(bitKey2, subBitKey2);
	makeBitSubKeys(bitKey3, subBitKey3);

	for (i = 0; i < times; i++) {
		decryptBlock(ciphertext + i * 8, subBitKey1);
		encryptBlock(ciphertext + i * 8, subBitKey2);
		decryptBlock(ciphertext + i * 8, subBitKey3);
	}
}
