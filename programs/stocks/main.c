#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

int main()
{
	int userChoice;     //user choice to report,buy,sell,or quit

	//driver loop to execute while user does not quit
	do{
		//print message and options, get user's choice
		printf("\nWelcome to IniTrade.com\n");
		printf("\tReporting, buying, or selling?\n");
		printf("\t(0=quit, 1=report, 2=buy, 3=sell): ");
		scanf("%i", &userChoice);

		//jump to relevant functions depending on choice
		if (userChoice == 1){          //report
			//print name and # of all stocks owned
			printOwned();
			//get name of specific stock from user
			//show all shares and prices
			report();
		}else if (userChoice == 2){    //buy
			//get name of stock and current price from user, write to file
			//file is created if does not exist
			buy();
		}else if (userChoice == 3){    //sell
			//initialize queue
			queue *q;
			q = malloc(sizeof(queue));
			q->head = NULL;
			q->tail = NULL;
			//fill queue with stocks to sell
			//sell them, calculate profit/loss, print and write to file
			fillQueue(q);

			free(q);
		}
	}while (userChoice != 0);
	printf("Thank you for using IniTrade.com\n");
	return 0;
}
