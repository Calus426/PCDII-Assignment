#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
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

void addMember(Member memberInfo[], int memberSize)
{
	char upperchar,continueAdd,confirm,count=0;
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

	do 
	{
		//basic info
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.name);
		printf("\n");

		printf("Enter Member id:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberId);
		printf("\n");

		while (strlen(newMemberInfo.memberId) > 6 || strlen(newMemberInfo.memberId) < 2)
		{
			printf("Member ID at least two character.Please reenter!\n");
			printf("Enter Member id:");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberId);
		}

		while (newMemberInfo.memberId[0] != 'm' && newMemberInfo.memberId[0] != 'M')
		{
			printf("Member ID should be start with character \'M\'.Please reenter!\n");
			printf("Enter Member id:");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberId);
		}
		upperchar=newMemberInfo.memberId[0];
		newMemberInfo.memberId[0] = toupper(upperchar);
		
		for (int j = 0; j < memberSize; j++)//member id validation, 1 member id for 1 person only.
		{
			while (strcmp(newMemberInfo.memberId, memberInfo[j].memberId) == 0)
			{
				printf("Member ID exist!Please reenter.\n");
				printf("Enter Member id:");
				rewind(stdin);
				scanf("%s", &newMemberInfo.memberId);
				printf("\n");
			}
		}
		
		printf("Enter IC Number:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberIC);

		for (int j = 0; j < memberSize; j++)//IC Number validation
		{
			while (strcmp(newMemberInfo.memberIC, memberInfo[j].memberIC) == 0 ||strlen(newMemberInfo.memberIC)!=12)
			{
				if(strcmp(newMemberInfo.memberIC, memberInfo[j].memberIC) == 0)
				printf("IC exist!Please reenter.\n");

				if (strlen(newMemberInfo.memberIC) != 12)
					printf("IC Number should be in 12 number.\n");

				printf("Enter IC Number:");
				rewind(stdin);
				scanf("%s", &newMemberInfo.memberIC);
			}
		}
		printf("\n");


		do {
			printf("Gender:");
			rewind(stdin);
			scanf("%c", &newMemberInfo.gender);
			newMemberInfo.gender = toupper(newMemberInfo.gender);
			if (newMemberInfo.gender != 'F' && newMemberInfo.gender != 'M')
				printf("Gender only Male(m) or Female(f).Please reenter.\n");
		} while (newMemberInfo.gender != 'F'&& newMemberInfo.gender != 'M'); //Gender only can be Female(f) and Male (m)
		printf("\n");
		
		do
		{
			printf("Phone number:");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberPhone);
			if (strlen(newMemberInfo.memberPhone) > 11 || strlen(newMemberInfo.memberPhone) < 9)
				printf("Invalid Phone number(between 10 to 11 number).Please reenter.\n");
		}while (strlen(newMemberInfo.memberPhone) > 11 || strlen(newMemberInfo.memberPhone) < 9);
		printf("\n");

		printf("Member got a upline id(Y/N)? ");
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
		printf("\n");

		//Date join
		printf("Date join(day month year):");
		rewind(stdin);
		scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);

		while (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31 || newMemberInfo.joinDate.month < 1 || newMemberInfo.joinDate.month>12) {


			if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
			{
				printf("Day should be between 1 to 31.Please reenter.\n");
				printf("Date join(day month year):");
				rewind(stdin);
				scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);

				if (newMemberInfo.joinDate.month < 1 || newMemberInfo.joinDate.month>12)
				{
					printf("Month should be between 1 to 12.Please reenter.\n");
					printf("Date join(day month year):");
					rewind(stdin);
					scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
				}
					
			}

			else if (newMemberInfo.joinDate.month < 1 || newMemberInfo.joinDate.month>12)
			{
				printf("Month should be between 1 to 12.Please reenter.\n");
				printf("Date join(day month year):");
				rewind(stdin);
				scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
			}
				



			else if (newMemberInfo.joinDate.month == 4 || newMemberInfo.joinDate.month == 6 || newMemberInfo.joinDate.month == 9
				|| newMemberInfo.joinDate.month == 11)

			{
				while (newMemberInfo.joinDate.day > 30)
				{
					printf("Day for month %d only until 30.Please reenter\n.", newMemberInfo.joinDate.month);
					printf("Date join(day month year):");
					rewind(stdin);
					scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
				}

			}

			else if (newMemberInfo.joinDate.month == 2)
			{

				while ((newMemberInfo.joinDate.year % 4 == 0) && newMemberInfo.joinDate.day > 29)
				{
					printf("Day for month %d in Year %d only have 29 days.Please reenter.\n",newMemberInfo.joinDate.month,newMemberInfo.joinDate.year);
					printf("Date join(day month year):");
					rewind(stdin);
					scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
				}


				while ((newMemberInfo.joinDate.year % 4 != 0) && newMemberInfo.joinDate.day > 28)
				{
					printf("Day for month %d in Year %d only have 28 days.Please reenter.\n", newMemberInfo.joinDate.month, newMemberInfo.joinDate.year);
					printf("Date join(day month year):");
					rewind(stdin);
					scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);
				}

			}
						
		}
		printf("\n");

		printf("Member address1:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add1);
		printf("\n");

		printf("Member address2:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add2);
		printf("\n");

		printf("Postcode(XXXXX):");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.postcode);
		while (strlen(newMemberInfo.memberAdd.postcode) !=5)
		{
			printf("Please reenter.\n");
			printf("Postcode(XXXXX):");
			rewind(stdin);
			scanf("%[^\n]", &newMemberInfo.memberAdd.postcode);
		}

		printf("\n");

		printf("Member city:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.city);
		printf("\n");

		printf("Member state:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.state);
		printf("\n");

		printf("\n\nAre you sure to add in this member(Y/N)?");
		rewind(stdin);
		scanf("%c", &confirm);
		
		while (toupper(confirm) != 'Y' && toupper(confirm) != 'N')
		{
			printf("Invalid choice.Please reenter.\n");
			printf("\n\nAre you sure to add in this member?");
			rewind(stdin);
			scanf("%c", &confirm);
	
		}

		if (tolower(confirm) == 'y')
		{
			fwrite(&newMemberInfo, sizeof newMemberInfo, 1, ptr);
			printf("Added member sucessfully!\n");
		}

		else if (tolower(confirm) == 'n')
		{
			printf("Member not added in.\n");
		}


		printf("Do you want to add more member(Y/N)?");
		rewind(stdin);
		scanf("%c", &continueAdd);

		while (toupper(continueAdd) != 'Y' && toupper(continueAdd) != 'N')
		{
			printf("Invalid choice.Please reenter.\n");
			printf("Do you want to add more member(Y/N)?");
			rewind(stdin);
			scanf("%c", &continueAdd);
		}
	}while (toupper(continueAdd) == 'Y');

	fclose(ptr);

}