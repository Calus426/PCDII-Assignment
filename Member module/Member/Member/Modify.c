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


void modifyMember(Member memberInfo[], int memberSize)
{
	char memberID[10], sureYesNo;
	char newName[40], newPhoneNo[12], newIC[13];
	char upperchar;
	int newDay, newMonth, newYear,wantedIndex;
	int dateCheck = 0;
	int matchcount = 0, selectEdit;
	Member matchMember[2];

	display(memberInfo, memberSize);
	printf("\n\n");

	do 
	{
		printf("Enter member ID to modify(X = exit):");
		rewind(stdin);
		scanf("%s", &memberID);

		upperchar = memberID[0];
		memberID[0] = toupper(upperchar); 


		for (int i = 0; i < memberSize; i++)
		{

			if (((strcmp(memberID, memberInfo[i].memberId) == 0)))
			{
				matchMember[matchcount] = memberInfo[i];
				matchcount++;
				wantedIndex = i;
			}
		}

		if (matchcount == 0)
		{
			printf("Member ID does not exist.Please reenter.\n");
		}

		if (tolower(memberID[0]) == 'x')
			break;

	} while (matchcount== 0);


	if (matchcount > 0)
	{
		system("cls");
		printf("\n\nMember Found!\n");
		printf("============\n\n");
		displayResult(matchMember, 0);
		printf("\n\n");

		do
		{
			printf("Are you sure u want to edit this member(Y/N)? ");
			rewind(stdin);
			scanf("%c", &sureYesNo);

			switch (sureYesNo)
			{
			case 'y':
			case 'Y':
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
						strcpy(memberInfo[wantedIndex].name, newName);
						break;

					case 2:
						do
						{
							printf("Phone number:");
							rewind(stdin);
							scanf("%s", &newPhoneNo);
							if (strlen(newPhoneNo) > 11 || strlen(newPhoneNo) < 9)
								printf("Invalid Phone number(between 10 to 11 number).Please reenter.\n");
						} while (strlen(newPhoneNo) > 11 || strlen(newPhoneNo) < 9);
						strcpy(memberInfo[wantedIndex].memberPhone, newPhoneNo);
						break;

					case 3:

						dateCheck = 0;
						while (dateCheck == 0) {
							printf("Date join(day month year):");
							rewind(stdin);
							scanf("%d %d %d", &newDay, &newMonth, &newYear);;

							if (newDay <= 0 || newDay > 31)
							{
								printf("Day should be between 1 to 31.Please reenter.\n");

								if (newMonth < 1 || newMonth>12)
								{
									printf("Month should be between 1 to 12.Please reenter.\n");
								}

							}

							else if (newMonth < 1 || newMonth>12)
							{
								printf("Month should be between 1 to 12.Please reenter.\n");

								if (newDay <= 0 || newDay > 31)
									printf("Day should be between 1 to 31.Please reenter.\n");
							}

							else if (newMonth == 2)
							{

								if ((newYear % 4 == 0) && newDay > 29)
								{
									printf("Day for month %d in Year %d only have 29 days.Please reenter.\n", newMonth, newYear);

								}


								else if ((newYear % 4 != 0) && newDay > 28)
								{
									printf("Day for month %d in Year %d only have 28 days.Please reenter.\n", newMonth, newYear);

								}
								else
									dateCheck = 2;
							}

							else if (newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11)
							{

								if (newDay <= 0 || newDay > 30)
									printf("Day should be between 1 to 30.Please reenter.\n");

								else
									dateCheck = 1;
							}


							else if (newMonth == 1 || newMonth == 3 || newMonth == 5 || newMonth == 7 || newMonth == 8
								|| newMonth == 10 || newMonth == 12)
							{
								if (newDay <= 0 || newDay > 31)
									printf("Day should be between 1 to 31.Please reenter.\n");

								else
									dateCheck = 3;
							}

							else
								dateCheck = 4;

						}

						memberInfo[wantedIndex].joinDate.day = newDay;
						memberInfo[wantedIndex].joinDate.month = newMonth;
						memberInfo[wantedIndex].joinDate.year = newYear;
						break;

					case 4:
						printf("Enter new IC Number:");
						rewind(stdin);
						scanf("%s", &newIC);

						for (int j = 0; j < memberSize; j++)//IC Number validation
						{
							while (strcmp(newIC, memberInfo[j].memberIC) == 0 || strlen(newIC) != 12)
							{
								if (strcmp(newIC, memberInfo[j].memberIC) == 0)
									printf("IC exist!Please reenter.\n");

								if (strlen(newIC) != 12)
									printf("IC Number should be in 12 number.\n");

								printf("Enter new IC Number:");
								rewind(stdin);
								scanf("%s", &newIC);
								j = -1;
							}
						}
						strcpy(memberInfo[wantedIndex].memberIC, newIC);
						break;

					case 5:break;

					default:printf("Enter valid selection!\n");


					}

				} while (selectEdit != 5);
			case 'n':
			case 'N':
				break;
			default:printf("Please enter valid choice(Y/N).\n");
			}

		} while (tolower(sureYesNo) != 'y' && tolower(sureYesNo) != 'n');
		
	}
	

}