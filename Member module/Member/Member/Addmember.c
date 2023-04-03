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

	Member memberInfo;
	char uplineYesNo;  

	for (int i = 0; i <1; i++) 
	{
		//basic info
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.name);

		printf("Enter Member id:");
		rewind(stdin);
		scanf("%s", &memberInfo.memberId);

		printf("Gender:");
		rewind(stdin);
		scanf("%c", &memberInfo.gender);

		printf("Phone number:");
		rewind(stdin);
		scanf("%s", &memberInfo.memberPhone);

		printf("Member got a upline id?");
		rewind(stdin);
		scanf("%c", &uplineYesNo);

		if (tolower(uplineYesNo) == 'y')
		{
			printf("Upline id:");
			rewind(stdin);
			scanf("%s", &memberInfo.uplineId);
		}

		printf("Date join(day month year):");
		rewind(stdin);
		scanf("%d %d %d", &memberInfo.joinDate.day, &memberInfo.joinDate.month, &memberInfo.joinDate.year);

		printf("Member address1:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.memberAdd.add1);

		printf("Member address2:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.memberAdd.add2);

		printf("Postcode:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.memberAdd.postcode);

		printf("Member city:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.memberAdd.city);

		printf("Member state:");
		rewind(stdin);
		scanf("%[^\n]", &memberInfo.memberAdd.state);


		fwrite(&memberInfo, sizeof memberInfo, 1, ptr);
	}

	fclose(ptr);

}