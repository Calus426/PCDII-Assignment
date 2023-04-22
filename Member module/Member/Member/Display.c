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



void display(Member memberInfo[],int memberSize)
{
	system("cls");

	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %s\n", " Name", "Member Id","IC", "Gender", "Phone Number", "Upline Id","Join Date");
	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %s\n","=================","=========","=============","======","============","=========","==========");

	for (int i = 0; i < memberSize; i++) {
		printf("%2d.  %-20s %-10s %-13s %-7c %-13s %-10s %.2d-%.2d-%d\n",i+1, memberInfo[i].name, memberInfo[i].memberId, memberInfo[i].memberIC, toupper(memberInfo[i].gender), memberInfo[i].memberPhone, memberInfo[i].uplineId,
			memberInfo[i].joinDate.day, memberInfo[i].joinDate.month, memberInfo[i].joinDate.year);
	}
	printf("==============================================================================================\n\n");

}

void detailDisplay(Member memberInfo[], int memberSize)
{

	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %-12s % s\n", " Name", "Member Id","IC", "Gender", "Phone Number", "Upline Id", "Join Date","Address");
	printf("    %-21s %-10s %-13s %-7s %-13s %-10s %-12s %s\n", "==============", "=========", "=============","======", "============", "=========", "==========", "========================================================");

	for (int i = 0; i < memberSize; i++) {
		printf("%2d.  %-20s %-10s %-13s %-7c %-13s %-10s %.2d-%.2d-%d   %s,%s,%s,%s,%s\n", i + 1, memberInfo[i].name, memberInfo[i].memberId,memberInfo[i].memberIC, toupper(memberInfo[i].gender), memberInfo[i].memberPhone, memberInfo[i].uplineId,
			memberInfo[i].joinDate.day, memberInfo[i].joinDate.month, memberInfo[i].joinDate.year,memberInfo[i].memberAdd.add1, memberInfo[i].memberAdd.add2, memberInfo[i].memberAdd.postcode, 
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
	printf("\tMember ID:\t%s \n", memberInfo[memberSize].memberId );
	printf("\tIC Number:\t%s \n", memberInfo[memberSize].memberIC);
	printf("\tGender:\t\t%c\n", memberInfo[memberSize].gender);
	printf("\tPhone Number:\t%s \n", memberInfo[memberSize].memberPhone);
	printf("\tUpline ID:\t%s \n", memberInfo[memberSize].uplineId);
	printf("\tDate of Join:\t%.2d-%.2d-%d \n", memberInfo[memberSize].joinDate.day, memberInfo[memberSize].joinDate.month, memberInfo[memberSize].joinDate.year);
	printf("\tAddress:\t%s,%s,%s,%s,%s \n", memberInfo[memberSize].memberAdd.add1, memberInfo[memberSize].memberAdd.add2, memberInfo[memberSize].memberAdd.postcode,
		memberInfo[memberSize].memberAdd.city, memberInfo[memberSize].memberAdd.state);
	printf("\t__________________________________________________________________________\n");

}