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
	char name[40], memberId[7],memberIC[13],gender, memberPhone[12], uplineId[7];
	Date joinDate;
	Address memberAdd;
}Member;

typedef struct {
	char memberId[10];
	int qtySold;
}MemberReport;


void addMember(Member[], int);
void display (Member[], int );
void getMember(Member[], int *);
void search(Member[],int);
void detailDisplay(Member memberInfo[], int memberSize);
int searchMenu();
void modifyMember(Member memberInfo[], int memberSize);
void deleteMember(Member memberInfo[], int *memberSize);
void displayResult(Member memberInfo[], int memberSize);
void report(Member memberInfo[], int memberSize);
void report2(Member memberInfo[], int memberSize);

void main() //Menu for Member Module
{ 
	Member member[100];
	int memberSize;
	getMember(member, &memberSize);
	int choice;

	do {
		choice = 0;
		printf("\t\t========================\n");
		printf("\t\tChoose ur next move!!\n");
		printf("\t\t========================\n\n\n");
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

		case 2:  addMember(member, memberSize); getMember(member, &memberSize); break;
		case 3:  search(member, memberSize); system("cls"); break;
		case 4:  modifyMember(member, memberSize);	system("cls"); break;
		case 5:  display(member, memberSize);deleteMember(member, &memberSize); system("cls"); break;
		case 6:	 report(member, memberSize); system("cls"); break;
		case 7:  report2(member, memberSize); system("cls"); break;
		case 8:  break;
		default:printf("Enter valid choice!(1-7)\n"); system("pause"); system("cls");
		}

	} while (choice != 8);

}

