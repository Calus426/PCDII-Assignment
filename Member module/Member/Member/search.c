//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <math.h>
//#include <string.h>
//#pragma warning (disable:4996)
//
//typedef struct {
//	int day, month, year;
//}Date;
//
//typedef struct {
//	char add1[40], add2[40], postcode[6], city[40], state[40];
//
//}Address;
//
//typedef struct
//{
//	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7 ];
//	Date joinDate;
//	Address memberAdd;
//}Member;
//
//
//void search(Member memberInfo[], int memberSize)
//{
//	system("cls");
//	Member matchMember[100];
//	int matchcount = 0, yearJoin;
//	char mID[10], ulID[10],upperchar[3];
//	int choice;
//	
//
//
//	do
//	{
//		choice = searchMenu();
//
//		switch (choice)
//		{
//		case 1:
//			system("cls");
//			printf("Enter member ID(M00001):");
//			rewind(stdin);
//			scanf("%s", &mID);
//
//			upperchar[0] = mID[0];
//			mID[0] = toupper(upperchar[0]);
//
//			matchcount = 0;
//
//			for (int i = 0; i < memberSize; i++)
//			{
//
//				if (((strcmp(mID, memberInfo[i].memberId) == 0)))
//				{
//					matchMember[matchcount] = memberInfo[i];
//					matchcount++;
//				}
//
//			}
//			if (matchcount == 0)
//			{
//				printf("No member found!\n\n");
//				system("pause");
//			}
//			else
//			{
//				detailDisplay(matchMember, matchcount);
//			}
//
//			
//			break;
//
//
//
//		case 2:
//			system("cls");
//			printf("Enter upline ID(UL0001):");
//			rewind(stdin);
//			scanf("%s", &ulID);
//
//			upperchar[1] = ulID[0];
//			ulID[0] = toupper(upperchar[1]);
//
//			upperchar[2] = ulID[1];
//			ulID[1] = toupper(upperchar[2]);
//
//			matchcount = 0;
//
//			for (int i = 0; i < memberSize; i++)
//			{
//
//				if (((strcmp(ulID, memberInfo[i].uplineId) == 0)))
//				{
//					matchMember[matchcount] = memberInfo[i];
//					matchcount++;
//				}
//
//			}
//			if (matchcount == 0)
//			{
//				printf("No member found!\n\n");
//				system("pause");
//			}
//			else
//			{
//				detailDisplay(matchMember, matchcount);
//			}
//
//			break;
//
//		case 3:
//			system("cls");
//			printf("Enter Year of joinning(2021):");
//			rewind(stdin);
//			scanf("%d", &yearJoin);
//
//			matchcount = 0;
//
//			for (int i = 0; i < memberSize; i++)
//			{
//
//				if (yearJoin == memberInfo[i].joinDate.year)
//				{
//					matchMember[matchcount] = memberInfo[i];
//					matchcount++;
//				}
//
//			}
//
//			if (matchcount == 0)
//			{
//				printf("No member found!\n\n");
//				system("pause");
//			}
//			else
//			{
//				detailDisplay(matchMember, matchcount);
//			}
//			break;
//
//		case 4:break;
//
//		}
//	}while (choice == 1 || choice == 2 || choice == 3);
//}
//
//int searchMenu()
//{
//	int choice;
//	printf("======================================\n");
//	printf("\t\tSearch function\n");
//	printf("======================================\n");
//	printf("1. Search by Member ID\n");
//	printf("2. Search by UpLine ID\n");
//	printf("3. Search by Year join\n");
//	printf("4. Exit searching\n\n");
//
//	do {
//		printf("Enter choice(1-4):");
//		rewind(stdin);
//		scanf("%d", &choice);
//
//		if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
//			printf("Invalid Choice!Please reenter\n");
//	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
//
//	return choice;
//
//}
