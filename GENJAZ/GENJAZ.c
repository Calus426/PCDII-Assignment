#include <stdio.h>
#pragma warning (disable:4996)

void memberModule();
void SalesInformationModule();
void stockModule();
int staffInformationModule();
void logo();
void menu();

void main() {
	int select = 0;

	do {
		system("cls");
		logo();
		menu();
		printf("\t\t\t    Select An Option : ");
		rewind(stdin);
		scanf("%d", &select);

		switch (select) {
		case 1: staffInformationModule();
			break;
		case 2: memberModule();
			break;
		case 3: SalesInformationModule();
			break;
		case 4: stockModule();
			break;
		case 5: printf("\n\t\t\t     Thank You, Hope to See You Soon!\n");
			return 0;
			break;
		default: printf("\n\t Not mataching result, Please select again\n");
		}
	} while (select != 5);
}

void logo() {
	printf("\t+-------------------------------------------------------------------------------+\n");
	printf("\t ___________   __________   ____    ___    ___________     _____    ___________\n");
	printf("\t |==========|  |=========|  |===\\   |==|   |==========|   /=====\\   |==========|\n");
	printf("\t |==|          |==|         |====\\  |==|       |==|      /== _ ==\\         /==/  \n");
	printf("\t |==|          |==_______   |==|==\\ |==|       |==|      |==|_|==|       /==/    \n");
	printf("\t |==|   ____   |=========|  |==|\\==\\|==|       |==|      |=======|     /==/          \n");
	printf("\t |==|  |====|  |==|         |==| \\== ==|   __  |==|      |==| |==|   /==/        \n");
	printf("\t |==______==|  |==_______   |==|  \\====|  |==| |==|      |==| |==|  |==/_______\n");
	printf("\t |==========|  |=========|  |==|   \\===|    |====|       |==| |==|  |==========|\n");
	printf("\t  \n");
	printf("\t+-------------------------------------------------------------------------------+\n");
}

void menu() {
	printf("\n\t\t\t   +=================================+");
	printf("\n\t\t\t   |\t  1) Staff  Information      |");
	printf("\n\t\t\t   |\t  2) Member Information      |");
	printf("\n\t\t\t   |\t  3) Sales  Information      |");
	printf("\n\t\t\t   |\t  4) Stock  Information      |");
	printf("\n\t\t\t   |\t  5)       Exit              |");
	printf("\n\t\t\t   +=================================+\n");
}