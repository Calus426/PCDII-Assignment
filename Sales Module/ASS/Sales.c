#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define MAX_SALES 30

//used by everyone
typedef struct {
	int day, month, year;
}Date;
//struct from lucas
typedef struct {
	char add1[40], add2[40], postcode[6], city[40], state[40];

}Address;

typedef struct
{
	char name[40], memberId[7], memberIC[13], gender, memberPhone[12], uplineId[7];
	Date joinDate;
	Address memberAdd;
}Member;

//data field that will be use by the sale information module

typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[10];
	Date date;
}SALES;

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

void getSales(SALES salesOrder[], int *salesNum) {
	//file opening
	FILE* fileOpen = fopen("salesRecord.bin", "rb");
	if (fileOpen == NULL) {
		printf("\tError file \"salesRecord.bin\" cannot be open!\n");
		return 0;
	}
	*salesNum = 0;
	//ensure file open succesfully
	while (fread(&salesOrder[*salesNum], sizeof(SALES), 1, fileOpen) != 0) {
		(*salesNum)++;
	}
}

//function of the sales information module
void displaySRecord(SALES salesOrder[],int salesNum);
void searchSRecord(SALES salesOrder[], int salesNum);
void result(SALES salesOrder[], int i);
void modifySReccord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize);
int addSRecord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize);
void popularItem(SALES salesOrder[], int salesNum);
void salesCommissionReport(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize);
void totalSalesReport(SALES salesOrder[], int salesNum);
void header();
void validation(int matchSearch);

void main() {
	//read lucas and terence's file
	Member memberInfo[20];
	int memberSize = 0;
	getMember(memberInfo, &memberSize);

	SALES salesOrder[MAX_SALES];
	int option = 0, salesNum = 0, i = 0;
	getSales(salesOrder, &salesNum);

	do {
		//showing the menu
		system("cls");
		printf("\t==================================\n");
		printf("\tWELCOME TO SALES INFORMATION MENU\n");
		printf("\t==================================\n");
		printf("\t1) DISPLAY SALES RECORD\n");
		printf("\t2) SEARCH  SALES RECORD\n");
		printf("\t3) MODIFY  SALES RECORD\n");
		printf("\t4) ADD     SALES RECORD\n");
		printf("\t5) POPULAR SALES RECORD\n");
		printf("\t6) SALES   COMMISSIONS REPORT\n");
		printf("\t7) TOTAL   SALES REPORT\n");
		printf("\t8) EXIT\n");
		printf("\t==================================\n");
		printf("\tPLEASE ENTER AN OPTION : ");
		rewind(stdin);
		//select an option to go to desired function
		scanf("%d", &option);
		printf("\t==================================\n");
		switch (option) {
		case 1: displaySRecord(salesOrder, salesNum);
				system("pause");
			break;

		case 2: searchSRecord(salesOrder, salesNum);
			break;

		case 3: modifySReccord(salesOrder, salesNum, memberInfo, memberSize);
			break;

		case 4: salesNum = addSRecord(salesOrder, salesNum, memberInfo, memberSize);
			break;

		case 5: popularItem(salesOrder, salesNum);
			break;

		case 6: salesCommissionReport(salesOrder, salesNum, memberInfo, memberSize);
			break;

		case 7: totalSalesReport(salesOrder, salesNum);
			break;

		case 8: 
			FILE* update = fopen("salesRecord.bin", "wb");
			if (update == NULL) {
				printf("\tError file \"salesRecord.bin\" cannot be open!\n");
				return 0;
			}
			for (int i = 0; i < salesNum; i++) {
				fwrite(&salesOrder[i], sizeof(SALES), 1, update);
			}
			fclose(update);
			printf("\n\t\t\tTHANK YOU HAVE A NICE DAY\n\n");
			break;

		default: printf("\n\tPLEASE ENTER A CORRECT OPTION\n");
				system("pause");
		}
	} while (option != 8);

	system("pause");
}

void displaySRecord(SALES salesOrder[],int salesNum) {
	//display all sales information inside of sales record file
	printf("\n\t\t\t\t\tAll Sales Order Record\n");
	header();
	for (int i = 0; i < salesNum; i++) {
		
		printf("\t%s \t %14s \t %3d\t     $ %7.2f \t      %s\t %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
			salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	}
	printf("\t===================================================================================\n");
}

void searchSRecord(SALES salesOrder[], int salesNum) {
	int opt, i, matchSearch;
	printf("\n\t\t\tSearch Record\n");
	printf("\n\tSearch Record by : \n");
	printf("\t===============================\n");
	do {
		//allow use to filter and search for sales record
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
				//compare to exit
				if (strcmp(tolower(id), "x") == 0) {
					return 0;
				}
				for (i = 0; i < salesNum; i++) {
					if (strcmp(id, salesOrder[i].salesOrderId) == 0) {
						//display data from sales record file
						result(salesOrder, i);
						matchSearch = i;
					}
				}
				//validating data inputed by user
				validation(matchSearch);
			} while (matchSearch == -1);
			break;

		case 2: 
			do {
				matchSearch = -1;
				printf("\tEnter Item Code (Enter X to exit): ");
				char findItemCode[10];
				scanf(" %[^\n]", &findItemCode);
				printf("\t===============================\n");
				if (strcmp(toupper(findItemCode), "x") == 0) {
					return 0;
				}
				for (i = 0; i < salesNum; i++) {
					if (strcmp(findItemCode, salesOrder[i].itemCode) == 0) {
						result(salesOrder, i);
						matchSearch = i;
					}
				}
				validation(matchSearch);
			} while (matchSearch == -1);
			break;

		case 3:
			int select=0;
			do {
				//search record by date
				printf("\t1) Day\n");
				printf("\t2) Month\n");
				printf("\t3) Year\n");
				printf("\t4) Return\n");
				printf("\t===============================\n");
				printf("\tSearch By : ");
				int findDay, findMonth, findYear;
				rewind(stdin);
				scanf("%d", &select);
				printf("\t===============================\n");
				switch (select) {
				case 1:
					do {
						findDay = 0;
						matchSearch = -1;
						printf("\tEnter Sales Date (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findDay);
						printf("\t===============================\n");
						if (findDay < 0) {
							return 0;
						}
						for (i = 0; i < salesNum; i++) {
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
						for (i = 0; i < salesNum; i++) {
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
						for (i = 0; i < salesNum; i++) {
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
				default:
						printf("\n\tPLEASE ENTER A CORRECT OPTION\n\n");
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

void modifySReccord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize) {
	displaySRecord(salesOrder, salesNum);
	int i, matchSearch;
	do {
		matchSearch = -1;
		printf("\tSelect Sales Order Id to modify (Enter X to exit) : ");
		char findSalesId[10];
		scanf(" %[^\n]", &findSalesId);
		//validate data entered
		if (strcmp(tolower(findSalesId), "x") == 0) {
			return 0;
		}
		for (i = 0; i < salesNum; i++) {
			if (strcmp(findSalesId, salesOrder[i].salesOrderId) == 0) {
				matchSearch = i;
			}
		}
		if (matchSearch == -1) {
			printf("\n\tNo matching result found, please enter sales order id.\n\n");
		}
		else {
			int opt, j;
			do {
				//displaying menu for user to view
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
						//for (i = 0; i < salesNum; i++) {
						//	if (strcmp(newICode,/*get from terence*/) == 0) {
						//		strcpy(salesOrder[matchSearch].itemCode, newICode);
						//		j++;
						//	}
						//}
						if (j == 0) {
							printf("\n\tInvalid Item Code Entered, Please Select Again\n");
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
							printf("\n\tInvalid Quantity Entered, Please Select Again\n");
						}
					break;

				case 3: printf("\tEnter Sold Item Price : ");
					double newPrice;
					scanf(" %lf", &newPrice);
					if (newPrice > 0 && newPrice < 10000) {
						salesOrder[matchSearch].price = newPrice;
					}
					else {
						printf("\n\tInvalid Amount Entered, Please Select Again\n");
					}
					break;

				case 4: printf("\tEnter Member Id : ");
					char newMemID[10];
					j = 0;
					scanf(" %[^\n]", &newMemID);
					for (i = 0; i < memberSize; i++) {
						if (strcmp(newMemID,memberInfo[i].memberId) == 0) {
							strcpy(salesOrder[matchSearch].memberId, newMemID);
							j++;
						}
					}
					if (j == 0) {
						printf("\n\tInvalid Member ID Entered, Please Select Again\n");
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
						printf("\n\tInvalid Date Entered, Please Select Again\n");
					}
					break;

				case 6: return 0;
					break;

				default: printf("\tPLEASE ENTER A CORRECT OPTION\n");
				}
			} while (opt != 6);

		}
	}while (matchSearch == -1);
	system("pause");
}

int addSRecord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize) {
	//declare data
	char yn, addsales[10], additemC[10], addmemID[10], minSalesId[10];
	strcpy(minSalesId, salesOrder[salesNum - 1].salesOrderId);
	double addSprice, tPrice;
	int addquan, adddate, addmonth, addyear, i, valid;
	do {
		do {
			valid = 0;
			printf("\n\tEnter New Sales Order Id (Latest Sales Order ID : %s): ", salesOrder[salesNum-1].salesOrderId);
			scanf(" %s", &addsales);
			printf("\n\t===============================\n");
			if (strcmp(tolower(addsales), "x")==0) {
				return salesNum;
			}
			//validate data entered
			if (strcmp(addsales, "S200") <= 0 && strcmp(addsales, minSalesId) > 0) {
				//save valid data in to the struct
				strcpy(salesOrder[salesNum].salesOrderId, addsales);
				valid++;
			} else {
				//print error massage if data entered is invalid
				printf("\tInvalid Sales Order Id Entered, Please Select And Enter Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);

		do {
			valid = 1;
			printf("\n\tEnter New Sold Item Code : ");
			scanf(" %s", &additemC);
			printf("\n\t===============================\n");
			if (strcmp(tolower(additemC), "x") == 0) {
				return salesNum;
			}
			tPrice = 0;
			//for (i = 0; i </*from terence*/; i++) {
			//	if (strcmp(additemC,/*from terence*/) == 1) {
			//		strcpy(salesOrder[salesNum].itemCode, additemC);
			//		tPrice=from terence;
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
				salesOrder[salesNum].qtySold = addquan;
				salesOrder[salesNum].price = addquan * tPrice;
				valid++;
			}
			else {
				printf("\tInvalid Quantity Entered, Please Select And Enter Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);
			/*do {
				valid = 0;
				printf("\n\tEnter Sold Item  Price : ");
				rewind(stdin);
				scanf(" %lf", &addSprice);
				printf("\n\t===============================\n");
				if (addSprice > 0 && addSprice < 9999) {
					salesOrder[salesNum].price = addSprice;
					valid++;
				}
				else {
					printf("\n\tInvalid Sold Price Entered, Please Select And Enter Again");
					printf("\n\t===============================\n");

				}
			} while (valid == 0);*/

		do {
			valid = 1;
			printf("\n\tEnter Member Id : ");
			scanf(" %s", &addmemID);
			printf("\n\t===============================\n");
			if (strcmp(tolower(addmemID), "x") == 0) {
				return salesNum;
			}
			for (i = 0; i < memberSize; i++) {
				if (strcmp(addmemID, memberInfo[i].memberId) == 1) {
					strcpy(salesOrder[salesNum].memberId, addmemID);
					valid++;
				}
			}
			if(valid==0) {
				printf("\nInvalid Member Id Entered, Please Select And Enter Again");
			 printf("\n\t===============================\n");
			}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\tEnter Sold Date By Following (DD/MM/YYYY) : ");
			scanf(" %d/%d/%d", &adddate, &addmonth, &addyear);
			printf("\n\t===============================\n");
			if (adddate > 0 && adddate < 31 && addmonth > 0 && addmonth < 13 && addyear > 2000 && addyear < 2024) {
				salesOrder[salesNum].date.day = adddate;
				salesOrder[salesNum].date.month = addmonth;
				salesOrder[salesNum].date.year = addyear;
				valid++;
			}
			else {
				printf("\n\n\tInvalid Date Entered, Please Select Again");
				printf("\n\t===============================\n");
			}
		} while (valid == 0);

		salesNum++;
		printf("\tDo you want to continue adding? (Y/N) : ");
		scanf(" %c", &yn);
		if (toupper(yn) == 'N') {
			displaySRecord(salesOrder, salesNum);
			return salesNum;
		}
	} while (salesNum != MAX_SALES);
	return salesNum;
	system("pause");
}

void popularItem(SALES salesOrder[], int salesNum) {
//	int itemSold[20], popular = -99;
//	char popularItem[6];
//	
//	for (int i = 0; i < salesNum; i++) {
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
}

void salesCommissionReport(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize) {
	double upLineComm[MAX_SALES] = {0};
	int j, i;
	for (i = 0; i < memberSize; i++) {
		for (j = 0; j < salesNum; j++) {
			if (strcmp(memberInfo[i].memberId, salesOrder[j].memberId) == 0) {
				upLineComm[i] = salesOrder[j].price * 0.05;
			}
		}
	}
	printf("\t\tCommission of Each Member's Upline\n");
	printf("\t========================================\n");
	printf("\tMEMBER ID \t UPLINE'S COMMISSIONS\n");
	for (int i = 0; i < 10; i++) {
		printf("\t%7s \t\t%6.2f\n",memberInfo[i].memberId, upLineComm[i]);
	}
	system("pause");
}

void totalSalesReport(SALES salesOrder[], int salesNum) {
	int i, totalItemSold = 0;
	double totalSales = 0;

	for (i = 0; i < salesNum; i++) {
		totalItemSold += salesOrder[i].qtySold;
		totalSales += salesOrder[i].price;
	}
	printf("\n\t\t\t\tTOTAL SALES REPORT\n");
	printf("\t================================================================\n");
	printf("\tSALES ID \t   ITEM CODE \t\tQUANTITY\t  AMOUNT\n");
	printf("\t================================================================\n");
	for (i = 0; i < salesNum; i++) {
		printf("\t%s \t\t    %7s \t\t   %02d \t\t %7.2f\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode, salesOrder[i].qtySold, salesOrder[i].price);
	}
	printf("\t================================================================\n");
	printf("\tTOTAL\t\t\t\t           %d           %7.2f\n",totalItemSold,totalSales);
	printf("\t================================================================\n");
	system("pause");
}

void header() {
	//header used for presenting data
	printf("\t===================================================================================\n");
	printf("\tSALES ORDER ID    ITEM CODE    QUANTITY     SALES AMOUNT    MEMBER ID    SALES DATE\n");
	printf("\t===================================================================================\n");
}
void result(SALES salesOrder[], int i) {
	//return result after validation to search function
	printf("\tSales Order ID  : %s \n\tItem Code \t: %s \n\tUnit Sold \t: %d\n\tSales Amount \t: $%-3.2f \n\tMember ID \t: %s \n\tSales Date  \t: %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
		salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	printf("\t===============================\n");
}
void validation(int matchSearch) {
	//search validation, print out massage if invalid
	if (matchSearch == -1) {
		printf("\n\tNo matching result found, please enter again.\n\n");
		printf("\t===============================\n");
	}
}