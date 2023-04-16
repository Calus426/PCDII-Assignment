#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)
//Item Code, item description, item price, quantity in stock, minimum level,reorder quantity,



typedef struct {

	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;



}NewMerchandise;

NewMerchandise NM;

void addNew()
{
	FILE* AN;
	AN = fopen("stock.txt", "w");
	
	if (AN == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}
	char option;
	do
	{
		printf("1. Enter new merchandise code              :");
		scanf("%s", &NM.MCode);

		printf("2. Enter new merchandise name              :");
		scanf(" %[^\n]", &NM.MName);

		printf("3. Enter new merchandise price             :");
		scanf(" %lf", &NM.MPrice);

		printf("4. Enter new merchandise stock             :");
		scanf(" %d", &NM.MStock);

		printf("5. Enter new merchandise minimum level     :");
		scanf(" %d", &NM.MMinimum);

		printf("6. Enter new merchandise reorder quantity  :");
		scanf(" %d", &NM.MReorder);
		
		fprintf(AN, "%s| %s| %.2lf| %d| %d| %d|", NM.MCode, NM.MName, NM.MPrice, NM.MStock, NM.MMinimum, NM.MReorder);

		printf("\nAny new merchandise more ? (if Yes press Y or No press N) :");
		scanf(" %c", &option);
		

	} while (toupper(option) != 'N');
	
	printf("New merchandise saved \n");
	system("pause");

	fclose(AN);
}