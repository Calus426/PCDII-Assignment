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

void addMember()
{
	FILE* ptr = fopen("member.bin", "wb");

	if (ptr == NULL)  //ensure the file can be opened
	{
		printf("Unable to open file");
		exit(-1);
	}

	Member memberinfo;
	char uplineYesNo;  

	for (int i = 0; i <1; i++) 
	{
		//basic info
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.name);

		printf("Enter Member id:");
		rewind(stdin);
		scanf("%s", &memberinfo.memberId);

		printf("Gender:");
		rewind(stdin);
		scanf("%c", &memberinfo.gender);

		printf("Phone number:");
		rewind(stdin);
		scanf("%c", &memberinfo.gender);

		printf("Member got a upline id?");
		rewind(stdin);
		scanf("%c", &uplineYesNo);

		if (tolower(uplineYesNo) == 'y')
		{
			printf("Upline id:");
			rewind(stdin);
			scanf("%s", &memberinfo.uplineId);
		}

		printf("Date join(day month year):");
		rewind(stdin);
		scanf("%d %d %d", &memberinfo.joinDate.day, &memberinfo.joinDate.month, &memberinfo.joinDate.year);

		printf("Member address1:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.memberAdd.add1);

		printf("Member address2:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.memberAdd.add2);

		printf("Postcode:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.memberAdd.postcode);

		printf("Member city:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.memberAdd.city);

		printf("Member state:");
		rewind(stdin);
		scanf("%[^\n]", &memberinfo.memberAdd.state);


		fwrite(&memberinfo, sizeof memberinfo, 1, ptr);
	}

	fclose(ptr);

}