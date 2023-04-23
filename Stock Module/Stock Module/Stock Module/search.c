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



void search(MerchandiseInStock MIS[], int mDataSize)
{
	char option;
	do
	{
		displayData(MIS, mDataSize);
		MerchandiseInStock matchData;

		char  MTSCode[30];

		printf("  Please Enter Merchandise Code : ");
		scanf(" %s", &MTSCode);


		for (int i = 0; i < mDataSize; i++)
		{
			if ((strcmp(MTSCode, MIS[i].MCode) == 0))
			{
				matchData = MIS[i];
				
			}
		}

		printf("\n\n  =====================================================\n");
		printf("                  < MERCHANDISE DETAIL >\n");
		printf("  =====================================================\n");
		printf("  MERCHANDISE CODE             : %s\n", matchData.MCode);
		printf("  MERCHANDISE NAME             : %s\n", matchData.MName);
		printf("  MERCHANDISE PRICE (RM)       : %.2lf\n", matchData.MPrice);
		printf("  MERCHANDISE STOCK IN HAND    : %d\n", matchData.MStock);
		printf("  MERCHANDISE MINIMUM LEVEL    : %d\n", matchData.MMinimum);
		printf("  MERCHANDISE REORDER QUANTITY : %d\n", matchData.MReorder);
		printf("  =====================================================\n");
		printf("  Press 'Y' to continue to search merchandise or 'N' back to menu :");
		scanf(" %c", &option);

	} while (toupper(option) != 'N');

}
