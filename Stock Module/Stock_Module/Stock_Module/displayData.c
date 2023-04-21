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

void displayData(const MerchandiseInStock MIS[], int mDataSize)
{

	for (int i = 0; i < mDataSize; i++)
	{

		printf("%s %s %.2lf %d %d %d\n", MIS[i].MCode, MIS[i].MName, MIS[i].MPrice, MIS[i].MStock, MIS[i].MMinimum, MIS[i].MReorder);

	}

}