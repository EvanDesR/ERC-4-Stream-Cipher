#include "cryptlib.h"

#define F fflush(stdout)


int main(void);


//hex output

void printbin(int8* text, int16 sizeOfText)
{
	int32 i;
	int8* pointer;

	assert(sizeOfText > 0); //assert function checks if predicate is true. If false, entire program halts.

	for (i = sizeOfText, pointer = text; i > 0; i--, pointer++) //while i is larger than 0. increase p per iteration
	{
		if (! (i % 2)) //if 
			printf(" ");
		printf("%.02x", *pointer);
		
	}
	printf("\n");

	return;
}

int main()
{
	rc4 *rc4;
	int16 sizeOfKey, sizeOfText;
	char* key, * target;
	int8* encrypted, * decrypted;
	
	key = "Key_HERE"; //create real encryption key when we use it (8Bit - 2048 Bits according to rc4 standard
	sizeOfKey = strlen(key);
	target =  "Shall I compare thee to a summer's day?";
	sizeOfText = strlen(target);
	printf("input: %s \n", target);
	rc4 = rc4Init(key, sizeOfKey);
	printf("key \n");
	printbin(rc4->s, sizeOfKey);
	F;
	encrypted = rc4Encrypt(rc4, target, sizeOfText);

	printf("encrypted version \n");
	printbin(encrypted, sizeOfText);
	F;

	rc4Uninit(rc4);
	printf("intializing rc4"); F;

	rc4 = rc4Init(key, sizeOfKey);

	decrypted = rc4decrypt(rc4, encrypted, sizeOfText);
	
	printf("Decrypted -> %s \n",decrypted);



	



}