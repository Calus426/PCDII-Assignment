#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
#define MAX_SALES 30
#define MAX_MEMBER 100

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

typedef struct {
	char memberId[7];
	int qtySold;
	double totalSpent;
}MemberReport;

typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[7];
	Date date;
}SALES_MEMBER;

typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[10];
	Date date;
}SALES;


void memberModule();
void addMember(Member[], int);
void display(Member[], int);
void getMember(Member[], int*);
void memberSearch(Member[], int);
void detailDisplay(Member memberInfo[], int memberSize);
int searchMenu();
void modifyMember(Member memberInfo[], int memberSize);
void deleteMember(Member memberInfo[], int* memberSize);
void displayResult(Member memberInfo[], int memberSize);
void report_buyMost(Member memberInfo[], int memberSize);
void report_highestSpent(Member memberInfo[], int memberSize);

//void main()
//{
//	memberModule();
//}
void memberModule() //Menu for Member Module
{
	
	Member member[100];
	int memberSize;
	getMember(member, &memberSize);
	int choice;
	//above 4 need to put at void main
	system("cls");

	do {
		choice = 0;
		printf("\t\t==================================\n");
		printf("\t\tWELCOME TO MEMBER INFORMATION MENU\n");
		printf("\t\t==================================\n\n\n");
		printf("\t\t1.Display member\n");
		printf("\t\t2.Add member\n");
		printf("\t\t3.Search member\n");
		printf("\t\t4.Modify member\n");
		printf("\t\t5.Remove member\n");
		printf("\t\t6.Member Report that bought the most item\n");
		printf("\t\t7.Member Report of highest total spending\n");
		printf("\t\t8.Exit\n\n\n");
		printf("\t\tEnter choice:");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			display(member, memberSize);
			system("pause");
			system("cls");
			break;

		case 2:  addMember(member, memberSize); getMember(member, &memberSize); system("cls"); break;
		case 3:  memberSearch(member, memberSize); system("cls"); break;
		case 4:  modifyMember(member, memberSize);	system("cls"); break;
		case 5:  display(member, memberSize); deleteMember(member, &memberSize); system("cls"); break;
		case 6:	 report_buyMost(member, memberSize); system("cls"); break;
		case 7:  report_highestSpent(member, memberSize); system("cls"); break;
		case 8:  printf("\n\n\t\tBYEBYE!\n\n"); system("pause"); break;
		default:printf("Enter valid choice!(1-7)\n"); system("pause"); system("cls");
		}

	} while (choice != 8);

}


void getMember(Member memberInfo[], int* memberSize)
{

	FILE* getPtr = fopen("member.bin", "rb");

	if (getPtr == NULL)
	{
		printf("Unable to open the file.\n");
		system("pause");
		exit(-1);
	}

	*memberSize = 0;

	while (fread(&memberInfo[*memberSize], sizeof memberInfo[*memberSize], 1, getPtr))
	{
		(*memberSize)++;

	}

	fclose(getPtr);
}


//Display Function

void display(Member memberInfo[], int memberSize)
{
	system("cls");

	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %s\n", " Name", "Member Id", "IC", "Gender", "Phone Number", "Upline Id", "Join Date");
	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %s\n", "=================", "=========", "=============", "======", "============", "=========", "==========");

	for (int i = 0; i < memberSize; i++) {
		printf("%2d.  %-20s %-10s %-13s %-7c %-13s %-10s %.2d-%.2d-%d\n", i + 1, memberInfo[i].name, memberInfo[i].memberId, memberInfo[i].memberIC, toupper(memberInfo[i].gender), memberInfo[i].memberPhone, memberInfo[i].uplineId,
			memberInfo[i].joinDate.day, memberInfo[i].joinDate.month, memberInfo[i].joinDate.year);
	}
	printf("==============================================================================================\n\n");

}

void detailDisplay(Member memberInfo[], int memberSize)
{

	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %-12s % s\n", " Name", "Member Id", "IC", "Gender", "Phone Number", "Upline Id", "Join Date", "Address");
	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %-12s %s\n", "==============", "=========", "=============", "======", "============", "=========", "==========", "========================================================");

	for (int i = 0; i < memberSize; i++) {
		printf("%2d.  %-20s %-10s %-13s %-7c %-13s %-10s %.2d-%.2d-%d   %s,%s,%s,%s,%s\n", i + 1, memberInfo[i].name, memberInfo[i].memberId, memberInfo[i].memberIC, toupper(memberInfo[i].gender), memberInfo[i].memberPhone, memberInfo[i].uplineId,
			memberInfo[i].joinDate.day, memberInfo[i].joinDate.month, memberInfo[i].joinDate.year, memberInfo[i].memberAdd.add1, memberInfo[i].memberAdd.add2, memberInfo[i].memberAdd.postcode,
			memberInfo[i].memberAdd.city, memberInfo[i].memberAdd.state);
	}
	printf("\n\n");
	system("pause");
	system("cls");
}

void displayResult(Member memberInfo[], int memberSize)
{
	printf("\t__________________________________________________________________________\n");
	printf("\tName:\t\t%s \n", memberInfo[memberSize].name);
	printf("\tMember ID:\t%s \n", memberInfo[memberSize].memberId);
	printf("\tIC Number:\t%s \n", memberInfo[memberSize].memberIC);
	printf("\tGender:\t\t%c\n", memberInfo[memberSize].gender);
	printf("\tPhone Number:\t%s \n", memberInfo[memberSize].memberPhone);
	printf("\tUpline ID:\t%s \n", memberInfo[memberSize].uplineId);
	printf("\tDate of Join:\t%.2d-%.2d-%d \n", memberInfo[memberSize].joinDate.day, memberInfo[memberSize].joinDate.month, memberInfo[memberSize].joinDate.year);
	printf("\tAddress:\t%s,%s,%s,%s,%s \n", memberInfo[memberSize].memberAdd.add1, memberInfo[memberSize].memberAdd.add2, memberInfo[memberSize].memberAdd.postcode,
		memberInfo[memberSize].memberAdd.city, memberInfo[memberSize].memberAdd.state);
	printf("\t__________________________________________________________________________\n");

}

//Add member Function
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
			printf("Unable to open file.\n");
			return;
		}

		system("cls");
		//basic info
	//Member ID and validation
		int memberIDcheck = 0;
		while (memberIDcheck == 0)
		{
			memberIDcheck = 1;

			printf("Enter Member id(M#####)(X=Exit):");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberId);
			printf("\n");

			upperchar[0] = newMemberInfo.memberId[0];
			newMemberInfo.memberId[0] = toupper(upperchar[0]);

			if (newMemberInfo.memberId[0] == 'X' && newMemberInfo.memberId[1] == '\0')
			{
				break;
			}

			for (int j = 0; j < memberSize; j++)
			{
				if (strcmp(newMemberInfo.memberId, memberInfo[j].memberId) == 0)
				{
					printf("Member ID exist!Please reenter.\n");
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
			else
			{
				for (int j = 1; j < strlen(newMemberInfo.memberId); j++)
				{
					if (isalpha(newMemberInfo.memberId[j]))
					{
						printf("Member ID should be start with character \'M\' and following with number.Please reenter!\n");
						memberIDcheck = 0;
						break;
					}
				}
			}
		}

		if (newMemberInfo.memberId[0] == 'X' && newMemberInfo.memberId[1] == '\0')
		{
			system("cls");
			break;
		}
		//Member name
		printf("Enter Name:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.name);
		printf("\n");

		//IC Number and validation
		printf("Enter IC Number:");
		rewind(stdin);
		scanf("%s", &newMemberInfo.memberIC);

		for (int j = 0; j < memberSize; j++)
		{
			while (strcmp(newMemberInfo.memberIC, memberInfo[j].memberIC) == 0 || strlen(newMemberInfo.memberIC) != 12)
			{
				if (strcmp(newMemberInfo.memberIC, memberInfo[j].memberIC) == 0)
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

		//Gender and validation
		do {
			printf("Gender(M/F):");
			rewind(stdin);
			scanf("%c", &newMemberInfo.gender);
			newMemberInfo.gender = toupper(newMemberInfo.gender);
			if (newMemberInfo.gender != 'F' && newMemberInfo.gender != 'M')
				printf("Gender only Male(m) or Female(f).Please reenter.\n");
		} while (newMemberInfo.gender != 'F' && newMemberInfo.gender != 'M'); //Gender only can be Female(f) and Male (m)
		printf("\n");

		do
		{
			printf("Phone number:");
			rewind(stdin);
			scanf("%s", &newMemberInfo.memberPhone);
			if (strlen(newMemberInfo.memberPhone) > 11 || strlen(newMemberInfo.memberPhone) < 9)
				printf("Invalid Phone number(between 10 to 11 number).Please reenter.\n");
		} while (strlen(newMemberInfo.memberPhone) > 11 || strlen(newMemberInfo.memberPhone) < 9);
		printf("\n");


		//Upline ID and validation
		do
		{
		printf("Member got a upline id(Y/N)? ");
		rewind(stdin);
		scanf("%c", &uplineYesNo);
		
			if (tolower(uplineYesNo) == 'y')
			{
				printf("Upline id(UL####):");
				rewind(stdin);
				scanf("%s", &newMemberInfo.uplineId);

				while (strlen(newMemberInfo.uplineId) > 6 || strlen(newMemberInfo.uplineId) < 2)
				{
					printf("Upline ID at least 2 character and maximun 6.Please reenter!\n");
					printf("Enter Upline id:");
					rewind(stdin);
					scanf("%s", &newMemberInfo.uplineId);
				}

				while (newMemberInfo.uplineId[0] != 'U' && newMemberInfo.uplineId[0] != 'u' || (newMemberInfo.uplineId[1] != 'l' && newMemberInfo.uplineId[1] != 'L'))
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

			else if (tolower(uplineYesNo) == 'n')
			{
				strcpy(newMemberInfo.uplineId, "    -");
				printf("\n");
			}
			else
				printf("Please enter valid choice(Y/N).\n");
			
		} while (tolower(uplineYesNo) != 'n' && tolower(uplineYesNo) != 'y');
		printf("\n");

		//Date join validation
		int dateCheck = 0;
		while (dateCheck == 0) {
			printf("Date join(day month year):");
			rewind(stdin);
			scanf("%d %d %d", &newMemberInfo.joinDate.day, &newMemberInfo.joinDate.month, &newMemberInfo.joinDate.year);

			if (newMemberInfo.joinDate.year < 2021)
			{
				printf("Year enter cannot less then Year 2021.Please reenter.\n");
			}

			else if (newMemberInfo.joinDate.day <= 0 || newMemberInfo.joinDate.day > 31)
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
					dateCheck = 1;
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
					dateCheck = 1;
			}

			else
				dateCheck = 1;

		}
		printf("\n");

		//Address 
		printf("Member address1:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add1);
		printf("\n");


		printf("Member address2:");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.add2);
		printf("\n");

		//postcode can be 5 digit only
		printf("Postcode(XXXXX):");
		rewind(stdin);
		scanf("%[^\n]", &newMemberInfo.memberAdd.postcode);
		while (strlen(newMemberInfo.memberAdd.postcode) != 5)
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

		//Confirm to add or not
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

		//write in b.file and get member.
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

		//Wanted to add more or not
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

		if (toupper(continueAdd) == 'N') //if no more adding member,then close file.
			fclose(ptr);

	} while (toupper(continueAdd) == 'Y');


}

//Search Function
void memberSearch(Member memberInfo[], int memberSize)
{
	system("cls");
	Member matchMember[100];
	int matchcount = 0, yearJoin;
	char mID[10], ulID[10], upperchar[3];
	int choice;



	do
	{
		choice = searchMenu();

		switch (choice)
		{
		case 1:
			system("cls");
			printf("Enter member ID(M00001):");
			rewind(stdin);
			scanf("%s", &mID);

			upperchar[0] = mID[0];
			mID[0] = toupper(upperchar[0]);

			matchcount = 0;

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
				printf("\n\n");
				detailDisplay(matchMember, matchcount);
			}


			break;



		case 2:
			system("cls");
			printf("Enter upline ID(UL0001):");
			rewind(stdin);
			scanf("%s", &ulID);

			upperchar[1] = ulID[0];
			ulID[0] = toupper(upperchar[1]);

			upperchar[2] = ulID[1];
			ulID[1] = toupper(upperchar[2]);

			matchcount = 0;

			for (int i = 0; i < memberSize; i++)
			{

				if (((strcmp(ulID, memberInfo[i].uplineId) == 0)))
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
				printf("\n\n");
				detailDisplay(matchMember, matchcount);
			}

			break;

		case 3:
			system("cls");
			printf("Enter Year of joinning(2021):");
			rewind(stdin);
			scanf("%d", &yearJoin);

			matchcount = 0;

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
				printf("\n\n");	
				detailDisplay(matchMember, matchcount);
			}
			break;

		case 4:break;

		}
	} while (choice == 1 || choice == 2 || choice == 3);
}

int searchMenu()
{
	int choice;
	printf("======================================\n");
	printf("\t   Search function\n");
	printf("======================================\n");
	printf("1. Search by Member ID\n");
	printf("2. Search by UpLine ID\n");
	printf("3. Search by Year join\n");
	printf("4. Exit searching\n\n");

	do {
		printf("Enter choice(1-4):");
		rewind(stdin);
		scanf("%d", &choice);

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
			printf("Invalid Choice!Please reenter\n");
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

	return choice;

}

//Modify Function

void modifyMember(Member memberInfo[], int memberSize)
{
	char memberID[10], sureYesNo;
	char newName[40], newPhoneNo[12], newIC[13];
	char upperchar;
	int newDay, newMonth, newYear, wantedIndex;
	int dateCheck = 0;
	int matchcount = 0, selectEdit;
	Member matchMember[2];

	display(memberInfo, memberSize);

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

		if (tolower(memberID[0]) == 'x' && memberID[1] == '\0')
		{
			printf("Bye~~~~\n");
			system("pause");
			break;
		}

		else if (matchcount == 0)
		{
			printf("Member ID does not exist.Please reenter.\n");
		}



	} while (matchcount == 0);


	if (matchcount > 0)
	{
		system("cls");
		printf("\n\n\tMember Found!\n");
		printf("\t============\n");
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
					selectEdit = 0;
					printf("1.Edit Name\n");
					printf("2.Edit Member Phone Number\n");
					printf("3.Edit Member Join Date\n");
					printf("4.Edit IC Number\n");
					printf("5.Exit edit\n\n");
					printf("Select(1-5):");
					rewind(stdin);
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

					case 5: {

					
						FILE *editPtr = fopen("member.bin", "wb");
						for (int i = 0; i < memberSize; i++)
						{
							fwrite(&memberInfo[i], sizeof memberInfo[i], 1, editPtr);
						}
						
						
						fclose(editPtr); 
						printf("Edit member sucessfully!\n");
						system("pause");
						break;
					}
					default:printf("Enter valid selection!\n\n"); system("pause");


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


//Delete Function
void deleteMember(Member memberInfo[], int* memberSize)
{
	char memberID[10], sureDelete, upperchar;
	int matchcount = 0, deleteIndex;
	Member matchMember[2];

	do {


		printf("Enter member ID to delete(X = exit):");
		rewind(stdin);
		scanf("%s", &memberID);

		upperchar = memberID[0];
		memberID[0] = toupper(upperchar);

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
			printf("\n\nMember Found!\n");
			printf("============\n\n");
			displayResult(matchMember, 0);
			printf("\n\n");

			do {
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

					FILE* delPtr = fopen("member.bin", "wb");
					for (int k = 0; k < *memberSize; k++)
					{
						fwrite(&memberInfo[k], sizeof memberInfo[k], 1, delPtr);
					}
					fclose(delPtr);
					printf("\n\nDeleted successfully!\n\n");
					system("pause");
				}

				else if (toupper(sureDelete) == 'N')
				{
					printf("Delete Unsuccessfully!\n");
					system("pause");
				}

				else
					printf("Enter Valid Choice.\n");

			} while (toupper(sureDelete) != 'Y' && toupper(sureDelete) != 'N');
		}

		else if (memberID[0] == 'X' && memberID[1] == '\0')
		{
			matchcount = 1;
			printf("Bye~~~~\n");
			system("pause");
			break;
		}

		else
		{
			printf("Member ID not found!\n\n");

		}

	} while (matchcount == 0);


}

//Report1
void report_buyMost(Member memberInfo[], int memberSize)
{
	system("cls");

	SALES_MEMBER salesOrderMember[MAX_SALES];
	MemberReport report[MAX_MEMBER] = { "M00000",1,0.00 };
	MemberReport temp;
	int salesN = 0;
	char num;

	FILE* fileOpen = fopen("salesRecord.bin", "rb");
	if (fileOpen == NULL) {
		printf("\tError file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}

	while (fread(&salesOrderMember[salesN], sizeof(salesOrderMember[salesN]), 1, fileOpen) != 0) {
		salesN++;
	}


	for (int i = 0; i < memberSize; i++)
	{
		strcpy(report[i].memberId, memberInfo[i].memberId);
		report[i].qtySold = 0;
		report[i].totalSpent = 0.00;
	}

	for (int i = 0; i < salesN; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(salesOrderMember[i].memberId, report[j].memberId) == 0)
			{
				report[j].qtySold += salesOrderMember[i].qtySold;
				report[j].totalSpent += salesOrderMember[i].qtySold * salesOrderMember[i].price;
			}
		}
	}

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = i + 1; j < memberSize; j++)
		{
			if (report[i].qtySold < report[j].qtySold)
			{
				temp = report[i];
				report[i] = report[j];
				report[j] = temp;
			}

		}
	}

	printf("===================================================================================================== \n");
	printf("%-2s   %-30s\t%s\t%s\t%s\n", "", "Name", "Member ID", "TOTAL ITEM BOUGHT", "TOTAL SPENT");
	printf("=====================================================================================================\n");

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(report[i].memberId, memberInfo[j].memberId) == 0)
			{
				printf("%2d.  ", i + 1);
				printf("%-30s", memberInfo[j].name);
			}

		}

		printf("\t%s", report[i].memberId);
		printf("\t\t%d\t\t\t", report[i].qtySold);
		printf("%.2lf\n", report[i].totalSpent);


	}
	printf("=====================================================================================================\n");

	system("pause");
}

//Report2
void report_highestSpent(Member memberInfo[], int memberSize)
{
	system("cls");

	SALES_MEMBER salesOrderMember[MAX_SALES];
	MemberReport report[MAX_MEMBER] = { "M00000",1,0.00 };
	MemberReport temp;
	int salesN = 0;
	char num;

	FILE* fileOpen = fopen("salesRecord.bin", "rb");
	if (fileOpen == NULL) {
		printf("\tError file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}

	while (fread(&salesOrderMember[salesN], sizeof(salesOrderMember[salesN]), 1, fileOpen) != 0) {
		salesN++;
	}


	for (int i = 0; i < memberSize; i++)
	{
		strcpy(report[i].memberId, memberInfo[i].memberId);
		report[i].qtySold = 0;
		report[i].totalSpent = 0.00;
	}

	for (int i = 0; i < salesN; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(salesOrderMember[i].memberId, report[j].memberId) == 0)
			{
				report[j].qtySold += salesOrderMember[i].qtySold;
				report[j].totalSpent += salesOrderMember[i].qtySold * salesOrderMember[i].price;
			}
		}
	}

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = i + 1; j < memberSize; j++)
		{
			if (report[i].totalSpent < report[j].totalSpent)
			{
				temp = report[i];
				report[i] = report[j];
				report[j] = temp;
			}

		}
	}

	printf("===================================================================================================== \n");
	printf("%-2s   %-30s\t%s\t%s\t%s\n", "", "Name", "Member ID", "TOTAL ITEM BOUGHT", "TOTAL SPENT");
	printf("=====================================================================================================\n");

	for (int i = 0; i < memberSize; i++)
	{
		for (int j = 0; j < memberSize; j++)
		{
			if (strcmp(report[i].memberId, memberInfo[j].memberId) == 0)
			{
				printf("%2d.  ", i + 1);
				printf("%-30s", memberInfo[j].name);
			}

		}

		printf("\t%s", report[i].memberId);
		printf("\t\t%d\t\t\t", report[i].qtySold);
		printf("%.2lf\n", report[i].totalSpent);

	}
	printf("=====================================================================================================\n");

	system("pause");
}