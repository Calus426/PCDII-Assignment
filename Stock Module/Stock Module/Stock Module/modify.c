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
typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder; 

}ModifyMerchandiseData;

ModifyMerchandiseData mmd;

void modifyData(MerchandiseInStock MIS[], int *mDataSize)
{
	int option;
	

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
	printf("    Enter your choice :");
	scanf(" %d", &option);

	switch (option)
	{
	case 1 :
			printf("Enter New Merchandise Code   :");
			scanf(" %[^\n]", &mmd.MCode);
		

			break;

	case 2:

			break;

	case 3:

			break;

	case 4:

			break;

	case 5:

			break;

	case 6:

			break;
	
	default:

		printf("  ====================================\n\n");
		printf("    Wrong input please try again....");
		printf("  ====================================\n\n");
		break;
	}
	

}