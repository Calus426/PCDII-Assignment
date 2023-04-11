#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#pragma warning(disable:4996)

int mChoice;

void menu()
{

	while (mChoice != 7)
	{

	
	 printf("\n\n================================\n"
		        "    What is Your Next Move??\n"
		        "================================\n"
		        " 1. Add a new Merchandise\n"
		        " 3. Modify Merchandise Data\n"
		        " 4. Check Merchandise List\n"
		        " 5. Delete Merchandise Data\n"
		        " 6. Daily Report\n"
		        " 7. Exit\n"
		 "\n\n"
		        "Enter your choice  : ");
     scanf("%d", &mChoice);

	 printf("\n\n");

	 switch (mChoice)
	 {
	  case 1 :

		
		break;

	  case 2:

		
		break;

	  case 3:
		
		break;

	  case 4:
		
		break;

	  case 5:
		
		break;


	  case 6:
		
		break;

	  case 7:

		  printf("Bye Bye!!!");
	  default:

		printf("Unknow Value Please Try Agian\n"
		       "===============================================================================================================");
		
		
	 }

	} 
}