#include <stdio.h>
#include <stdlib.h>

typedef unsigned __int128 u128;

u128 p(u128 x, u128 y)
{
	u128 res = 1;
	while (y--)
		res *= x;
	return res;
}

void PrintBase(u128 num, int len, unsigned char base, FILE*file)
{
	if (base > 62)return;
	char c;
	u128 exp;
	for (u128 l = 0; l < len; l++)
	{
		exp = p(base, len - l - 1);
		c = num / exp;

		if (c >= 10 && c <= 35)
			fputc(c - 10 + 'A', file);
		else if (c >= 36 && c <= 62)
			fputc(c - 36 + 'a', file);
		else
			fputc(c + '0', file);
		num = num % exp;
	}
	fputc('\n', file);
}

void create_numbers(int len, unsigned char letters, FILE*file,double file_size, bool progress)
{
	u128 max = p(letters, len);
	int precent = -1;
	size_t last_size=0;
	for (u128 x = 0; x < max; x++)
	{
		PrintBase(x, len, letters, file);
		if (progress && ( precent != (int)((double)x * 100 / max) || (ftell(file)-last_size)/(1024*1024) ))
		{
			precent = (int)((double)x * 100 / max);
			last_size=ftell(file);
			fseek(file,0,SEEK_END);
			printf("\rProgress: %d%% or %.3fGB of %.3fGB", precent,(double)ftell(file)/(1024*1024*1024),file_size);
			fseek(file,last_size,SEEK_SET);
		}
	}
	putchar('\n');
}

int main(int argc, char**argv)
{
	if (argc > 1 && (argv[1][0] == '?' || argv[1][1] == '?'))
	{
		printf("pass_gen number_length base output_path\n");
	}

	if (argc < 4)return 0;

	int len = atoi(argv[1]);
	char letters = atoi(argv[2]);
	FILE*file=fopen(argv[3], "w");
	if (!file)
	{
		printf("Cannot create file.\n");
		return 0;
	}
	
	printf("Printing ");
	
	//print number of numbers
	u128 exp=p(letters, len);
	int max = 0;
	for (; p(10, max) <= exp; max++);
	
	for (int i = 0; i < max; i++)
	{
		putchar('0'+exp/p(10,max-1-i));
		exp%=p(10,max-1-i);
	}
	
	printf(" numbers in base %d to file %s.\nIt will take about %f GBs. Is that OK?\n", letters, argv[3], ((double)p(letters, len)*(len + 2)) / (1024 * 1024 * 1024));

	if (getchar() != 'y')
	{
		fclose(file);
		remove(argv[3]);
		return 0;
	}
	getchar();
	printf("Would you like to see the progress?\n");
	

	create_numbers(len, letters, file,((double)p(letters, len)*(len + 2)) / (1024 * 1024 * 1024),getchar()=='y');

	fclose(file);
	return 0;
}
