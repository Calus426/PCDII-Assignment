#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)
//Item Code, item description, item price, quantity in stock, minimum level,reorder quantity

typedef struct {

	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;



}MerchandiseInStock;

MerchandiseInStock MIS;

typedef struct {

	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;



}MerchandiseToSearch;

MerchandiseToSearch MTS;



void search()
{
	char option;

	FILE* SH;
	SH = fopen("stock.txt", "r");

	if (SH == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}

	

	while (fscanf(SH, "%[^|] %[^|] %[^|] %[^|] %[^|] %[^|] ", &MIS.MCode, &MIS.MName, &MIS.MPrice, &MIS.MStock, &MIS.MMinimum, &MIS.MReorder) != EOF)
	{

		printf("Enter Merchandise Code or Merchandise Name (C = Code , N = Name): ");
		scanf(" %c", &option);

		if (toupper(option) == 'C')
		{
			printf("Enter Merchandise Code : ");
			scanf(" %[^\n]", MTS.MCode);

		}
		else if (toupper(option) == 'N')
		{
			printf("Enter Merchandise Name : ");
			scanf(" %[^\n]", MTS.MName);
		}
		else
		{
			printf("\n\nWrong input enter!!!");
			printf("\n===========================================================================\n\n");
		}


		

	}

	fclose(SH);
}