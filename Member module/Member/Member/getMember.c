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

void getMember(Member memberInfo[], int *memberSize)
{

	FILE* getPtr = fopen("member.bin", "rb");

	*memberSize = 0;

	while (fread(&memberInfo[*memberSize], sizeof memberInfo[*memberSize], 1, getPtr))
	{
		(*memberSize)++;

	}

	fclose(getPtr);
}