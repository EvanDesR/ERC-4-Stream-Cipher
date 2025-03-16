#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>



#define export __attribute__((visibility("default")))
#define rc4decrypt(p,x,y) rc4Encrypt(p,x,y) //calls to rc4decryt just get forwarded to rc4ecrnypt
#define rc4Uninit(x) free(x);

typedef struct s_rivestCrypt4 rc4;

//type definitions
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_rivestCrypt4 // to hold internal state of encryption engine
{ //informed by the rc4 wiki page
	int8 i, j, k; //j and i are counters.k holds byte
	int8 s[256]; 


};

rc4* rc4Init(int8* key, int16 sizeOfKey);

int8 rc4Byte(rc4* p);

int8* rc4Encrypt(rc4 *p,int8* stringToEncrypt, int16 sizeOfString);