#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)

typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;

}MerchandiseInStock;

void modifyData(MerchandiseInStock MIS[], int *mDataSize)
{

}