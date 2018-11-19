#include <sys/ptrace.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>



void boom ()
{
	int i;
	int boom[6]={0x42,0X4f,0X4f,0X4d,0X20,0X21};

	for (i=0; i < 6 ; i++)
		printf("%c", toascii(boom[i]));

	printf("\n");
	exit(1);
}

void func_cipher42 (int *altered, int *word, int *flag_xor)
{
	int i;
	*flag_xor=123; //set flag for xor loop
printf("\n");
	// func_cipher42 on word[]
	for (i=0; i < 30 ; i++)
		altered[i]=word[i]^0x42;
}

void func_cipher13 (int *altered)
{
	int i=0;
	for (i=0; i < 30 ; i++)
		altered[i]=altered[i] - 13;
}

void func_cipher6 (int *altered)
{
	int i=0;
	for (i=0; i < 30 ; i++)
		altered[i]=altered[i] - (i*6);
}

void nuke(int *junk)
{
	int i=0;
	for (i=0; i < 11; i++)
		junk[i]=toascii(junk[i]) + 2;
}

void apoptosis(int *junk, int *altered)
{
	int i=0;
	junk[i]=altered[i]%88;
}

int main ()
{
	int checkFlag_xor=123;
	int flag_xor=0;
	int i,j,k;

	int word[30]={0x23,0x39,0x3c,0x7d,0xc5,0xd8,0xdc,0xdb,0x1f,0xe9,0xe8,0x80,0x37,0xff,0x84,0x8e,0x99,0xd1,0x9f,0xa6,0xa9,0x142,0x146,0xbe,0x143,0x81,0x88,0x8d,0xad,0xa6};
	int *junk;
	junk=malloc(sizeof(int) *11);
	int *altered;
	altered=malloc(sizeof(int) *30);

	// messages
	int planted[26]={0x54,0X68,0X65,0X20,0X62,0X6f,0X6d,0X62,0X20,0X68,0X61,0X73,0X20,0X62,0X65,0X65,0X6e,0X20,0X70,0X6c,0X61,0X6e,0X74,0X65,0X64,0X2e};
	int debugg[24]={0x49,0X20,0X73,0X65,0X65,0X20,0X79,0X6f,0X75,0X20,0X64,0X65,0X62,0X75,0X67,0X67,0X69,0X6e,0X67,0X20,0X6d,0X65,0X20,0X21};


	// The bomb has been planted
	for (i=0; i < 26 ; i++)
		printf("%c", toascii(planted[i]));
	printf("\n");

	// patch to != to pass the loop
	while (isdigit(checkFlag_xor) == 0)
			boom();

	// anti debugger
	 if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
  {
		for (i=0; i < 24 ; i++)
			printf("%c", toascii(debugg[i]));
		printf("\n");

		boom();
  }

	// patch to != to enter func_cipher42 alteration
	if ( checkFlag_xor == 123 )
		boom();
	else
	{
	// func_cipher42 alteration loop
		func_cipher42(altered,word,&flag_xor);
	}

	// check if passed in loop func_cipher42. If not, boom
	if (checkFlag_xor != flag_xor)
		{
			boom();
		}
	else
	{
		apoptosis(junk,altered);
	}

	// left-shift13 on altered[]
	func_cipher13(altered);

	// patch to pass -1 func_cipher6 alteration case
	int size;
	size=isalpha(i);

	switch(size)
	{
		case -1:
			// func_cipher6 alteration loop
			func_cipher6(altered);
			break;
		case 0:
			boom();
			break;
		case 1024:
			// junk func_cipher42
			func_cipher42(altered,word,&flag_xor);
			break;
		}

	// check final int
	if (altered[2] == altered[14])
	{
		for (i=0; i < 30 ; i++)
			printf("%c", toascii(altered[i]));
		printf("\n");

		exit(1);
	}
	else
		boom();

	return 0;
}
