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
	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[6];
	Date joinDate;
	Address memberAdd;
}Member;

void addMember()
{
	char c;
	int i = 0;
	system("cls");
	FILE* ptr = fopen("member.txt", "ab");

	if (ptr == NULL)  //ensure the file can be opened
	{
		printf("Unable to open file");
		exit(-1);
	}

	Member newMemberInfo;
	char uplineYesNo;  

	for (int i = 0; i <1; i++) 
	{
		//basic info
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.name);

		printf("Enter Member id:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberId);

		printf("Enter IC Number:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberIC);

		do {
			printf("Gender:");
			rewind(stdin);
			scanf("%c", &newMemberInfo.gender);
		} while ((tolower(newMemberInfo.gender)) != 'f'&& (tolower(newMemberInfo.gender)) != 'm');
		

		printf("Phone number:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberPhone);

		printf("Member got a upline id?");
		rewind(stdin);
		scanf("%c", &uplineYesNo);

		if (tolower(uplineYesNo) == 'y')
		{
			printf("Upline id:");
			rewind(stdin);
			scanf("%s", &newMemberInfo.uplineId);
		}

		else
			strcpy(newMemberInfo.uplineId, "    -");

		do {
			printf("Date join(day month year):");
			rewind(stdin);
			scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);

			if (newMemberInfo.joinDate.month == 2) 
			{
				if (newMemberInfo.joinDate.year % 4 == 0)
				{
					if (newMemberInfo.joinDate.day > 29)
					{
						while (newMemberInfo.joinDate.day > 29)
						{
							printf("February in year %d only have 29 days!Please reenter.\n", newMemberInfo.joinDate.year);
							printf("Date join(day):");
							rewind(stdin);
							scanf("%d", &newMemberInfo.joinDate.day);
						}
						
						
					}
				}
				else 
				{
					if (newMemberInfo.joinDate.day > 28) {
						while (newMemberInfo.joinDate.day > 28) 
					{
						printf("February in year %d only have 28 days!Please reenter.\n", newMemberInfo.joinDate.year);
						printf("Date join(day):");
						rewind(stdin);
						scanf("%d", &newMemberInfo.joinDate.day);
					}
					
					}
					
				}
			}
				
					
					
							

		    if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
			{
				printf("Day cannot less than 0 or more than 31 and Month cannot less than 1 or more than 12!Please reenter.\n");
				printf("Date join(day month year):");
				rewind(stdin);
				scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
			}

		} while (newMemberInfo.joinDate.day<=0|| newMemberInfo.joinDate.day>31|| newMemberInfo.joinDate.month<1 || newMemberInfo.joinDate.month>12);
		

		printf("Member address1:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add1);

		printf("Member address2:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add2);

		printf("Postcode:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.postcode);

		printf("Member city:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.city);

		printf("Member state:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.state);


		fwrite(&newMemberInfo, sizeof newMemberInfo, 1, ptr);

	}

	fclose(ptr);

}