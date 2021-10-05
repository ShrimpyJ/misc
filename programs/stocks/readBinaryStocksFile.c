/* File: readBinaryStockFile.c
 * Author: Cindy
 * Prompts read stock data from  binary file and print
 */ 
#include <stdio.h>
#include <string.h>
#include "stock.h"

int main() {
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
      printStock( s );
      fread( (char*)(&s), 1, sizeof(stock_t), input );
   }
   fclose( input );

   return 0;
}
