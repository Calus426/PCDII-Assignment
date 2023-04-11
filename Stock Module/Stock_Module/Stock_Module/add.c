#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)


char mName[30];

void addNew()
{
	FILE* AN;
	AN = fopen("stock.txt", "w");

	printf("Enter new merchandise name  :");


	fclose(AN);
}