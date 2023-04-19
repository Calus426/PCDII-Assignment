#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)
typedef struct {

	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;



}MerchandiseInStock;


void merchandiseData(MerchandiseInStock MIS[], int *mDataSize)
{
	FILE* MD;
	MD = fopen("stock.txt", "r");

	if (MD == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}

	*mDataSize = 0;

	while ()
	{
		(*mDataSize)++;
	}


	fclose(MD);
}

