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
	MerchandiseInStock matchData[2];

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
		


	
}