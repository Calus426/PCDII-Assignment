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

void restockMerchandise(MerchandiseInStock MIS[], int *mDataSize)
{
	char option;
	int  selection, quantity, qReoerder;

	do
	{
		displayData(MIS, *mDataSize);
		MerchandiseInStock matchData;

		char  MTSCode[30];
		int	  matchNumber;

		printf("  Please Enter Merchandise Code : ");
		scanf(" %s", &MTSCode);

		for (int i = 0; i < *mDataSize; i++)
		{
			if ((strcmp(MTSCode, MIS[i].MCode) == 0))
			{
					matchData = MIS[i];
					matchNumber = i;

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
		printf("\n  Restock in :");
		printf("\n              1. Manually ");
		printf("\n              2. Automatically ");
		printf("\n\n  Please enter your selection : ");
		
		scanf(" %d", &selection);

		FILE* RMD;
		RMD = fopen("stock.txt", "w");

		switch (selection)
		{
			case 1:
				printf("  =============================================\n");
				printf("    Enter the restock quantity : ");
				scanf(" %d",  &quantity);
				MIS[matchNumber].MStock += quantity; 
				printf("  =======================\n");
				printf("    Restock sucessfully\n");
				printf("  =======================\n");

				for (int k = 0; k < *mDataSize; k++)
				{
					fprintf(RMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder); 
				}
				break;

			case 2:
				MIS[matchNumber].MStock += MIS[matchNumber].MReorder;
				for (int k = 0; k < *mDataSize; k++)
				{
					fprintf(RMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder); 
				}
				printf("  =======================\n");
				printf("    Restock sucessfully\n");
				printf("  =======================\n");
		 		break;

			default: 
				printf("  ================================\n");
				printf("    Wrong input please try again\n");
				printf("  ================================\n");
				break;
		}

		fclose(RMD);

		printf("  Press 'Y' to continue restock merchandise or 'N' back to menu :");
		scanf(" %c", &option);

	} while (toupper(option) != 'N');
}