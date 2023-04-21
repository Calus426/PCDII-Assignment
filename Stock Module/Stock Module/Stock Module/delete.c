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


void deleteData(MerchandiseInStock MIS[], int *mDataSize)
{
	int deleteNum;
	char option, deleteOption;
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
				deleteNum = i;
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
		printf("  =====================================================\n\n");

		printf("Press 'Y' if you want to delete this merchandise data :");
		scanf(" %c", &deleteOption);

		if (toupper(deleteOption) == 'Y')
		{
			for (int j = deleteNum; j < *mDataSize; j++)
			{
				MIS[j] = MIS[j + 1];
			}

			(*mDataSize)--;

			FILE* DMD;
			DMD = fopen("stock.txt", "w");

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(DMD, "%s|%s|%.2lf|%d|%d|%d|", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}

			fclose(DMD);
			printf("  \nMerchandise Data has deleted sucessfully\n");

		}

		printf("  Press 'Y' to continue to delete merchandise data or 'N' back to menu :");
		scanf(" %c", &option);

	} while (toupper(option) != 'N');


}