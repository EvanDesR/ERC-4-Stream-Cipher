#include "cryptlib.h"



//INITALIZATION FUNCTION
 rc4* rc4Init(int8* key, int16 sizeOfKey) //returns rc4 struct pointer, and KSA
{
	rc4* p;
	p = malloc(sizeof(rc4));

	if (p == NULL)
	{
		//assert_perror(errno);
		printf("assert_perror(errno);");
	}


	for (int i = 0; i < 256; i++) //zero everything out
	{
		p->s[i] = 0;
	}
	p->i = p->j = p->k = 0;
	int8 keyDerivedArrayIndexValue = 0, tmp2 = 0;

	
	for (int i = (int)p->i; i < 256; i++, p->i = (int8)i) //iterate through all 255 elements in s array (it looks weird cuz array is of int8 type, which is defined as char)
	{
		p->s[p->i] = p->i; //For all 255 elements of char array s, put the respective index value as the char code.
	}

	for (int iterator = (int)p->i; iterator < 256; iterator++, p->i = (int8)iterator)
	{
		keyDerivedArrayIndexValue = ((p->j + p->s[p->i]) + (key[p->i % sizeOfKey])); //char tmp1= j+s + key[index] (modulo allows for wrap around, meaning message can be longer than key)
		p->j = keyDerivedArrayIndexValue % 256; //j is given a new value derived from j, s[i] and key[i]
		tmp2 = p->s[p->i]; //tmp2 holds copy of current s[i] value

		//every for loop iteration will produce a keyDerivedArrayIndexValue. The element pointed to by iterator will swap values with keyDerivedArrayIndexValue.
		//This produces our key stream
		p->s[p->i] = p->s[p->j]; //s[i] now holds value at s[j]. (Key derived shuffling of the array)
		p->s[p->j] = tmp2; //s[j] now holds value initially held at s[i].

		//s[i] and s[j] have had their values swapped

	}

	p->i = p->j = 0;

	return p;
}
//END OF INITIALIZATION FUNCTION

int8 rc4Byte(rc4 *p) //PRGA
{
	int16 tmp1, tmp2;

	//iterator +1
	//shuffle s[i] and s[j] further
	//byte = s[ ( s[i] + s[j] ) % 256 ]


		p->i = (p->i + 1) % 256; //iterator +1
		p->j = (p->j + p->s[p->i]) % 256; // j = j+i %256

		tmp1 = p->s[p->j]; //tmp1 holding s[j]
		p->s[p->j] = p->s[p->i]; //s[j] now holding s[i]
		p->s[p->i] = tmp1; // s[i] now holding s[j]
		tmp1 = (p->s[p->i] + p->s[p->j]) % 256;

		p->k = p->s[tmp1]; //output byte is created.

		return p->k;
}

 int8 *rc4Encrypt(rc4 *p, int8 *target,int16 sizeOfTarget)
{
	int8* cipherText;
	cipherText = (int8*)malloc(sizeOfTarget+1);

	if (!cipherText)
	{
		printf("assert_perror(errno)");
	}
	
	for (int x = 0; x <= sizeOfTarget; x++)
	{
		cipherText[x] = (target[x] ^ rc4Byte(p)); //XOR cleartext byte with rc4 keystream byte


	}
	return cipherText;
}