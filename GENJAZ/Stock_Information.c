#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)

typedef struct
{
	int day, month, year;

}Date;

typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;
	Date reorderDate;

}MerchandiseInStock;

typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;
	Date reorderDate;

}NewMerchandise;

void addNew();
void search(MerchandiseInStock MIS[], int mDataSize);
void merchandiseData(MerchandiseInStock MIS[], int* mDataSize);
void displayData(MerchandiseInStock MIS[], int mDataSize);
void deleteData(MerchandiseInStock MIS[], int* mDataSize);
void modifyData(MerchandiseInStock MIS[], int* mDataSize);
void restockMerchandise(MerchandiseInStock MIS[], int* mDataSize);
void merchandiseList(MerchandiseInStock MIS[], int mDataSize);

void stockModule() {

	MerchandiseInStock MIS[100];
	int mDataSize;
	int  mChoice;

	do {
		merchandiseData(MIS, &mDataSize);
		system("cls");

		printf("\n\n  ================================\n"
			"      What is Your Next Move??\n"
			"  ================================\n"
			"   1. Add a new Merchandise\n"
			"   2. Modify Merchandise Detail\n"
			"   3. Search Merchandise Detail\n"
			"   4. Delete Merchandise Data\n"
			"   5. Restock Merchandise\n"
			"   6. Merchandise Detail\n"
			"   7. Exit\n"
			"\n\n"
			"  Enter your choice  : ");
		scanf(" %d", &mChoice);

		printf("\n\n");

		switch (mChoice)
		{
		case 1:
			addNew();
			break;

		case 2:
			modifyData(MIS, &mDataSize);

			break;

		case 3:
			search(MIS, mDataSize);
			break;



		case 4:
			deleteData(MIS, &mDataSize);
			break;

		case 5:
			restockMerchandise(MIS, &mDataSize);
			break;


		case 6:
			merchandiseList(MIS, mDataSize);
			break;

		case 7:
			printf("  You are exiting\n\n");
			break;

		default:

			printf("Unknow Value Please Try Agian\n"
				"============================================================================================================");


		}

	} while (mChoice != 7);

	system("pause");

}

void merchandiseData(MerchandiseInStock MIS[], int* mDataSize)
{
	FILE* MD;
	MD = fopen("stock.txt", "r");

	if (MD == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}

	*mDataSize = 0;

	int i = 0;
	while (fscanf(MD, "%[^|]|%[^|]|%lf|%d|%d|%d|%d-%d-%d|\n", &MIS[i].MCode, &MIS[i].MName, &MIS[i].MPrice, &MIS[i].MStock, &MIS[i].MMinimum, &MIS[i].MReorder, &MIS[i].reorderDate.day, &MIS[i].reorderDate.month, &MIS[i].reorderDate.year) != EOF)
	{

		i++;
		*mDataSize = i;
	}


	fclose(MD);
}

void addNew()
{
	NewMerchandise NM;
	FILE* AN;
	AN = fopen("stock.txt", "a");

	if (AN == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}
	char option;
	do
	{
		printf("1. Enter New Merchandise Code              :");
		scanf("%s", &NM.MCode);

		printf("2. Enter New Merchandise Name              :");
		scanf(" %[^\n]", &NM.MName);

		printf("3. Enter New Merchandise Price             :");
		scanf(" %lf", &NM.MPrice);

		printf("4. Enter New Merchandise Stock             :");
		scanf(" %d", &NM.MStock);

		printf("5. Enter New Merchandise Minimum Level     :");
		scanf(" %d", &NM.MMinimum);

		printf("6. Enter New Merchandise Reorder Quantity  :");
		scanf(" %d", &NM.MReorder);

		NM.reorderDate.day = 0;
		NM.reorderDate.month = 0;
		NM.reorderDate.year = 0;

		fprintf(AN, "\n%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|", NM.MCode, NM.MName, NM.MPrice, NM.MStock, NM.MMinimum, NM.MReorder, NM.reorderDate.day, NM.reorderDate.month, NM.reorderDate.year);

		printf("\nAny New Merchandise More ? (if Yes press Y or No press N) :");
		scanf(" %c", &option);


	} while (toupper(option) != 'N');

	printf("New merchandise saved \n");
	system("pause");

	fclose(AN);
}

void modifyData(MerchandiseInStock MIS[], int* mDataSize)
{
	int option, selection;
	int matchNumber;
	char mMCode[10];
	char mMName[30];
	double mMPrice;
	int mMStock, mMMinimum, mMReorder, rDay, rMonth, rYear;



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
	printf("  MERCHANDISE LAST REORDER DATE: %d-%d-%d\n", matchData.reorderDate.day, matchData.reorderDate.month, matchData.reorderDate.year);
	printf("  =====================================================\n\n");

	printf("    Which data you will like to change \n");
	printf("  ======================================\n");
	printf("    1. Code\n");
	printf("    2. Name\n");
	printf("    3. Price\n");
	printf("    4. Stock Quantity\n");
	printf("    5. Minimum Level\n");
	printf("    6. Reorder Quantity\n");
	printf("    7. Last Reorder Date\n");
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
		}
		printf("  ==========================================");
		printf("\n    Merchandise data change sucessful...\n");
		printf("  ==========================================");
		break;

	case 7:
		printf("  Enter New Merchandise Last Reorder Date (dd mm yy):");
		scanf(" %d %d %d", &rDay, &rMonth, &rYear);
		MIS[matchNumber].reorderDate.day = rDay;
		MIS[matchNumber].reorderDate.month = rMonth;
		MIS[matchNumber].reorderDate.year = rYear;

		for (int k = 0; k < *mDataSize; k++)
		{
			fprintf(MMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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
		printf("  MERCHANDISE LAST REORDER DATE: %d-%d-%d\n", matchData.reorderDate.day, matchData.reorderDate.month, matchData.reorderDate.year);
		printf("  =====================================================\n\n");
		printf("  Press 'Y' to continue to search merchandise or 'N' back to menu :");
		scanf(" %c", &option);

	} while (toupper(option) != 'N');

}

void deleteData(MerchandiseInStock MIS[], int* mDataSize)
{
	int deleteNum;
	char option, deleteOption;


	do
	{
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
		printf("  MERCHANDISE LAST REORDER DATE: %d-%d-%d\n", matchData.reorderDate.day, matchData.reorderDate.month, matchData.reorderDate.year);
		printf("  =====================================================\n\n");

		printf("Press 'Y' if you want to delete this merchandise data : ");
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
				fprintf(DMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
			}



			fclose(DMD);
			printf("  ============================================\n");
			printf("    Merchandise Data has deleted sucessfully\n");
			printf("  ============================================\n");

		}
		else if (toupper(deleteOption) == 'N')
		{
			printf("  ======================\n");
			printf("    Command has cancel\n");
			printf("  ======================\n");
		}
		else
		{
			printf("  =============================================================================\n");
			printf("    Wrong input!!! Please try again... ( Nothing change on merchandise data )\n");
			printf("  =============================================================================");
		}

		printf("\n  Press 'Y' to continue to delete other merchandise data or 'N' back to menu :");
		scanf(" %c", &option);

	} while (toupper(option) != 'N');


}

void restockMerchandise(MerchandiseInStock MIS[], int* mDataSize)
{
	char option;
	int  selection, quantity, qReoerder, rDay, rMonth, rYear;

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
		printf("  MERCHANDISE LAST REORDER DATE: %d-%d-%d\n", matchData.reorderDate.day, matchData.reorderDate.month, matchData.reorderDate.year);
		printf("  =====================================================\n\n");
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
			scanf(" %d", &quantity);
			printf("    Enter restock date (dd mm yy): ");
			scanf(" %d %d %d", &rDay, &rMonth, &rYear);

			MIS[matchNumber].MStock += quantity;
			printf("  =======================\n");
			printf("    Restock sucessfully\n");
			printf("  =======================\n");

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(RMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
			}
			break;

		case 2:
			printf("  =============================================\n");
			printf("    Enter restock date (dd mm yy): ");
			scanf(" %d %d %d", &rDay, &rMonth, &rYear);

			MIS[matchNumber].MStock += MIS[matchNumber].MReorder;

			for (int k = 0; k < *mDataSize; k++)
			{
				fprintf(RMD, "%s|%s|%.2lf|%d|%d|%d|%d-%d-%d|\n", MIS[k].MCode, MIS[k].MName, MIS[k].MPrice, MIS[k].MStock, MIS[k].MMinimum, MIS[k].MReorder, MIS[k].reorderDate.day, MIS[k].reorderDate.month, MIS[k].reorderDate.year);
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

void merchandiseList(MerchandiseInStock MIS[], int mDataSize)
{
	int number;
	system("cls");
	printf("\n\n");

	for (int i = 0; i < mDataSize; i++)
	{
		number = i + 1;

		printf("    NO.%d\n", number);
		printf("  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
		printf("    Code             : %s\n    Name             : %s\n    Price(RM)        : %.2lf\n    Stock Quantity   : %d\n    Minimum Level    : %d\n    Reorder Quantity : %d\n    Last Reorder Date: %d-%d-%d\n", MIS[i].MCode, MIS[i].MName, MIS[i].MPrice, MIS[i].MStock, MIS[i].MMinimum, MIS[i].MReorder, MIS[i].reorderDate.day, MIS[i].reorderDate.month, MIS[i].reorderDate.year);
		printf("  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("------------------------------------------------------\n\n");

	}
	system("pause");
}

void displayData(MerchandiseInStock MIS[], int mDataSize)
{
	system("cls");
	printf("\n\n  =====================================\n");
	printf("       < MERCHANDISE CODE & NAME >\n");
	printf("  =====================================\n");
	for (int i = 0; i < mDataSize; i++)
	{
		int number = i + 1;

		printf("    %d. %s     %s\n", number, MIS[i].MCode, MIS[i].MName);

	}
	printf("  =====================================\n\n");
}
