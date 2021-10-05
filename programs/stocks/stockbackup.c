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

	DIR* dirPtr;
	struct dirent* dirEntry;
	dirPtr = opendir(".");
	while ((dirEntry = readdir(dirPtr)) != NULL){
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

		//print name if extension is ".bin"
		if (strcmp(dirEntry->d_name + len - 4, ".bin") == 0){
			strncpy(ticker,dirEntry->d_name,i);
			ticker[i] = '\0';
			printf("%s\n", ticker);
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

//get single .bin file from user and read
void report()
{
	FILE* input;
	stock_t s;
	char filename[MAX_TICKER_LENGTH + 4];
   
	printf("Enter stock ticker symbol: ");
	scanf("%s", filename);
	strcat(filename, ".bin");
	printf("Ticker\tPurchase Date\tShares\tPrice Per Share\n");
	printf("--------------------------------------------------\n");
	input = fopen(filename, "rb");
	while(!feof(input)) {
		fread((char*)(&s), 1, sizeof(stock_t), input);
		printStock(s, s.date);
	}
	fclose(input);
	return;
}

void writeFile()
{
	FILE* output;
	stock_t s;
	int userResponse;  //0 when user is done 
	char filename[MAX_TICKER_LENGTH + 4];

	printf("Enter stock ticker symbol to buy: ");
	scanf("%s", filename);
	char ticker[MAX_TICKER_LENGTH];
	strcpy (ticker, filename);
	strcat(filename, ".bin");
	output = fopen(filename, "a");

	do{
		getStock(&s, ticker);
		fwrite((char*)(&s), 1, sizeof(stock_t), output);
		printf("Continue? (0 = no): ");
		scanf("%d", &userResponse);
	}while(userResponse != 0);

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

void sell(struct stock_t s, struct queue *q)
{
	FILE* input;
	char filename[MAX_TICKER_LENGTH + 4];
	int i = 1;

	printf("Enter stock ticker symbol to sell: ");
	scanf("%s", filename);
	strcat(filename, ".bin");
	input = fopen(filename, "r");

	if (input == NULL){
		printf("No owned stock for %s\n", filename);
		return;
	}

	while (!feof(input)){
		enqueue(q,i);
		i++;
		fread((char*)(&s), 1, sizeof(stock_t), input);
		printf("%d\n",q->tail->data);
	}

	fclose(input);
}

void enqueue(struct queue *q, int item)
{
	list_node *node;
	if (q->tail == NULL){    //if empty
		//q->tail = q->head->next;
		node = list_insert(q->head,item);
		q->head = q->tail = node;
	}
	else{
//		list_insert(q->tail,item);
//		q->tail = q->tail->next;
		node = list_insert(q->tail,item);
		q->tail->next = node;
		q->tail = node;
	}
}
	//enqueue(q,item)
	//if(!tail)//empty
	////insert(head,item)
	////q->tail=head->next
	//else
	////insert(tail,item)
	////q->tail=q->tail->next

//queue* dequeue(struct queue q)
//{
//	queue *result;
//	list_node = head->next;
//	if (!node){
//		return;
//	}
//	if (node == tail){
//		tail = NULL;
//		result = node->data;
//		list_delete(head);
//		return result;
//	}
//}

	//struct queue{
	////linked_list *head  //dummy node
	////linked_list *tail
	//}
	//dequeue(q)
	//node=head->next
	//if(!node)
	////return
	//if(node==tail)
	////tail=NULL
	//result=node->data
	//delete(head)
	//return result
