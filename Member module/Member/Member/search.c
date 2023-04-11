#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning (disable:4996)

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char add1[40], add2[40], postcode[6], city[40], state[40];

}Address;

typedef struct
{
	char name[40], memberId[7], gender, memberPhone[12], uplineId[6];
	Date joinDate;
	Address memberAdd;
}Member;


void search()
{
	FILE* dPtr = fopen("member.bin", "rb");


	if (dPtr == NULL)  //ensure the file can be opened
	{
		printf("Unable to open file");
		exit(-1);
	}

	Member memberInfo[30];
	int pCount = 0;

	while (fread(&memberInfo[pCount], sizeof memberInfo[pCount], 1, dPtr))
	{
		pCount++;
	}



}