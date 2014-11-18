// One-Time Pad implementation by IvanSarno
/*
input:
	1) number of characters of original message (multiple of 8,possibly complete with random characters)
	2)text file with the message
	3)file with the binary key ( 8 bits per character )
output:
	File encrypted (or decrypted ) called output
*/

#include <stdio.h>
#include <stdlib.h>


void crypt(FILE *textfile, FILE *keyfile, int numchar);
unsigned long long *otpxor(unsigned long long *text, unsigned long long *key, int numint);





 int main(int argc, char **argv)
 {
	 if (argc <4 )
	 {
 		printf("error input\n");
 		return 0;
 	}

 	int num = atoi(argv[1]);
	if (num%8)
		{
			printf("error: number of character must be multiple of 8\ncomplete message and key with random char\n");
			return 0;
		}

 	FILE *text, *key;
 	text = fopen(argv[2],"rb");
 	key = fopen(argv[3],"rb");
	
	if (text && key)
 		crypt(text,key,num/8);
 	else printf("error input\n");

 	return 0;

 }			

unsigned long long *otpxor(unsigned long long *text, unsigned long long *key, int numint)
{
  int i;

  for (i=0; i<numint; i++)
    text[i] = key[i] ^ text[i];
 

  return text;
}


void crypt(FILE *textfile, FILE *keyfile, int num)
{
	unsigned long long *text;
	unsigned long long *key;
	

	text = (unsigned long long *) malloc (num * sizeof (long long));
	key = (unsigned long long *) malloc (num * sizeof (long long));

//read text in binary mode, in blocks of 8 char, like int 
	fread(text, sizeof(long long), num, textfile);
	fread(key, sizeof(long long), num, keyfile);

	text = otpxor(text, key, num);

	FILE *out = fopen("output", "wb");

	fwrite(text, sizeof(long long), num, out);

	fclose(textfile);
	fclose(keyfile);
	fclose(out);
}
