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

void display(Member memberInfo[],int memberSize)
{


	printf("    %-20s %-10s %-7s %-13s %-10s %s\n", "Name", "Member Id", "Gender", "Phone Number", "Upline Id","Join Date");
	printf("    %-20s %-10s %-7s %-13s %-10s %s\n","==============","=========","======","============","=========","==========");

	for (int i = 0; i < memberSize; i++) {
		printf("%d.  %-20s %-10s %-7c %-13s %-10s %.2d-%.2d-%d\n",i+1, memberInfo[i].name, memberInfo[i].memberId, memberInfo[i].gender, memberInfo[i].memberPhone, memberInfo[i].uplineId,
			memberInfo[i].joinDate.day, memberInfo[i].joinDate.month, memberInfo[i].joinDate.year);
	}
	
	system("pause");
}