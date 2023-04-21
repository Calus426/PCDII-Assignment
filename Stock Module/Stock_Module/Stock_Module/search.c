#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)
//Item Code, item description, item price, quantity in stock, minimum level,reorder quantity
//printf("%s %s %.2lf %d %d %d\n", MIS[i].MCode, MIS[i].MName, MIS[i].MPrice, MIS[i].MStock, MIS[i].MMinimum, MIS[i].MReorder);

typedef struct {

	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;



}MerchandiseInStock;



void search(MerchandiseInStock MIS[], int *mDataSize)
{
	char option;
	do
	{
		MerchandiseInStock matchData[30];

		char compare[30], MTSCode[30];
		
		int matchNumber;

		matchNumber = 0;

	
		printf("Please Enter Merchandise Code : ");
		scanf(" %s", &MTSCode);

		compare[0] = MTSCode[0];
		MTSCode[0] = toupper(compare[0]);
		
		for (int i = 0; i < mDataSize; i++)
		{
			if ((strcmp(MTSCode, MIS[i].MCode) == 0))
			{
				matchData[matchNumber] = MIS[i];
				matchNumber++;
			}
		}
		
		printf("                < MERCHANDISE DETAIL >\n");
		printf("=====================================================\n");
		printf("MERCHANDISE CODE             : %s\n", matchData[matchNumber].MCode);
		printf("MERCHANDISE NAME             : %s\n", matchData[matchNumber].MName);
		printf("MERCHANDISE PRICE            : %.2lf\n", matchData[matchNumber].MPrice);
		printf("MERCHANDISE STOCK IN HAND    : %d\n", matchData[matchNumber].MStock);
		printf("MERCHANDISE MINIMUM LEVEL    : %d\n", matchData[matchNumber].MMinimum);
		printf("MERCHANDISE REORDER QUANTITY : %d\n", matchData[matchNumber].MReorder);
		printf("=====================================================\n");
		printf("Press 'Y' to continue search merchandise or 'N' back to menu :");
		scanf("%c", &option);

	} while (toupper(option) != 'N');
	
}