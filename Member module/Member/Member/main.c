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
	char memberId[7],gender,memberPhone[12],uplineId[6];
	Date joinDate;
	Address memberAdd;
}Member;

void main() 
{ 
	FILE* ptr = fopen("member.bin", "rb");

	if (ptr == NULL)
	{
		printf("Unable to open file");
		exit(-1);
	}
}

