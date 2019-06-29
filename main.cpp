#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned __int128 u128;

u128 p(u128 x, u128 y)
{
	u128 res = 1;
	while (y--)
		res *= x;
	return res;
}

void PassGen(u128 num, unsigned char base, unsigned char len,const char*letters,FILE*file)
{
	for (int i = 0; i < len; i++)
	{
		fputc(letters[num % base],file);
		num /= base;
	}
	fputc('\n',file);
}

void create_numbers(int len, char*letters, FILE*file,double file_size, bool progress)
{
	size_t last_size=0,base=strlen(letters);
	u128 max = p(base, len);
	int precent = -1;
	for (u128 x = 0; x < max; x++)
	{
		PassGen(x,base,len,letters,file);
		if (progress && ( precent != (int)((double)x * 100 / max) || (_ftelli64(file)-last_size)/(1024*1024) ))
		{
			precent = (int)((double)x * 100 / max);
			last_size=_ftelli64(file);
			_fseeki64(file,0,SEEK_END);
			printf("\rProgress: %d%% or %.3fGB of %.3fGB", precent,(double)_ftelli64(file)/(1024*1024*1024),file_size);
			_fseeki64(file,last_size,SEEK_SET);
		}
	}
	putchar('\n');
}

int main(int argc, char**argv)
{
	if(argc!=4)
	{
		puts("For usage and more information, check https://github.com/SKC-Developer/Passwords-Generator");
		return 0;
	}

	int len = atoi(argv[1]);
	char*letters = argv[2];
	size_t base=strlen(letters);
	FILE*file=fopen(argv[3], "w");
	if (!file)
	{
		printf("Cannot create file.\n");
		return 0;
	}
	
	printf("Printing ");
	
	//print number of numbers
	int max = 0;
	u128 exp=p(base,len);
	for (; p(10, max) <= exp; max++);
	
	for (int i = 0; i < max; i++)
	{
		putchar('0'+exp/p(10,max-1-i));
		exp%=p(10,max-1-i);
	}
	
	printf(" numbers in base %d to file %s.\nIt will take about %f GBs. Is that OK?\n", letters, argv[3], ((double)p(base, len)*(len + 2)) / (1024 * 1024 * 1024));

	if (getchar() != 'y')
	{
		fclose(file);
		remove(argv[3]);
		return 0;
	}
	getchar();
	printf("Would you like to see the progress?\n");
	

	create_numbers(len, letters, file,((double)p(base, len)*(len + 2)) / (1024 * 1024 * 1024),getchar()=='y');

	fclose(file);
	return 0;
}
