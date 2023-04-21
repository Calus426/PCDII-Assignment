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
	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7];
	Date joinDate;
	Address memberAdd;
}Member;

void getMember(Member[], int*);

void addMember(Member memberInfo[], int memberSize)
{
	char upperchar[4], continueAdd, confirm;
	int i = 0;
	system("cls");
	
	Member newMemberInfo;
	char uplineYesNo;  

	do 
	{
		FILE* ptr = fopen("member.bin", "ab");

		if (ptr == NULL)  //ensure the file can be opened
		{
			printf("Unable to open file");
			exit(-1);
		}

		system("cls");
		//basic info
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.name);
		printf("\n");

		
		int memberIDcheck = 0;
		while (memberIDcheck == 0) 
		{
			memberIDcheck = 1;
			printf("Enter Member id(M#####):");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberId);
			printf("\n");

			upperchar[0] = newMemberInfo.memberId[0];
			newMemberInfo.memberId[0] = toupper(upperchar[0]);


			for (int j = 0; j < memberSize; j++)
			{
				if (strcmp(newMemberInfo.memberId, memberInfo[j].memberId) == 0)
				{
					printf("Member ID exist!Please reenter.\n");
					memberIDcheck = 0;
				}

			}

			for (int j = 1; j < strlen(newMemberInfo.memberId); j++)
			{
				if (isalpha(newMemberInfo.memberId[j]))
				{
					printf("Member ID should be start with character \'M\' and following with number.Please reenter!\n");
					memberIDcheck = 0;
				}
			}
			
			if (strlen(newMemberInfo.memberId) > 6 || strlen(newMemberInfo.memberId) < 2)
			{
				printf("Member ID at least 2 character and maximum 6.Please reenter!\n");
				memberIDcheck = 0;
			}

			else if (newMemberInfo.memberId[0] != 'M')
			{
				printf("Member ID should be start with character \'M\'.Please reenter!\n");
				memberIDcheck = 0;
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
				j = -1;
			}
		}
		printf("\n");


		do {
			printf("Gender(M/F):");
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
			
			while (strlen(newMemberInfo.uplineId) > 6 || strlen(newMemberInfo.uplineId) < 2)
			{
				printf("Upline ID at least 2 character and maximun 6.Please reenter!\n");
				printf("Enter Upline id:");
				rewind(stdin);
				scanf("%s", &newMemberInfo.uplineId);
			}

			while (newMemberInfo.uplineId[0] != 'U' && newMemberInfo.uplineId[0] != 'u' ||( newMemberInfo.uplineId[1] != 'l' && newMemberInfo.uplineId[1] != 'L'))
			{
				printf("Upline ID should be start with character \'UL\'.Please reenter!\n");
				printf("Enter Upline id:");
				rewind(stdin);
				scanf("%s", &newMemberInfo.uplineId);
			}
			upperchar[1] = newMemberInfo.uplineId[0];
			newMemberInfo.uplineId[0] = toupper(upperchar[1]);

			upperchar[2] = newMemberInfo.uplineId[1];
			newMemberInfo.uplineId[1] = toupper(upperchar[2]);
		}

		else
			strcpy(newMemberInfo.uplineId, "    -");
		printf("\n");


		//Date join
		int dateCheck = 0;
		while (dateCheck == 0) {
			printf("Date join(day month year):");
			rewind(stdin);
				scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);

			if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
			{
				printf("Day should be between 1 to 31.Please reenter.\n");

				if (newMemberInfo.joinDate.month < 1 || newMemberInfo.joinDate.month>12)
				{
					printf("Month should be between 1 to 12.Please reenter.\n");
				}

			}

			else if (newMemberInfo.joinDate.month < 1 || newMemberInfo.joinDate.month>12)
			{
				printf("Month should be between 1 to 12.Please reenter.\n");

				if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
					printf("Day should be between 1 to 31.Please reenter.\n");
			}

			else if (newMemberInfo.joinDate.month == 2)
			{

				if ((newMemberInfo.joinDate.year % 4 == 0) && newMemberInfo.joinDate.day > 29)
				{
					printf("Day for month %d in Year %d only have 29 days.Please reenter.\n", newMemberInfo.joinDate.month, newMemberInfo.joinDate.year);

				}


				else if ((newMemberInfo.joinDate.year % 4 != 0) && newMemberInfo.joinDate.day > 28)
				{
					printf("Day for month %d in Year %d only have 28 days.Please reenter.\n", newMemberInfo.joinDate.month, newMemberInfo.joinDate.year);

				}
				else
					dateCheck = 2;
			}

			else if (newMemberInfo.joinDate.month == 4 || newMemberInfo.joinDate.month == 6 || newMemberInfo.joinDate.month == 9 || newMemberInfo.joinDate.month == 11)
			{

				if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 30)
					printf("Day should be between 1 to 30.Please reenter.\n");

				else
					dateCheck = 1;
			}


			else if (newMemberInfo.joinDate.month == 1 || newMemberInfo.joinDate.month == 3 || newMemberInfo.joinDate.month == 5 || newMemberInfo.joinDate.month == 7 || newMemberInfo.joinDate.month == 8
				|| newMemberInfo.joinDate.month == 10 || newMemberInfo.joinDate.month == 12)
			{
				if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
					printf("Day should be between 1 to 31.Please reenter.\n");

				else
					dateCheck = 3;
			}

				else
					dateCheck = 4;
						
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
			fclose(ptr);
			getMember(memberInfo, &memberSize);

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

		if(toupper(continueAdd)== 'N')
			fclose(ptr);

	}while (toupper(continueAdd) == 'Y');


}