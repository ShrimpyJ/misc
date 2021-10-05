#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "stock.h"

stock_t st;

void printOwned()
{
	printf("\nStocks Owned\n------------\n");

	DIR* dirPtr;
	struct dirent* dirEntry;
	dirPtr = opendir("./stocks");
	while ((dirEntry = readdir(dirPtr)) != NULL){
		//avoid directories "." and ".."
		if (dirEntry->d_name[0] == '.'){
			continue;
		}

		//read file name up to '.'
		char ticker[MAX_TICKER_LENGTH];        //name of file up to '.'
		char extension[4];
		int i = 0;                             //index of current letter
		while (dirEntry->d_name[i] != '.' && i < strlen(dirEntry->d_name)){
			i++;
		}
		char *tck = dirEntry->d_name;       //name of ticker
		char *ext = dirEntry->d_name + i;   //name of file extension

		strcpy(extension,ext);

		//print name if extension is ".bin"
		if (strcmp(extension,".bin") == 0){
			strncpy(ticker,tck,i);
			ticker[i] = '\0';
			printf("%s\n", ticker);
		}
	}
	closedir(dirPtr);
}

void printStock(struct stock_t s, struct date_t date)
{
	printf("%s\t%2d/%2d/%4d\t%d\t$\t%f\n", s.ticker,date.month,date.day,date.year,s.numShares,s.pricePerShare);
	return;
}

void readFile() {
   FILE* input;
   stock_t s;
   char ticker[10];
   
   printf("Enter stock ticker: ");
   scanf("%s", ticker );
   strcat ( ticker, ".bin" );

   // open binary file
   input = fopen( ticker, "rb" );

   
   fread( (char*)(&s), 1, sizeof(stock_t), input );
   while( !feof( input ) ) {
      printStock(s, s.date);
      fread( (char*)(&s), 1, sizeof(stock_t), input );
   }
   fclose( input );
   return;
}
