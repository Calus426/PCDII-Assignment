#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define MAX_SALES 30

typedef struct {
	int day, month, year;
}DATE;

typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[10];
	DATE date;
}SALES;

void displaySRecord(SALES salesOrder[],int salesN);
void searchSRecord(SALES salesOrder[], int salesN);
void modifySReccord(SALES salesOrder[], int salesN);
int addSRecord(SALES salesOrder[], int salesN);
void popularItem(SALES salesOrder[], int salesN);
void salesReport(SALES salesOrder[], int salesN);

void main() {
	SALES salesOrder[MAX_SALES];
	int option = 0, salesN = 0, i = 0;
//	FILE* fileOpen;
//	fileOpen = fopen("salesRecord.bin", "wb");
//	if (fileOpen == NULL) {
//		printf("Error file \"salesRecord.bin\" cannot be open!\n");
//		return 0;
//	}
//	for (int i = 0; i < 2; i++) {
//		rewind(stdin);
//		printf("enter name : ");
//		scanf(" %[^\n]", &salesOrder[i].salesOrderId);
//		rewind(stdin);
//		printf("enter num : ");
//		scanf(" %[^\n]", &salesOrder[i].itemCode);
//
//		printf("enter num : ");
//		scanf(" %d", &salesOrder[i].qtySold);
//
//		printf("enter num : ");
//		scanf(" %lf", &salesOrder[i].price);
//
//		printf("enter num : ");
//		scanf(" %[^\n]", &salesOrder[i].memberId);
//
//		printf("enter num : ");
//		scanf(" %d/%d/%d", &salesOrder[i].date.day, &salesOrder[i].date.month, &salesOrder[i].date.year);
//
//		fwrite(&salesOrder[i], sizeof(SALES), 1, fileOpen);
//	}
//}
	FILE* fileOpen = fopen("salesRecord.bin", "rb");
	if (fileOpen == NULL) {
		printf("Error file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}
	while (fread(&salesOrder[salesN], sizeof(SALES), 1, fileOpen) != 0 ) {
		salesN++;
	}

	do {
		system("cls");

		printf("WELCOME TO SALES INFORMATION MENU\n");
		printf("1) DISPLAY SALES RECORD\n");
		printf("2) SEARCH  SALES RECORD\n");
		printf("3) MODIFY  SALES RECORD\n");
		printf("4) ADD     SALES RECORD\n");
		printf("5) POPULAR SALES RECORD\n");
		printf("6) SALES REPORT\n");
		printf("7) EXIT\n");


		printf("\nPLEASE ENTER AN OPTION : ");
		rewind(stdin);
		scanf("%d", &option);

		switch (option) {
		case 1: displaySRecord(salesOrder, salesN);
			break;

		case 2: searchSRecord(salesOrder, salesN);
			break;

		case 3: modifySReccord(salesOrder, salesN);
			break;

		case 4: salesN = addSRecord(salesOrder, salesN);
			break;

		case 5: popularItem(salesOrder, salesN);
			break;

		case 6: salesReport(salesOrder, salesN);
			break;

		case 7: 
			FILE* update = fopen("salesRecord.bin", "wb");
			if (update == NULL) {
				printf("Error file \"salesRecord.bin\" cannot be open!\n");
				return 0;
			}
			for (int i = 0; i < salesN; i++) {
				fwrite(&salesOrder[i], sizeof(SALES), 1, update);
			}
			fclose(update);
			printf("\nTHANK YOU HAVE A NICE DAY\n");
			break;

		default: printf("\nPLEASE ENTER A CORRECT OPTION\n");
		}
	} while (option != 7);

	system("pause");
}

void displaySRecord(SALES salesOrder[],int salesN) {
	printf("\nSALES ORDER ID    ITEM CODE    QUANTITY     PRICE    MEMBER ID   SALES DATE\n");
	for (int i = 0; i < salesN; i++) {
		
		printf("%s \t %14s \t %3d\t    $%-3.2f \t %s \t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
			salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	}

	system("pause");
}

void searchSRecord(SALES salesOrder[], int salesN) {
	int opt, i, matchSearch = 0;

	printf("\nSearch Record by : \n");
	printf("1) ID\n");
	printf("2) Item Code\n");
	printf("3) Date\n");
	printf("4) Return\n");

	do {
		printf("\nPLEASE ENTER AN OPTION : ");
		rewind(stdin);
		scanf("%d", &opt);

		switch (opt) {
		case 1: 
			printf("Enter Sales Order Id : ");
			char id[10];
			scanf(" %[^\n]", &id);

			for (i = 0; i < salesN; i++) {
				if (strcmp(id, salesOrder[i].salesOrderId) == 0) {
					printf("%s \t %14s \t %3d\t    $%-3.2f \t %s \t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
						salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
					matchSearch = i;
				}
			}
			if (matchSearch == -1) {
				printf("No matching result found, please enter again.\n");
			}
			system("pause");
			break;

		case 2: 
			printf("Enter Item Code : ");
			char icode[10];
			scanf(" %[^\n]", &icode);
			for (i = 0; i < salesN; i++) {
				if (strcmp(icode, salesOrder[i].itemCode) == 0) {
					printf("%s \t %14s \t %3d\t    $%-3.2f \t %s \t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
						salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
					matchSearch = i;
				}
			}
			if (matchSearch == -1) {
				printf("No matching result found, please enter again.\n");
			}
			system("pause");
			break;

		case 3:
			printf("Enter Sales Date in DD/MM/YYYY Format : ");
			int findDay, findMonth, findYear;
			scanf("%d/%d/%d", &findDay, &findMonth, &findYear);
			for (i = 0; i < salesN; i++) {
				if (findDay == salesOrder[i].date.day && findMonth == salesOrder[i].date.month && findYear == salesOrder[i].date.year) {
					printf("%s \t %14s \t %3d\t    $%-3.2f \t %s \t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
						salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
					matchSearch = i;
				}
			}
			if (matchSearch == -1) {
				printf("No matching result found, please enter again.\n");
			}
			system("pause");
			break;

		case 4: 
			return 0;
			break;

		default: printf("\nPLEASE ENTER A CORRECT OPTION\n");
		}
	} while (opt != 4);

}

void modifySReccord(SALES salesOrder[], int salesN) {
	displaySRecord(salesOrder, salesN);
	printf("\nSelect Sales Order Id to modify : ");
	char id[10];
	scanf(" %[^\n]", &id);

	int i, matchSearch = 0;
	for (i = 0; i < salesN; i++) {
		if (strcmp(id, salesOrder[i].salesOrderId) == 0) {
			matchSearch = i;
		}
	}
	if (matchSearch == -1) {
		printf("No matching result found, please enter again.\n");
	}
	else {
		int opt;
		do {
			system("cls");
			printf("1) Item Code\n");
			printf("2) Quantity Sold\n");
			printf("3) Price\n");
			printf("4) Member ID\n");
			printf("5) Sales Date\n");
			printf("6) Return\n");
			printf("\nSelect Which Field To Modify : ");
			rewind(stdin);
			scanf(" %d", &opt);
			printf("\n");
			switch (opt) {
			case 1: printf("Enter New Sold Item Code : ");
					scanf(" %[^\n]", &salesOrder[matchSearch].itemCode);
				break;

			case 2: printf("Enter Quantity Sold : ");
					scanf(" %d", &salesOrder[matchSearch].qtySold);
				break;

			case 3: printf("Enter Sold Item  Price : ");
					scanf(" %lf", &salesOrder[matchSearch].price);
				break;

			case 4: printf("Enter Member Id : ");
					scanf(" %[^\n]", &salesOrder[matchSearch].memberId);
				break;

			case 5: printf("Enter Sold Date : ");
					scanf(" %d/%d/%d", &salesOrder[matchSearch].date.day, &salesOrder[matchSearch].date.month, &salesOrder[matchSearch].date.year);
				break;

			case 6: return 0;
				break;

			default: printf("\nPLEASE ENTER A CORRECT OPTION\n");
			}
		} while (opt != 6);

	}
	system("pause");
}

int addSRecord(SALES salesOrder[], int salesN) {
	char yn;
	do {
		printf("\nEnter New Sales Order Id : ");
		scanf(" %s", &salesOrder[salesN].salesOrderId);

		printf("\nEnter New Sold Item Code : ");
		scanf(" %s", &salesOrder[salesN].itemCode);

		printf("\nEnter Quantity Sold : ");
		scanf(" %d", &salesOrder[salesN].qtySold);

		printf("\nEnter Sold Item  Price : ");
		scanf(" %lf", &salesOrder[salesN].price);

		printf("\nEnter Member Id : ");
		scanf(" %s", &salesOrder[salesN].memberId);

		printf("\nEnter Sold Date : ");
		scanf(" %d/%d/%d", &salesOrder[salesN].date.day, &salesOrder[salesN].date.month, &salesOrder[salesN].date.year);
		salesN++;
		printf("\nDo you want to continue adding? (Y/N) : ");
		scanf(" %c", &yn);
		if (toupper(yn) == 'N') {
			return salesN;
		}
	} while (salesN != MAX_SALES);
	return salesN;
	system("pause");
}

void popularItem(SALES salesOrder[], int salesN) {

}


void salesReport(SALES salesOrder[], int salesN) {
	printf("you are in sales\n");
	for (int i = 0; i < salesN; i++) {

	}
	system("pause");
}