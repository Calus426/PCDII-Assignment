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


void modifyMember(Member memberInfo[], int memberSize)
{
	char memberID[10], sureYesNo;
	char newName[40], newPhoneNo[12], newIC[13];
	int newDay, newMonth, newYear;

	printf("Enter member ID to modify:");
	scanf("%s", &memberID);

	int matchcount = 0,selectEdit;
	Member matchMember[100];

	for (int i = 0; i < memberSize; i++)
	{

		if (((strcmp(memberID, memberInfo[i].memberId) == 0)))
		{
			matchMember[matchcount] = memberInfo[i];
			matchcount++;
			printf("\n\nMember Found!\n");
			printf("============\n\n\n");
			detailDisplay(matchMember, matchcount);

			
			printf("Are you sure u want to edit this member? ");
			rewind(stdin);
			scanf("%c", &sureYesNo);

			if (tolower(sureYesNo) == 'y')
			{
				do
				{
					printf("1.Edit Name\n");
					printf("2.Edit Member Phone Number\n");
					printf("3.Edit Member Join Date\n");
					printf("4.Edit IC Number\n");
					printf("5.Exit edit\n");
					printf("Select(1-5):");
					scanf("%d", &selectEdit);

					switch (selectEdit)
					{
					case 1:
						printf("Enter new name:");
						rewind(stdin);
						scanf("%[^\n]", &newName);
						strcpy(memberInfo[i].name, newName); 
						break;

					case 2:
						printf("Enter new Phone Number:");
						rewind(stdin);
						scanf("%s", &newPhoneNo);
						strcpy(memberInfo[i].memberPhone, newPhoneNo);
						break;

					case 3:
						printf("Enter new Join Date(day month year):");
						rewind(stdin);
						scanf("%d %d %d", &newDay,&newMonth,&newYear);
						memberInfo[i].joinDate.day = newDay;
						memberInfo[i].joinDate.month = newMonth;
						memberInfo[i].joinDate.year = newYear;
						break;

					case 4:
						printf("Enter new IC Number:");
						rewind(stdin);
						scanf("%s", &newIC);
						strcpy(memberInfo[i].memberIC, newIC);
						break;

					case 5:break;

					default:printf("Enter valid selection!\n");


					}
					
				} while (selectEdit != 5);
				
			}
				

		}
	}
	

}