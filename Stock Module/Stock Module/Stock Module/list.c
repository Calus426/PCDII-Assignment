//#include<stdio.h>
//#include<stdlib.h>
//#include<ctype.h>
//
//#pragma warning(disable:4996)
//
//typedef struct
//{
//	char MCode[10];
//	char MName[30];
//	double MPrice;
//	int MStock, MMinimum, MReorder;
//
//}MerchandiseInStock;
//
//void merchandiseList(MerchandiseInStock MIS[], int mDataSize)
//{
//	int number;
//	system("cls");
//	printf("\n\n");
//
//	for (int i = 0; i < mDataSize; i++)
//	{
//		number = i + 1;
//
//		printf("    NO.%d\n", number);
//		printf("  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
//		printf("    Code             : %s\n    Name             : %s\n    Price(RM)        : %.2lf\n    Stock Quantity   : %d\n    Minimum Level    : %d\n    Reorder Quantity : %d\n", MIS[i].MCode, MIS[i].MName, MIS[i].MPrice, MIS[i].MStock, MIS[i].MMinimum, MIS[i].MReorder);
//		printf("  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
//		printf("------------------------------------------------------\n\n");
//		
//	}
//	system("pause");
//}