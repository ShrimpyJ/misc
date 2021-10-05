#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "stock.h"
#include "linkedList.h"

stock_t st;

//print name and # owned of all owned stocks
void printOwned()
{
	printf("\nStocks Owned\n------------\n");
	stock_t s;

	//search through files in current directory for ".bin" extensions
	DIR* dirPtr;
	struct dirent* dirEntry;
	dirPtr = opendir(".");
	while ((dirEntry = readdir(dirPtr)) != NULL){
		int totalShares = 0;
		//avoid directories "." and ".."
		if (dirEntry->d_name[0] == '.'){
			continue;
		}

		//read file name up to '.'
		char ticker[MAX_TICKER_LENGTH];        //name of file up to '.'
		int i = 0;                             //index of current letter
		size_t len = strlen(dirEntry->d_name); //size of file name in bytes
		while (dirEntry->d_name[i] != '.' && i < len){
			i++;
		}

		//if extension is ".bin", get total #  of shares and print with name
		if (strcmp(dirEntry->d_name + len - 4, ".bin") == 0){
			//get total # of shares for stock
			FILE* input;
			input = fopen(dirEntry->d_name, "rb");
			while(fread((char*)(&s), 1, sizeof(stock_t), input)){
				totalShares += s.numShares;
			}
			fclose(input);

			//print name and # of shares
			strncpy(ticker,dirEntry->d_name,i);
			ticker[i] = '\0';
			printf("%s\t%4d\n",s.ticker,totalShares);
		}
	}
	closedir(dirPtr);
}

//print all info relevant to single stock
void printStock(struct stock_t s, struct date_t date)
{
	printf("%s\t%2d/%2d/%4d\t%3d\t$%9.2f\n", s.ticker,date.month,date.day,date.year,s.numShares,s.pricePerShare);
	return;
}

//get file name, append ".bin" if needed and return
char *getFilename(int key, char ticker[])
{
	char *filename = malloc(MAX_TICKER_LENGTH + 4);

	//for user-input tickers (keys 1 and 3)
	if (key % 2 == 1){
		scanf("%s", filename);
		//return ticker without .bin extension
		if (key == 3){
			return filename;
		}
	}
	//for tickers where name is already known (keys 2 and 4)
	else if (key % 2 == 0){
		strcpy(filename,ticker);
		//return ticker without .bin extension
		if (key == 4){
			return filename;
		}
	}

	//return ticker with .bin extension
	strcat(filename, ".bin");
	return filename;
}

//get single .bin file from user and read
void report()
{
   	//get file name from user and open
	FILE* input;
	stock_t s;
	printf("Enter stock ticker symbol: ");
	char *filename = getFilename(1,"");
	input = fopen(filename, "rb");

	//print header
	printf("Ticker\tPurchase Date\tShares\tPrice Per Share\n");
	printf("--------------------------------------------------\n");

	//print stock info
	while(fread((char*)(&s), 1, sizeof(stock_t), input)){
		printStock(s, s.date);
	}
	free(filename);
	fclose(input);
	return;
}

//get .bin file and stock info to buy from user, then write info to file
void buy()
{
	FILE* output;      //file to write to
	stock_t s;
	int userResponse;  //0 when user is done 

	//get ticker to buy from user
	printf("Enter stock ticker symbol to buy: ");
	char *ticker = getFilename(3,"");
	//append ".bin" and open
	char *filename = getFilename(2,ticker);
	output = fopen(filename, "a");

	//get stock info from user while they choose to continue
	do{
		getStock(&s, ticker);
		fwrite((char*)(&s), 1, sizeof(stock_t), output);
		printf("Continue? (0 = no): ");
		scanf("%d", &userResponse);
	}while(userResponse != 0);

	free(filename);
	free(ticker);
	fclose(output);
	return;
}

//get stock info (date, # of shares, and price) from system and user
void getStock(struct stock_t *s, char ticker[])
{
	//get ticker name
	strcpy(s->ticker, ticker);

	//get time from system
	time_t now = time(NULL);
	struct tm *time = localtime(&now);
	s->date.month = time->tm_mon+1;
	s->date.day = time->tm_mday;
	s->date.year = time->tm_year+1900;

	//get info from user
	printf("Enter # of shares to buy: ");
	scanf("%d", &s->numShares);
	printf("Enter Price per share: ");
	scanf("%lf", &s->pricePerShare);
}

//fill a queue with stock_t structures to possibly be sold
void fillQueue(struct queue *q)
{
	FILE* input;
	int totalShares = 0;    //total number of shares sold
	struct stock_t s;

	//get stock to sell from user
	printf("Enter stock ticker symbol to sell: ");
	char *filename = getFilename(1,"");
	input = fopen(filename, "r");

	//print error if no .bin file found
	if (input == NULL){
		printf("No owned stock for %s\n", filename);
		return;
	}

	//enqueue dummy as head
	enqueue(q,s);

	//read stocks into queue
	while (fread((char*)(&s), 1, sizeof(stock_t), input)){
		enqueue(q,s);
		totalShares += s.numShares;
	}
	fclose(input);

	//print total shares owned for stock
	printf("Shares owned in %s: %d\n",s.ticker,totalShares);
	getSharesToSell(q,s,totalShares);
}

//add a stock_t struct to end of queue
void enqueue(struct queue *q, stock_t item)
{
	//if empty, place dummy node
	if (q->tail == NULL){
		list_node *dummy = list_init();
		q->head = q->tail = dummy;
	}
	//add stock to tail end of queue
	else{
		list_node *node = list_insert(node,item);
		q->tail->next = node;
		q->tail = node;
	}
}

//remove the oldest stock_t struct from queue (excluding dummy)
int dequeue(struct queue *q)
{
	list_node *node = q->head->next;
	//if no node found
	if (!node){
		return 0;
	}
	//if the head becomes NULL, change tail to NULL
	if (node == q->tail){
		q->tail = NULL;
	}
	int result = node->data.numShares;
	list_delete(q->head);
	return result;
}

//get info on shares to sell from user (# to sell, current stock price)
void getSharesToSell(struct queue *q, struct stock_t s, int totalShares)
{
	int numToSell;          //# of shares to be sold
	double currentPrice;    //current day value of shares

	//get info from user
	printf("Enter # of stocks to sell: ");
	scanf("%d",&numToSell);

	//if number entered exceeds total shares, return to menu
	if (numToSell > totalShares){
		printf("Error: Number input is higher than shares owned\n");
		return;
	}

	printf("Enter current stock price: ");
	scanf("%lf",&currentPrice);
	printf("%s\n",s.ticker);

	sellShares(q,s,numToSell,currentPrice);
}

//sell shares and calculate total gain or loss
void sellShares(struct queue *q, struct stock_t s, int numToSell, double currentPrice)
{
	int soldShares = 0;               //tracks # of total shares sold
	int remainder = numToSell;        //tracks # of remaining shares to sell after a whole struct is sold
	double totalBuy;                  //the original total price of shares being sold
	double totalSell = currentPrice * numToSell;  //the current total price of shares being sold
	double totalOverall;              //the yield result of gain or loss

	char ticker[MAX_TICKER_LENGTH];   //extensionless name of .bin file to possibly be killed
	strcpy(ticker,q->head->next->data.ticker);

	//main loop to execute while total shares sold is less than the number to sell
	while (soldShares < numToSell){
		//if oldest share held (head of queue) is less than remaining number to sell
		//sell/remove entire share and calculate remaining shares to sell
		if (q->head->next->data.numShares <= numToSell){
			soldShares += q->head->next->data.numShares;
			remainder -= q->head->next->data.numShares;
			//add total cost of original shares to totalBuy
			totalBuy += q->head->next->data.pricePerShare * q->head->next->data.numShares;
			dequeue(q);
		}
		//when the remaining number of shares to sell is less than the queue head
		//sell remaining # of shares from queue head
		else{
			q->head->next->data.numShares -= remainder;
			soldShares += remainder;
			//add total cost of original shares to totalBuy
			totalBuy += q->head->next->data.pricePerShare * remainder;
		}
	}

	//calculate and print overall yield
	totalOverall = totalSell - totalBuy;
	printf("Yield gain/loss for transaction: $%.2lf\n",totalOverall);

	//if all shares were sold, remove the .bin file
	if (q->head->next == NULL){
		killFile(q,ticker);
		return;
	}

	//otherwise write updated contents to file
	writeNew(q,s);
}

//write stock contents after selling to .bin file
void writeNew(struct queue *q, struct stock_t s)
{
	FILE* output;
	//char filename [MAX_TICKER_LENGTH + 4];
	char *filename = getFilename(2, q->head->next->data.ticker);
//	strcpy(filename,q->head->next->data.ticker);
//	strcat(filename, ".bin");

	output = fopen(filename, "w");

	//go through queue from head to tail and write contents to output file
	q->ptr = q->head->next;
	while (q->ptr != NULL){
		fwrite(&q->ptr->data, 1, sizeof(q->ptr->data), output);
		q->ptr = q->ptr->next;
	}

	free(filename);
	fclose(output);
}

//visciously murder the empty .bin file
void killFile(struct queue *q, char ticker[])
{
	char *filename = getFilename(2,ticker);
	strcpy(filename,ticker);
	strcat(filename, ".bin");
	printf("All shares sold for %s\nDeleting file...\n",filename);

	remove(filename);
	free(filename);
}
