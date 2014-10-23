// One-Time Pad implementation by IvanSarno
/* input:
			1)number of char of message, must be %8=0
			2) c for criptation or d for decriptation
			3) message in text file 
			4) key in binary file
	output:
			criptomessage in text file
*/


#include <stdio.h>
#include <stdlib.h>


void criptation(FILE *textfile, FILE *keyfile, int numchar);
void decriptation(FILE *textfile, FILE *keyfile, int numdigit);
char *otpcripto(unsigned int *text, unsigned int *key, int numint);





 int main(int argc, char **argv)
 {
	 if (argc <3 )
	 {
 		printf("error input");
 		return 0;
 	}
 	FILE *text, *key;
 	text = fopen(argv[3],"r");
 	key = fopen(argv[4],"rb");
	int num;
	char comand;
	sscanf(argv[2],"%c", &comand);
	sscanf(argv[1],"%d", &num);

 	if(comand == 'c')
 		criptation(text,key,num);
 	else if (comand == 'd')
 			 decriptation(text,key,num);
 			else printf("error input");

 	return 0;

 }			

 char *otpcripto(unsigned int *text, unsigned int *key, int numint)
{
  int i;

  for (i=0; i<numint; i++)
    text[i] = key[i] ^ text[i];
 

  return (char *)text;
}


void criptation(FILE *textfile, FILE *keyfile, int numchar)
{
	int i;
	char *text;
	unsigned int *key;
	int numint = numchar/8;

	text = (char *) malloc (numchar * sizeof (char));
	key = (unsigned int *) malloc (numint * sizeof (int));

	for (i=0; i<numchar; i++)
		text[i] = fgetc(textfile);
	
	fread(key, 64, numint, keyfile);

	text = otpcripto((unsigned int *)text, key, numint);

	FILE *out = fopen("output", "w");

	for(i=0; i<numchar; i++)
		fprintf(out, "%03d", text[i]); 

	fclose(textfile);
	fclose(keyfile);
	fclose(out);
}


void decriptation(FILE *textfile, FILE *keyfile, int numdigit)
{
	int i,j;
	char *text;
	unsigned int *key;
	int numchar = numdigit/3;
	int numint = numchar/8;

	text = (char *) malloc (numchar * sizeof (char));
	key = (unsigned int *) malloc (numint * sizeof (int));
	char *buffer = (char *) malloc (4*numchar * sizeof (char));

	for(i=0,j=0;i<numchar;i++,j+=4)
	{
		buffer[j] = fgetc(textfile);
		buffer[j+1] = fgetc(textfile);
		buffer[j+2] = fgetc(textfile);
		buffer[j+3] = ' ';
	}
	

	for (i=0; i<numchar; i++)
		{
			sscanf(buffer + (4*i),"%d",&j);
			text[i] = (char) j;
		}
		

	free(buffer);
	
	fread(key, 64, numint, keyfile);

	text = otpcripto((unsigned int *)text, key, numint);

	FILE *out = fopen("output", "w");

	for(i=0; i<numchar; i++)
		fputc(text[i],out);

	fclose(textfile);
	fclose(keyfile);
	fclose(out);
}
