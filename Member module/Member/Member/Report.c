#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
#define MAX_SALES 30
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
	char memberId[10];
	Date date;
}SALES;

typedef struct {
	char memberId[10];
	int qtySold;
}MemberReport;

void report(Member memberInfo[], int memberSize)
{
	SALES salesOrder[MAX_SALES];
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

	MemberReport report[100];

	for (int i = 0; i < memberSize; i++)
	{
		strcpy(report[i].memberId, "M00000");
		if (memberSize < 10)
		{
			itoa(i, report[i].memberId[5],10);
			printf("%s", report[i].memberId[5]);
		}
		
	}

}