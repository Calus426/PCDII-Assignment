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


void search(Member memberInfo[],int memberSize)
{
	Member matchMember[100];
	int matchcount = 0;

	char mID[10];
	printf("Enter member ID:");
	scanf("%s", &mID);

	for (int i = 0; i < memberSize; i++) 
	{

		if (((strcmp(mID, memberInfo[i].memberId) == 0)))
		{
			matchMember[matchcount] = memberInfo[i];
			matchcount++;
		}
	
	}
	display(matchMember,matchcount);
}