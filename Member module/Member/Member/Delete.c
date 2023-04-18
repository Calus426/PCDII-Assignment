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

void deleteMember(Member memberInfo[], int *memberSize)
{
	char memberID[10],sureDelete;
	int matchcount = 0,deleteIndex;
	Member matchMember[2];

	printf("Enter member ID:");
	rewind(stdin);
	scanf("%s", &memberID);

	for (int i = 0; i < *memberSize; i++)
	{

		if (((strcmp(memberID, memberInfo[i].memberId) == 0)))
		{
			matchMember[matchcount] = memberInfo[i];
			deleteIndex = i;
			matchcount++;
		}

	}
	if (matchcount > 0)
	{
		detailDisplay(matchMember, matchcount);

		printf("Are you sure to delete this member(Y/N)?");
		rewind(stdin);
		scanf("%c", &sureDelete);

		if (toupper(sureDelete) == 'Y')
		{
			for (int j = deleteIndex; j < *memberSize; j++)
			{
				memberInfo[j] = memberInfo[j + 1];
			}
			(*memberSize)--;

			printf("\n\nDeleted sucessfully!\n\n");
		}


		FILE* delPtr = fopen("member.txt", "wb");
		for (int k = 0; k < *memberSize; k++)
		{
			fwrite(&memberInfo[k], sizeof memberInfo[k], 1, delPtr);
		}


		system("pause");
	}
		

	else
	{
		printf("Member ID not found!\n\n");
		system("pause");
	}

	

}