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

//struct from terence
typedef struct
{
	char MCode[10];
	char MName[30];
	double MPrice;
	int MStock, MMinimum, MReorder;
}MerchandiseInStock;

//data field that will be use by the sale information module
typedef struct {
	char salesOrderId[10];
	char itemCode[10];
	int qtySold;
	double price;
	char memberId[10];
	Date date;
}SALES;

void getMember1(Member memberInfo[], int* memberSize)
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

void merchandiseData1(MerchandiseInStock MIS[], int* mDataSize)
{
	FILE* MD;
	MD = fopen("stock.txt", "r");

	if (MD == NULL)
	{
		printf("Unable to open the file\n");
		exit(-1);
	}

	*mDataSize = 0;

	int i = 0;
	while (fscanf(MD, "%[^|]|%[^|]|%lf|%d|%d|%d|\n", &MIS[i].MCode, &MIS[i].MName, &MIS[i].MPrice, &MIS[i].MStock, &MIS[i].MMinimum, &MIS[i].MReorder) != EOF)
	{
		i++;
		*mDataSize = i;
	}
	fclose(MD);
}

void getSales(SALES salesOrder[], int* salesNum) {
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
void header();
void validation(int);
void result(SALES[], int);
void displaySRecord(SALES[], int);
void searchSRecord(SALES[], int);
void totalSalesReport(SALES[], int);
void popularItem(SALES[], int, MerchandiseInStock[], int);
void salesCommissionReport(SALES[], int, Member[], int);
void modifySReccord(SALES[], int, Member[], int , MerchandiseInStock[], int);
int  addSRecord(SALES[], int, Member[], int, MerchandiseInStock[], int);

void SalesInformationModule() {
	//read lucas and terence's file
	Member memberInfo[20];
	int memberSize = 0;
	getMember1(memberInfo, &memberSize);

	MerchandiseInStock MIS[20];
	int mDataSize = 0;
	merchandiseData1(MIS, &mDataSize);

	SALES salesOrder[MAX_SALES];
	int option = 0, salesNum = 0, i = 0;
	getSales(salesOrder, &salesNum);

	do {
		//showing the menu
		system("cls");
		printf("\t+=================================+\n");
		printf("\t WELCOME TO SALES INFORMATION MENU\n");
		printf("\t+=================================+\n");
		printf("\t 1)    DISPLAY SALES RECORD\n");
		printf("\t 2)    SEARCH  SALES RECORD\n");
		printf("\t 3)    MODIFY  SALES RECORD\n");
		printf("\t 4)    ADD     SALES RECORD\n");
		printf("\t 5)    POPULAR SALES RECORD\n");
		printf("\t 6)    SALES   COMMISSIONS REPORT\n");
		printf("\t 7)    TOTAL   SALES REPORT\n");
		printf("\t 8)    EXIT\n");
		printf("\t+================================+\n");
		printf("\t PLEASE ENTER AN OPTION : ");
		rewind(stdin);
		//select an option to go to desired function
		scanf("%d", &option);
		printf("\t+================================+\n");
		switch (option) {
		case 1: displaySRecord(salesOrder, salesNum);
			system("pause");
			break;

		case 2: searchSRecord(salesOrder, salesNum);
			break;

		case 3: modifySReccord(salesOrder, salesNum, memberInfo, memberSize, MIS, mDataSize);
			break;

		case 4: salesNum = addSRecord(salesOrder, salesNum, memberInfo, memberSize, MIS, mDataSize);
			break;

		case 5: popularItem(salesOrder, salesNum, MIS, mDataSize);
			break;

		case 6: salesCommissionReport(salesOrder, salesNum, memberInfo, memberSize);
			break;

		case 7: totalSalesReport(salesOrder, salesNum);
			break;

		case 8:
			FILE * update = fopen("salesRecord.bin", "wb");
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

void displaySRecord(SALES salesOrder[], int salesNum) {
	//display all sales information inside of sales record file
	printf("\n\t\t\t\t\tAll Sales Order Record\n");
	header();
	for (int i = 0; i < salesNum; i++) {

		printf("\t %s \t    %14s \t %3d\t     $ %7.2f \t      %s\t  %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
			salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	}
	printf("\t+===================================================================================+\n");
}

void searchSRecord(SALES salesOrder[], int salesNum) {
	int opt, i, matchSearch;
	printf("\n\t\t\t Search Record\n");
	do {
		printf("\n\t Search Record by : \n");
		printf("\t+==============================+\n");
		//allow use to filter and search for sales record
		printf("\t 1) ID\n");
		printf("\t 2) Item Code\n");
		printf("\t 3) Date\n");
		printf("\t 4) Return\n");
		printf("\t+==============================+\n");
		opt = 0, matchSearch = -1;
		printf("\t PLEASE ENTER AN OPTION : ");
		rewind(stdin);
		scanf("%d", &opt);
		printf("\t+==============================+\n");
		switch (opt) {
		case 1:
			do {
				matchSearch = -1;
				printf("\t Enter Sales Order Id (Enter X to exit) : ");
				char id[10];
				scanf(" %[^\n]", &id);
				printf("\t+===============================================+\n");
				//compare to exit
				if (strcmp(tolower(id), "x") == 0) {
					break;
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
				printf("\t Enter Item Code (Enter X to exit): ");
				char findItemCode[10];
				scanf(" %[^\n]", &findItemCode);
				printf("\t+===============================================+\n");
				if (strcmp(toupper(findItemCode), "x") == 0) {
					break;
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
			int select = 0;
			do {
				//search record by date
				printf("\n\t Search Record by : \n");
				printf("\t+==============================+\n");
				printf("\t 1) Day\n");
				printf("\t 2) Month\n");
				printf("\t 3) Year\n");
				printf("\t 4) Return\n");
				printf("\t+==============================+\n");
				printf("\t Search By : ");
				int findDay, findMonth, findYear;
				rewind(stdin);
				scanf("%d", &select);
				printf("\t+==============================+\n");
				switch (select) {
				case 1:
					do {
						findDay = 0;
						matchSearch = -1;
						printf("\t Enter Sales Date (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findDay);
						printf("\t+===============================================+\n");
						if (findDay < 0) {
							break;
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
						printf("\t Enter Sales Month (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findMonth);
						printf("\t+===============================================+\n");
						if (findMonth < 0) {
							break;
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
						printf("\t Enter Sales Year (Enter -1 to exit) : ");
						rewind(stdin);
						scanf("%d", &findYear);
						printf("\t+===============================================+\n");
						if (findYear < 0) {
							break;
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
				case 4: break;
					break;
				default:
					printf("\n\t PLEASE ENTER A CORRECT OPTION\n\n");
					printf("\t+==============================+\n");
				}
			} while (select != 4);
			break;

		case 4:
			return 0;
			break;

		default: printf("\n\t PLEASE ENTER A CORRECT OPTION\n\n");
			printf("\t+==============================+\n");
		}
	} while (opt != 4);
}

void modifySReccord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize, MerchandiseInStock MIS[], int mDataSize) {
	displaySRecord(salesOrder, salesNum);
	int i, matchSearch;
	do {
		matchSearch = -1;

		printf("\t Select Sales Order Id to modify (Enter X to exit) : ");
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
			printf("\t+======================================================+\n");
			printf("\n\t No matching result found, please enter sales order id.\n\n");
			printf("\t+======================================================+\n");
		}
		else {
			int opt, j;
			do {
				//displaying menu for user to view
				printf("\n\t+===============================+\n");
				printf("\t You are editing Sales Id : %s", findSalesId);
				printf("\n\t+===============================+\n");
				printf("\t 1) Item Code\n");
				printf("\t 2) Quantity Sold\n");
				printf("\t 3) Price\n");
				printf("\t 4) Member ID\n");
				printf("\t 5) Sales Date\n");
				printf("\t 6) Return\n");
				printf("\t+================================+\n");
				printf("\t Select Which Field To Modify : ");
				rewind(stdin);
				scanf(" %d", &opt);
				printf("\t+================================+\n");
				printf("\n");
				switch (opt) {
				case 1:
					do {
						j = 0;
						printf("\t Enter Updated Sold Item Code (Enter X to exit) : ");
						char newICode[10];
						scanf(" %[^\n]", &newICode);
						if (strcmp(tolower(newICode), "x") == 0) {
							break;
						}
						for (i = 0; i < salesNum; i++) {
							if (strcmp(newICode, MIS[i].MCode) == 0) {
								strcpy(salesOrder[matchSearch].itemCode, newICode);
								printf("\n\t\tUpdated data\n");
								printf("\n\t+===============================================+\n");
								result(salesOrder, matchSearch);
								j++;
							}
						}
						if (j == 0) {
							printf("\t+======================================================+\n");
							printf("\n\t Invalid Item Code Entered, Please Select Again\n\n");
							printf("\t+======================================================+\n");
						}
					} while (j == 0);
					break;

				case 2:
					do {
						j = 0;
						printf("\t Enter Updated Quantity Sold (Enter -1 to exit) : ");
						int newSold;
						rewind(stdin);
						scanf(" %d", &newSold);
						if (newSold < 0) {
							break;
						}
						if (newSold > 0 && newSold < 100) {
							salesOrder[matchSearch].qtySold = newSold;
							printf("\n\t\t\t    Updated data");
							printf("\n\t+===============================================+\n");
							result(salesOrder, matchSearch);
							j++;
						}
						else {
							printf("\t+======================================================+\n");
							printf("\n\t Invalid Quantity Entered, Please Select Again\n\n");
							printf("\t+======================================================+\n");
						}
					} while (j == 0);
					break;

				case 3:
					do {
						j = 0;
						printf("\t Enter Updated Sold Item Price (Enter -1 to exit) : ");
						double newPrice;
						rewind(stdin);
						scanf(" %lf", &newPrice);
						if (newPrice < 0) {
							break;
						}
						if (newPrice > 0 && newPrice < 10000) {
							salesOrder[matchSearch].price = newPrice;
							j++;
						}
						else {
							printf("\t+======================================================+\n");
							printf("\n\tInvalid Amount Entered, Please Select Again\n\n");
							printf("\t+======================================================+\n");
						}
					} while (j == 0);
					break;

				case 4:
					do {
						j = 0;
						printf("\t Enter Updated Member Id (Enter X to exit) : ");
						char newMemID[10];
						scanf(" %[^\n]", &newMemID);
						if (strcmp(tolower(newMemID), "x") == 0) {
							break;
						}
						for (i = 0; i < memberSize; i++) {
							if (strcmp(newMemID, memberInfo[i].memberId) == 0) {
								strcpy(salesOrder[matchSearch].memberId, newMemID);
								j++;
							}
						}
						if (j == 0) {
							printf("\t+======================================================+\n");
							printf("\n\tInvalid Member ID Entered, Please Select Again\n\n");
							printf("\t+======================================================+\n");
						}
					} while (j == 0);
					break;

				case 5:
					do {
						j = 0;
						printf("\t Enter Updated Sold Date (Please Follow DD/MM/YYYY Format) (Enter -1 to exit) : ");
						int newDay, newMonth, newYear;
						rewind(stdin);
						scanf(" %d/%d/%d", &newDay, &newMonth, &newYear);
						if (newDay < 0 || newMonth < 0 || newYear < 0) {
							break;
						}
						if (newDay > 0 && newDay < 31 && newMonth > 0 && newMonth < 13 && newYear > 2000 && newYear < 2024) {
							salesOrder[matchSearch].date.day = newDay;
							salesOrder[matchSearch].date.month = newMonth;
							salesOrder[matchSearch].date.year = newYear;
							j++;
						}
						else {
							printf("\t+======================================================+\n");
							printf("\n\t Invalid Date Entered, Please Select Again\n\n");
							printf("\t+======================================================+\n");
						}
					} while (j == 0);
					break;

				case 6: break;
					break;

				default: printf("\t PLEASE ENTER A CORRECT OPTION\n");
				}
			} while (opt != 6);

		}
	} while (matchSearch == -1);
	system("pause");
}

int addSRecord(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize, MerchandiseInStock MIS[], int mDataSize) {
	//declare data
	char yn, addsales[10], additemC[10], addmemID[10], minSalesId[10];
	strcpy(minSalesId, salesOrder[salesNum - 1].salesOrderId);
	double addSprice, tPrice;
	int addquan, adddate, addmonth, addyear, i, valid;
	do {
		do {
			valid = 0;
			printf("\n\t Enter New Sales Order Id (Latest Sales Order ID : %s) (Enter X to exit): ", salesOrder[salesNum - 1].salesOrderId);
			rewind(stdin);
			scanf(" %s", &addsales);
			printf("\n\t+==================================================================================+\n");
			if (strcmp(tolower(addsales), "x") == 0) {
				return salesNum;
			}
			//validate data entered
			if (strcmp(addsales, "S200") <= 0 && strcmp(addsales, minSalesId) > 0) {
				//save valid data in to the struct
				strcpy(salesOrder[salesNum].salesOrderId, addsales);
				valid++;
			}
			else {
				//print error massage if data entered is invalid
				printf("\t Invalid Sales Order Id Entered, Please Select And Enter Again");
				printf("\n\t+==================================================================================+\n");
			}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\t Enter New Sold Item Code (Enter X to exit) : ");
			rewind(stdin);
			scanf("%[^\n]", &additemC);
			printf("\n\t+==================================================================================+\n");

			if (strcmp(tolower(additemC), "x") == 0) {
				return salesNum;
			}
			tPrice = 0;

			for (i = 0; i < mDataSize; i++) {
				if (strcmp(additemC, MIS[i].MCode) == 0) {
					strcpy(salesOrder[salesNum].itemCode, additemC);
					tPrice = MIS[i].MPrice;
					valid++;
				}
			}

			if (valid == 0) {
				printf("\n Invalid Item Id Entered, Please Select And Enter Again");
				printf("\n\t+==================================================================================+\n");
			}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\t Enter Quantity Sold (Enter -1 to exit) : ");
			rewind(stdin);
			scanf(" %d", &addquan);
			printf("\n\t+==============================+\n");
			if (addquan < 0) {
				return salesNum;
			}
			if (addquan > 0 && addquan < 99) {
				salesOrder[salesNum].qtySold = addquan;
				salesOrder[salesNum].price = addquan * tPrice;
				valid++;
			}
			else {
				printf("\t Invalid Quantity Entered, Please Select And Enter Again");
				printf("\n\t+==============================+\n");
			}
		} while (valid == 0);

		do {
			valid = 1;
			printf("\n\t Enter Member Id (Enter X to exit) : ");
			scanf(" %s", &addmemID);
			printf("\n\t+==================================================================================+\n");
			if (strcmp(tolower(addmemID), "x") == 0) {
				return salesNum;
			}
			for (i = 0; i < memberSize; i++) {
				if (strcmp(addmemID, memberInfo[i].memberId) == 0) {
					strcpy(salesOrder[salesNum].memberId, addmemID);
					valid++;
				}
			}
			if (valid == 0) {
				printf("\n Invalid Member Id Entered, Please Select And Enter Again");
				printf("\n\t+==================================================================================+\n");
			}
		} while (valid == 0);

		do {
			valid = 0;
			printf("\n\t Enter Sold Date By Following (DD/MM/YYYY) (Enter -1 to exit) : ");
			rewind(stdin);
			scanf(" %d/%d/%d", &adddate, &addmonth, &addyear);
			printf("\n\t+==================================================================================+\n");
			if (adddate < 0 || addmonth < 0 || addyear < 0) {
				return salesNum;
			}
			if (adddate > 0 && adddate < 31 && addmonth > 0 && addmonth < 13 && addyear > 2000 && addyear < 2024) {
				salesOrder[salesNum].date.day = adddate;
				salesOrder[salesNum].date.month = addmonth;
				salesOrder[salesNum].date.year = addyear;
				valid++;
			}
			else {
				printf("\n\n\t Invalid Date Entered, Please Select Again");
				printf("\n\t+==================================================================================+\n");
			}
		} while (valid == 0);

		salesNum++;
		printf("\t Do you want to continue adding? (Y/N) : ");
		scanf(" %c", &yn);
		if (toupper(yn) == 'N') {
			displaySRecord(salesOrder, salesNum);
			system("pause");
			return salesNum;
		}
	} while (salesNum != MAX_SALES);
	return salesNum;
	system("pause");
}

void popularItem(SALES salesOrder[], int salesNum, MerchandiseInStock MIS[], int mDataSize) {
	int itemSold[20] = { 0 }, popular = -99, least = 100, i, j;
	char popularItem[10], unpopularItem[10];

	for (i = 0; i < mDataSize; i++) {
		for (j = 0; j < salesNum; j++) {
			if (strcmp(MIS[i].MCode, salesOrder[j].itemCode) == 0) {
				itemSold[i] += salesOrder[j].qtySold;
			}
		}
	}
	printf("\n\t\t\t         Item Sold List\n");
	printf("\t+=============================================================+\n");
	printf("\t Item Code\t\t\t\t   Unit Sold\n");
	printf("\t+=============================================================+\n");
	for (i = 0; i < mDataSize; i++) {
		printf("\t %s   \t\t\t\t      %2d\n", MIS[i].MCode, itemSold[i]);
		if (itemSold[i] > popular) {
			popular = itemSold[i];
			strcpy(popularItem, MIS[i].MCode);
		}
		if (itemSold[i] < least) {
			least = itemSold[i];
			strcpy(unpopularItem, MIS[i].MCode);

		}
	}
	printf("\t+=============================================================+\n");
	printf("\t The most popular item sold is  \"%7s\" which sold % 2d unit.\n", popularItem, popular);
	printf("\t+=============================================================+\n");
	printf("\t The least popular item sold is \"%7s\" which sold %2d unit.\n", unpopularItem, least);
	printf("\t+=============================================================+\n");
	system("pause");
}

void salesCommissionReport(SALES salesOrder[], int salesNum, Member memberInfo[], int memberSize) {
	double upLineComm[MAX_SALES] = { 0 };
	int j, i;

	for (i = 0; i < memberSize; i++) {
		for (j = 0; j < salesNum; j++) {
			if (strcmp(memberInfo[i].memberId, salesOrder[j].memberId) == 0) {
				upLineComm[i] = salesOrder[j].price * 0.05;
			}
		}
	}
	printf("\n\t\tCommission of Each Member's Upline\n");
	printf("\t+============================================+\n");
	printf("\t MEMBER ID \t\t UPLINE'S COMMISSIONS\n");
	printf("\t+============================================+\n");
	for (int i = 0; i < 10; i++) {
		printf("\t%7s \t\t\t%6.2f\n", memberInfo[i].memberId, upLineComm[i]);
	}
	printf("\t+============================================+\n");
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
	printf("\t+===============================================================+\n");
	printf("\t SALES ID \t   ITEM CODE \t\tQUANTITY\t  AMOUNT\n");
	printf("\t+===============================================================+\n");
	for (i = 0; i < salesNum; i++) {
		printf("\t %s \t\t    %7s \t\t   %02d \t\t %7.2f\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode, salesOrder[i].qtySold, salesOrder[i].price);
	}
	printf("\t+===============================================================+\n");
	printf("\t TOTAL\t\t\t\t           %d           %7.2f\n", totalItemSold, totalSales);
	printf("\t+===============================================================+\n");
	system("pause");
}

void result(SALES salesOrder[], int i) {
	//return result after validation to search function
	printf("\t Sales Order ID  \t: %s \n\tItem Code \t\t: %s \n\tUnit Sold \t\t: %d\n\tSales Amount \t\t: $%-3.2f \n\tMember ID \t\t: %s \n\tSales Date  \t\t: %02d/%02d/%04d\n", salesOrder[i].salesOrderId, salesOrder[i].itemCode,
		salesOrder[i].qtySold, salesOrder[i].price, salesOrder[i].memberId, salesOrder[i].date.day, salesOrder[i].date.month, salesOrder[i].date.year);
	printf("\t+===============================================+\n");
}
void validation(int matchSearch) {
	//search validation, print out massage if invalid
	if (matchSearch == -1) {
		printf("\n\t No matching result found, please enter again.\n\n");
		printf("\t+===============================+\n");
	}
}
void header() {
	//header used for presenting data
	printf("\t+===================================================================================+\n");
	printf("\t SALES ORDER ID    ITEM CODE    QUANTITY     SALES AMOUNT    MEMBER ID    SALES DATE\n");
	printf("\t+===================================================================================+\n");
}