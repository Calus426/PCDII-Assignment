#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning (disable:4996)

void menu() {
	int choice;

	
	do {
		system("cls");
		printf("========================\n");
		printf("Choose ur next move!!\n");
		printf("========================\n\n\n");
		printf("1.Display member\n");
		printf("2.Add member\n");
		printf("3.Search member\n");
		printf("4.Modify member\n");
		printf("5.Remove member\n");
		printf("6.Member commision\n");
		printf("7.Exit\n\n\n");
		printf("Enter choice:");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: display(); break;
		case 2: addMember(); break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7:break;
		default:printf("Enter valid choice!\n");
		}
	} while (choice != 7);
		
}