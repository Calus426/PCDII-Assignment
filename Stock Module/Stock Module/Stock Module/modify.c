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

void modifyData(MerchandiseInStock MIS[], int* mDataSize)
{
	int option, selection;
	int matchNumber;
	char mMCode[10];
	char mMName[30];
	double mMPrice;
	int mMStock, mMMinimum, mMReorder;



		displayData(MIS, *mDataSize);
		MerchandiseInStock matchData;

		char  MTSCode[10];

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
		printf("  =====================================================\n\n");

		printf("    Which data you will like to change \n");
		printf("  ======================================\n");
		printf("    1. Code\n");
		printf("    2. Name\n");
		printf("    3. Price\n");
		printf("    4. Stock Quantity\n");
		printf("    5. Minimum Level\n");
		printf("    6. Reorder Quantity\n");
		printf("  ======================================\n\n");
		printf("  Enter your choice :");
		scanf(" %d", &option);

		FILE* MMD;
		MMD = fopen("stock.txt", "w");

		switch (option)
		{
		case 1:
			printf("  Enter New Merchandise Code   :");
			scanf(" %[^\n]", &mMCode);
			strcpy(MIS[matchNumber].MCode, mMCode);

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		case 2:
			printf("  Enter New Merchandise Name   :");
			scanf(" %[^\n]", &mMName);
			strcpy(MIS[matchNumber].MName, mMName);

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		case 3:
			printf("  Enter New Merchandise Price   :");
			scanf(" %lf", &mMPrice);
			MIS[matchNumber].MPrice = mMPrice;

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		case 4:
			printf("  Enter New Merchandise Stock Quantity   :");
			scanf(" %d", &mMStock);
			MIS[matchNumber].MStock = mMStock;

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		case 5:
			printf("  Enter New Merchandise Minimum Level   :");
			scanf(" %d", &mMMinimum);
			MIS[matchNumber].MMinimum = mMMinimum;

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		case 6:
			printf("  Enter New Merchandise Reorder Quantity   :");
			scanf(" %d", &mMReorder);
			MIS[matchNumber].MReorder = mMReorder;
			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder);
			}
			printf("  ==========================================");
			printf("\n    Merchandise data change sucessful...\n");
			printf("  ==========================================");
			break;

		default:

			printf("  ======================================");
			printf("\n    Wrong input please try again....\n");
			printf("  ======================================");
			break;
		}

		fclose(MMD);
		system("pause");
		
}