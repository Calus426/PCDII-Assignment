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

void displaySRecord(SALES salesOrder[], int salesN);
void searchSRecord(SALES salesOrder[], int salesN);
void result(SALES salesOrder[], int i);
void modifySReccord(SALES salesOrder[], int salesN);
int addSRecord(SALES salesOrder[], int salesN);
void popularItem(SALES salesOrder[], int salesN);
void salesReport(SALES salesOrder[], int salesN);
void header();
void validation(int matchSearch);

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
		printf("\tError file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}
	while (fread(&salesOrder[salesN], sizeof(SALES), 1, fileOpen) != 0) {
		salesN++;
	}

	do {
		system("cls");
		printf("\t==================================\n");
		printf("\tWELCOME TO SALES INFORMATION MENU\n");
		printf("\t==================================\n");
		printf("\t1) DISPLAY SALES RECORD\n");
		printf("\t2) SEARCH  SALES RECORD\n");
		printf("\t3) MODIFY  SALES RECORD\n");
		printf("\t4) ADD     SALES RECORD\n");
		printf("\t5) POPULAR SALES RECORD\n");
		printf("\t6) SALES REPORT\n");
		printf("\t7) EXIT\n");
		printf("\t==================================\n");
		printf("\tPLEASE ENTER AN OPTION : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\t==================================\n");
		switch (option) {
		case 1: displaySRecord(salesOrder, salesN);
			break;

		case 2: searchSRecord(salesOrder, salesN);
			break;

		case 3: modifySReccord(salesOrder, salesN);
			break;

		case 4: salesN = addSRecord(salesOrder, salesN);
			break;

		case 5: //popularItem(salesOrder, salesN);
			break;

		case 6: /*salesReport(salesOrder, salesN);*/
			break;

		case 7:
			FILE * update = fopen("salesRecord.bin", "wb");
			if (update == NULL) {
				printf("\tError file \"salesRecord.bin\" cannot be open!\n");
				return 0;
			}
			for (int i = 0; i < salesN; i++) {
				fwrite(&salesOrder[i], sizeof(SALES), 1, update);
			}
			fclose(update);
			printf("\n\t\t\tTHANK YOU HAVE A NICE DAY\n\n");
			break;

		default: printf("\n\tPLEASE ENTER A CORRECT OPTION\n");
		}
	} while (option != 7);

	system("pause");
}

void displaySRecord(SALES salesOrder[], int salesN) {
	printf("\n\t\t\t\t\tAll Sales Order Record\n");
	header();
	for (int i = 0; i < salesN; i++) {

		printf("\t%s \t %14s \t %3d\t      $%-3.2f \t      %s\t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
			salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	}
	printf("\t=====================================================================================\n");
	system("pause");
}

void searchSRecord(SALES salesOrder[], int salesN) {
	int opt, i, matchSearch;
	printf("\n\t\t\tSearch Record\n");
	printf("\n\tSearch Record by : \n");
	printf("\t===============================\n");
	do {
		opt = 0, matchSearch = -1;
		printf("\t1) ID\n");
		printf("\t2) Item Code\n");
		printf("\t3) Date\n");
		printf("\t4) Return\n");
		printf("\t===============================\n");
		printf("\tPLEASE ENTER AN OPTION : ");
		rewind(stdin);
		scanf("%d", &opt);
		printf("\t===============================\n");
		switch (opt) {
		case 1:
			do {
				matchSearch = -1;
				printf("\tEnter Sales Order Id (Enter X to exit) : ");
				char id[10];
				scanf(" %[^\n]", &id);
				printf("\t===============================\n");
				if (strcmp(tolower(id), "x") == 0) {
					return 0;
				}
				for (i = 0; i < salesN; i++) {
					if (strcmp(id, salesOrder[i].salesOrderId) == 0) {
						result(salesOrder, i);
						matchSearch = i;
					}
				}
				validation(matchSearch);
			} while (matchSearch == -1);
			break;

		case 2:
			do {
				matchSearch = -1;
				printf("\tEnter Item Code (Enter X to exit): ");
				char icode[10];
				scanf(" %[^\n]", &icode);
				printf("\t===============================\n");
				if (strcmp(toupper(icode), "x") == 0) {
					return 0;
				}
				for (i = 0; i < salesN; i++) {
					if (strcmp(icode, salesOrder[i].itemCode) == 0) {
						result(salesOrder, i);
						matchSearch = i;
					}
				}
				validation(matchSearch);
			} while (matchSearch == -1);
			break;

		case 3:
			int select = 0;
			do {
				printf("\t1) Day\n");
				printf("\t2) Month\n");
				printf("\t3) Year\n");
				printf("\t4) Return\n");
				printf("\t===============================\n");
				printf("\tSearch By : ");
				int findDay, findMonth, findYear;
				scanf("%d", &select);
				switch (select) {
				case 1:
					do {
						findDay = 0;
						matchSearch = -1;
						printf("\t===============================\n");
						printf("\tEnter Sales Date (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findDay);
						printf("\t===============================\n");
						if (findDay < 0) {
							return 0;
						}
						for (i = 0; i < salesN; i++) {
							if (findDay == salesOrder[i].date.day) {
								result(salesOrder, i);
								matchSearch = i;
							}
						}
						validation(matchSearch);
					} while (matchSearch == -1);
					break;
				case 2:
					do {
						findMonth = 0;
						matchSearch = -1;
						printf("\t===============================\n");
						printf("\tEnter Sales Month (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findMonth);
						printf("\t===============================\n");
						if (findMonth < 0) {
							return 0;
						}
						for (i = 0; i < salesN; i++) {
							if (findMonth == salesOrder[i].date.month) {
								result(salesOrder, i);
								matchSearch = i;
							}
						}
						validation(matchSearch);
					} while (matchSearch == -1);
					break;
				case 3:
					do {
						findYear = 0;
						matchSearch = -1;
						printf("\t===============================\n");
						printf("\tEnter Sales Year (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findYear);
						printf("\t===============================\n");
						if (findYear < 0) {
							return 0;
						}
						for (i = 0; i < salesN; i++) {
							if (findYear == salesOrder[i].date.year) {
								result(salesOrder, i);
								matchSearch = i;
							}
						}
						validation(matchSearch);
					} while (matchSearch == -1);
					break;
				case 4: return 0;
					break;
				default:printf("\n\tPLEASE ENTER A CORRECT OPTION\n\n");
					printf("\t===============================\n");
				}
			} while (select != 4);
			break;

		case 4:
			return 0;
			break;

		default: printf("\n\tPLEASE ENTER A CORRECT OPTION\n\n");
			printf("\t===============================\n");
		}
	} while (opt != 4);
}

void modifySReccord(SALES salesOrder[], int salesN) {
	displaySRecord(salesOrder, salesN);
	int i, matchSearch;
	do {
		matchSearch = -1;
		printf("\n\t===============================\n");
		printf("\tSelect Sales Order Id to modify (Enter X to exit) : ");
		char id[10];
		scanf(" %[^\n]", &id);
		if (strcmp(tolower(id), "x") == 0) {
			return 0;
		}
		for (i = 0; i < salesN; i++) {
			if (strcmp(id, salesOrder[i].salesOrderId) == 0) {
				matchSearch = i;
			}
		}
		if (matchSearch == -1) {
			printf("\n\tNo matching result found, please enter again from Sales Menu.\n\n");
		}
		else {
			int opt, j;
			do {
				printf("\n\t===============================\n");
				printf("\t1) Item Code\n");
				printf("\t2) Quantity Sold\n");
				printf("\t3) Price\n");
				printf("\t4) Member ID\n");
				printf("\t5) Sales Date\n");
				printf("\t6) Return\n");
				printf("\t===============================\n");
				printf("\n\tSelect Which Field To Modify : ");
				rewind(stdin);
				scanf(" %d", &opt);
				printf("\t===============================\n");
				printf("\n");
				switch (opt) {
				case 1:
					do {
						printf("\tEnter New Sold Item Code : ");
						char newICode[10];
						j = 0;
						scanf(" %[^\n]", &newICode[10]);
						if (strcmp(tolower(newICode), "x") == 0) {
							return 0;
						}
						//for (i = 0; i < salesN; i++) {
						//	if (strcmp(newICode,/*get from terence*/) == 0) {
						//		strcpy(salesOrder[matchSearch].itemCode, newICode);
						//		j++;
						//	}
						//}
						if (j == 0) {
							printf("\n\tInvalid Item Code Entered, Please Select Again\n\n");
						}
					} while (j == 0);
					break;

				case 2:
					printf("\tEnter Quantity Sold : ");
					int newSold;
					scanf(" %d", &newSold);
					if (newSold > 0 && newSold < 100) {
						salesOrder[matchSearch].qtySold = newSold;
					}
					else {
						printf("\n\tInvalid Quantity Entered, Please Select Again\n\n");
					}
					break;

				case 3: printf("\tEnter Sold Item Price : ");
					double newPrice;
					scanf(" %lf", &newPrice);
					if (newPrice > 0 && newPrice < 10000) {
						salesOrder[matchSearch].price = newPrice;
					}
					else {
						printf("\n\tInvalid Amount Entered, Please Select Again\n\n");
					}
					break;

				case 4: printf("\tEnter Member Id : ");
					char newMID[10];
					j = 0;
					scanf(" %[^\n]", &newMID);
					//for (i = 0; i < salesN; i++) {
					//	if (strcmp(newMID,/*get from Lucas*/) == 0) {
					//		strcpy(salesOrder[matchSearch].memberId, newMID);
					//		j++;
					//	}
					//}
					if (j == 0) {
						//	printf("\n\n\tInvalid Member ID Entered, Please Select Again\n\n");
					}
					break;

				case 5: printf("\tEnter Sold Date (Please Follow DD/MM/YYYY Format) : ");
					int newDay, newMonth, newYear;
					scanf(" %d/%d/%d", &newDay, &newMonth, &newYear);
					if (newDay > 0 && newDay < 31 && newMonth > 0 && newMonth < 13 && newYear > 2000 && newYear < 2024) {
						salesOrder[matchSearch].date.day = newDay;
						salesOrder[matchSearch].date.month = newMonth;
						salesOrder[matchSearch].date.year = newYear;
					}
					else {
						printf("\n\tInvalid Date Entered, Please Select Again\n\n");
					}
					break;

				case 6: return 0;
					break;

				default: printf("\n\tPLEASE ENTER A CORRECT OPTION\n");
				}
			} while (opt != 6);

		}
	} while (matchSearch == -1);
	system("pause");
}

int addSRecord(SALES salesOrder[], int salesN) {
	char yn, addsales[10], additemC[10], addmemID[10], minSalesId[10];
	strcpy(minSalesId, salesOrder[salesN - 1].salesOrderId);
	double addSprice;
	int addquan, adddate, addmonth, addyear, i, valid;
	do {
		do {
			valid = 0;
			printf("\n\tEnter New Sales Order Id : ");
			scanf(" %s", &addsales);
			printf("\n\t===============================\n");
			if (strcmp(addsales, "s200") <= 0 && strcmp(addsales, minSalesId) >= 0) {
				strcpy(salesOrder[salesN].salesOrderId, addsales);
				valid++;
			}
			else {
				printf("\n\tInvalid Sales Order Id Entered, Please Select And Enter Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);

		do {
			valid = 1;
			printf("\n\tEnter New Sold Item Code : ");
			scanf(" %s", &additemC);
			printf("\n\t===============================\n");
			//for (i = 0; i </*from terence*/; i++) {
			//	if (strcmp(additemC,/*from terence*/) == 1) {
			//		strcpy(salesOrder[salesN].itemCode, additemC);
			//		valid++;
			//	}
			//}
			//if (valid == 0) {
			//	printf("\nInvalid Item Id Entered, Please Select And Enter Again");
			//	printf("\n\t===============================\n");
			//}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\tEnter Quantity Sold : ");
			rewind(stdin);
			scanf(" %d", &addquan);
			printf("\n\t===============================\n");
			if (addquan > 0 && addquan < 99) {
				salesOrder[salesN].qtySold = addquan;
				valid++;
			}
			else {
				printf("\n\tInvalid Quantity Entered, Please Select And Enter Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\tEnter Sold Item  Price : ");
			rewind(stdin);
			scanf(" %lf", &addSprice);
			printf("\n\t===============================\n");
			if (addSprice > 0 && addSprice < 9999) {
				salesOrder[salesN].price = addSprice;
				valid++;
			}
			else {
				printf("\n\tInvalid Sold Price Entered, Please Select And Enter Again");
				printf("\n\t===============================\n");

			}
		} while (valid == 0);

		do {
			valid = 1;
			printf("\n\tEnter Member Id : ");
			scanf(" %s", &addmemID);
			printf("\n\t===============================\n");
			//for (i = 0; i </*from Lucas*/; i++) {
			//	if (strcmp(addmemID,/*from lucas*/) == 1) {
			//		strcpy(salesOrder[salesN].memberId, addmemID);
			//		valid++;
			//	}
			//}
			//if(valid==0) {
			//	printf("\nInvalid Member Id Entered, Please Select And Enter Again");
			// printf("\n\t===============================\n");
			//}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\tEnter Sold Date By Following (DD/MM/YYYY) : ");
			scanf(" %d/%d/%d", &adddate, &addmonth, &addyear);
			printf("\n\t===============================\n");
			if (adddate > 0 && adddate < 31 && addmonth > 0 && addmonth < 13 && addyear > 2000 && addyear < 2024) {
				salesOrder[salesN].date.day = adddate;
				salesOrder[salesN].date.month = addmonth;
				salesOrder[salesN].date.year = addyear;
				valid++;
			}
			else {
				printf("\n\n\tInvalid Date Entered, Please Select Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);

		salesN++;
		printf("\n\tDo you want to continue adding? (Y/N) : ");
		scanf(" %c", &yn);
		if (toupper(yn) == 'N') {
			displaySRecord(salesOrder, salesN);
			return salesN;
		}
	} while (salesN != MAX_SALES);
	return salesN;
	system("pause");
}

//void popularItem(SALES salesOrder[], int salesN) {
//	int itemSold[20], popular = -99;
//	char popularItem[6];
//	
//	for (int i = 0; i < salesN; i++) {
//		for (int j = 0; j </*get from terence*/; j++) {
//			if (strcmp(salesOrder[j].itemCode,/*get from terence */) == 0) {
//				itemSold[i] += salesOrder[j].qtySold;
//			}
//		}
//	}
//	printf("\nItem Sold List\n");
//	printf("Item Code\t\tUnit Sold\n");
//	printf("=========\t\t==========\n");
//	for (int i = 0; i < 10; i++) {
//		printf("%s \t %d\n", /*get from terence item 1*/, itemSold[i]);
//		if (itemSold[i] > popular) {
//			popular = itemSold[i];
//			strcpy(popularItem,/*get from terence*/);
//		}
//	}
//	printf("\nThe most popular item sold is %s which sold %d unit.\n",/*get from terence*/, popular);
//	system("pause");
//}

//void salesReport(SALES salesOrder[], int salesN) {
//	header();
//	for (int i = 0; i < salesN; i++) {
//		for (int j = 0; j </*get from lucas*/; j++) {
//			if (strcmp(salesOrder[j].memberId,/*get from lucas*/) == 0) {
//
//			}
//		}
//	}
//	system("pause");
//}

void header() {
	printf("\t=====================================================================================\n");
	printf("\tSALES ORDER ID    ITEM CODE    QUANTITY     SALES AMOUNT    MEMBER ID    SALES DATE\n");
	printf("\t=====================================================================================\n");
}
void result(SALES salesOrder[], int i) {
	printf("\tSales Order ID  : %s \n\tItem Code \t: %s \n\tUnit Sold \t: %d\n\tSales Amount \t: $%-3.2f \n\tMember ID \t: %s \n\tSales Date  \t: %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
		salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	printf("\t===============================\n");
}
void validation(int matchSearch) {
	if (matchSearch == -1) {
		printf("\n\tNo matching result found, please enter again.\n\n");
		printf("\t===============================\n");
	}
}