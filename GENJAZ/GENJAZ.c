#include <stdio.h>
#pragma warning (disable:4996)

void main() {
	int select = 0;
	printf("\t+---------------------------------------------------------------+\n");
	printf("\t  ___________   __________\n");
	printf("\t  |==========|  |=========|\n");
	printf("\t  |==|          |==|\n");
	printf("\t  |==|          |==_______\n");
	printf("\t  |==|     __   |=========|\n");
	printf("\t  |==|     ==|  |==|\n");
	printf("\t  |==______==|  |==_______\n");
	printf("\t  |==========|  |=========|\n");
	printf("\t  \n");
	printf("\t+---------------------------------------------------------------+\n");

	do {
		printf("");
		rewind(stdin);
		scanf("%d", &select);

		switch (select) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default: printf("\n\t Not mataching result, Please select again\n");
		}
	} while (select != 5);
}