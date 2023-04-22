#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
#define MAX_SALES 30
#define MAX_MEMBER 100
typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char add1[40], add2[40], postcode[6], city[40], state[40];

}Address;

typedef struct
{
	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7];
	Date joinDate;
	Address memberAdd;
}Member;

typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[7];
	Date date;
}SALES;

typedef struct {
	char memberId[7];
	int qtySold;
	double totalSpent;
}MemberReport;

void report2(Member memberInfo[], int memberSize)
{
	system("cls");

	SALES salesOrder[MAX_SALES];
	MemberReport report[MAX_MEMBER] = { "M00000",1,0.00 };
	MemberReport temp;
	int salesN = 0;
	char num;

	FILE* fileOpen = fopen("salesRecord.bin", "rb");
	if (fileOpen == NULL) {
		printf("\tError file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}

	while (fread(&salesOrder[salesN], sizeof(SALES), 1, fileOpen) != 0) {
		salesN++;
	}


	for (int i = 0; i < memberSize; i++)
	{
		strcpy(report[i].memberId, memberInfo[i].memberId);
		report[i].qtySold = 0;
		report[i].totalSpent = 0.00;
	}

	for (int i = 0; i < salesN; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(salesOrder[i].memberId, report[j].memberId) == 0)
			{
				report[j].qtySold += salesOrder[i].qtySold;
				report[j].totalSpent += salesOrder[i].qtySold * salesOrder[i].price;
			}
		}
	}

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = i + 1; j < memberSize; j++)
		{
			if (report[i].totalSpent < report[j].totalSpent)
			{
				temp = report[i];
				report[i] = report[j];
				report[j] = temp;
			}

		}
	}

	printf("===================================================================================================== \n");
	printf("%-2s   %-30s\t%s\t%s\t%s\n", "", "Name", "Member ID", "TOTAL ITEM BOUGHT", "TOTAL SPENT");
	printf("=====================================================================================================\n");

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(report[i].memberId, memberInfo[j].memberId) == 0)
			{
				printf("%2d.  ", i + 1);
				printf("%-30s", memberInfo[j].name);
			}

		}

		printf("\t%s", report[i].memberId);
		printf("\t\t%d\t\t\t", report[i].qtySold);
		printf("%.2lf\n", report[i].totalSpent);
		 
	}
	printf("=====================================================================================================\n");

	system("pause");
}