#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)

void addNew();

typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;

}NewMerchandise;

NewMerchandise NM;

void main() {

	int mChoice;

	do {

		printf("\n\n================================\n"
			"    What is Your Next Move??\n"
			"================================\n"
			" 1. Add a new Merchandise\n"
			" 2. Modify Merchandise Data\n"
			" 3. Check Merchandise List\n"
			" 4. Delete Merchandise Data\n"
			" 5. Daily Report\n"
			" 6. Exit\n"
			"\n\n"
			"Enter your choice  : ");
		scanf("%d", &mChoice);

		printf("\n\n");

		switch (mChoice)
		{
		case 1:
			addNew();
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

		case 7:

			printf("You are exiting program.....\n\n");
			break;

		default:

			printf("Unknow Value Please Try Agian\n"
				"============================================================================================================");


		}

	} while (mChoice != 6);

	system("pause");

}

void addNew()
{
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

		fprintf(AN, "%s|%s|%.2lf|%d|%d|%d|", NM.MCode, NM.MName, NM.MPrice, NM.MStock, NM.MMinimum, NM.MReorder);

		printf("\nAny New Merchandise More ? (if Yes press Y or No press N) :");
		scanf(" %c", &option);


	} while (toupper(option) != 'N');

	printf("New merchandise saved \n");
	system("pause");

	fclose(AN);
}




