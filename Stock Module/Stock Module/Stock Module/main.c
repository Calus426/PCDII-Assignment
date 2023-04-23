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

void addNew();
void search(MerchandiseInStock MIS[], int mDataSize);
void merchandiseData(MerchandiseInStock MIS[], int *mDataSize);
void displayData(MerchandiseInStock MIS[], int mDataSize);
void deleteData(MerchandiseInStock MIS[], int *mDataSize);
void modifyData(MerchandiseInStock MIS[], int *mDataSize);
void restockMerchandise(MerchandiseInStock MIS[], int* mDataSize);

void main() {

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
			"   2. Modify Merchandise Data\n"
			"   3. Check Merchandise List\n"
			"   4. Delete Merchandise Data\n"
			"   5. Restock Merchandise\n"
			"   6. Report\n"
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



