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
	
	printf("     < MERCHANDISE CODE & NAME >\n");
	printf("=====================================\n");
	for (int i = 0; i < mDataSize; i++)
	{
		int number = i + 1;

		printf("  %d. %s     %s\n", number, MIS[i].MCode, MIS[i].MName);

	}
	printf("=====================================\n\n");
}