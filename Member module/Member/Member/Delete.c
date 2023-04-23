//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <math.h>
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
//	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7];
//	Date joinDate;
//	Address memberAdd;
//}Member;
//
//void deleteMember(Member memberInfo[], int *memberSize)
//{
//	char memberID[10], sureDelete,upperchar;
//	int matchcount = 0, deleteIndex;
//	Member matchMember[2];
//
//	do {
//
//	
//	printf("Enter member ID to delete(X = exit):");
//	rewind(stdin);
//	scanf("%s", &memberID);
//
//	upperchar = memberID[0];
//	memberID[0] = toupper(upperchar);
//
//	for (int i = 0; i < *memberSize; i++)
//	{
//
//		if (((strcmp(memberID, memberInfo[i].memberId) == 0)))
//		{
//			matchMember[matchcount] = memberInfo[i];
//			deleteIndex = i;
//			matchcount++;
//		}
//	}
//
//	if (matchcount > 0)
//	{
//		printf("\n\nMember Found!\n");
//		printf("============\n\n");
//		displayResult(matchMember, 0);
//		printf("\n\n");
//
//		do {
//			printf("Are you sure to delete this member(Y/N)?");
//			rewind(stdin);
//			scanf("%c", &sureDelete);
//
//			if (toupper(sureDelete) == 'Y')
//			{
//				for (int j = deleteIndex; j < *memberSize; j++)
//				{
//					memberInfo[j] = memberInfo[j + 1];
//				}
//				(*memberSize)--;
//
//				FILE* delPtr = fopen("member.bin", "wb");
//				for (int k = 0; k < *memberSize; k++)
//				{
//					fwrite(&memberInfo[k], sizeof memberInfo[k], 1, delPtr);
//				}
//				fclose(delPtr);
//				printf("\n\nDeleted successfully!\n\n");
//			}
//
//			else if (toupper(sureDelete) == 'N')
//			{
//				printf("Delete Unsuccessfully!\n");
//				system("pause");
//			}
//
//			else
//				printf("Enter Valid Choice.\n");
//
//		} while (toupper(sureDelete) != 'Y' && toupper(sureDelete) != 'N');
//	}
//	
//	else if (memberID[0] == 'X' && memberID[1] == '\0')
//	{
//		matchcount = 1;
//		printf("Bye~~~~\n");
//		system("pause");
//		break;
//	}
//
//	else
//	{
//		printf("Member ID not found!\n\n");
//		
//	}
//
//	} while (matchcount == 0);
//	
//
//}