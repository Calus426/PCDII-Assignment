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
	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7];
	Date joinDate;
	Address memberAdd;
}Member;


void search(Member memberInfo[], int memberSize)
{
	Member matchMember[100];
	int matchcount = 0, yearJoin;
	char mID[10], ulID[10];
	int choice = searchMenu();

	switch (choice)
	{
	case 1:
		system("cls");
		printf("Enter member ID:");
		rewind(stdin);
		scanf("%s", &mID);

		for (int i = 0; i < memberSize; i++)
		{

			if (((strcmp(mID, memberInfo[i].memberId) == 0)))
			{
				matchMember[matchcount] = memberInfo[i];
				matchcount++;
			}

		}
		if (matchcount == 0)
		{
			printf("No member found!\n\n");
			system("pause");
		}
		else
		{
			detailDisplay(matchMember, matchcount);
		}
		
		break;



	case 2:
		system("cls");
		printf("Enter upline ID:");
		rewind(stdin);
		scanf("%s", &ulID);

		for (int i = 0; i < memberSize; i++)
		{

			if (((strcmp(ulID, memberInfo[i].memberId) == 0)))
			{
				matchMember[matchcount] = memberInfo[i];
				matchcount++;
			}

		}
		if (matchcount == 0)
		{
			printf("No member found!\n\n");
			system("pause");
		}
		else
		{
			detailDisplay(matchMember, matchcount);
		}

		break;

	case 3:
		system("cls");
		printf("Enter Year of joinning:");
		rewind(stdin);
		scanf("%d", &yearJoin);

		for (int i = 0; i < memberSize; i++)
		{

			if (yearJoin == memberInfo[i].joinDate.year)
			{
				matchMember[matchcount] = memberInfo[i];
				matchcount++;
			}

		}

		if (matchcount == 0)
		{
			printf("No member found!\n\n");
			system("pause");
		}
		else
		{
			detailDisplay(matchMember, matchcount);
		}

		break;

	}
}

int searchMenu()
{
	int choice;
	printf("======================================\n");
	printf("\t\tSearch function\n");
	printf("======================================\n");
	printf("1. Search by Member ID\n");
	printf("2. Search by UpLine ID\n");
	printf("3. Search by Year join\n");
	printf("Enter choice(1-3):");
	scanf("%d", &choice);
	return choice;

}
