/* File: stock.h
 * Description: Structures and prototypes for stock info
 */
#ifndef STOCK_H
#define STOCK_H
#include "date.h"

#define MAX_PRICE 1000
#define MAX_TICKER_LENGTH 6
typedef struct stock_t
{
	char ticker[MAX_TICKER_LENGTH];
	date_t date;   //date bought
	int numShares;
	double pricePerShare;
} stock_t;
#include "linkedList.h"

typedef struct queue
{
	list_node *head, *tail, *ptr;
} queue;

char *getFilename(int key, char ticker[]);

//print list of all owned stocks
void printOwned();

//print all info relevant to single stock
void printStock(struct stock_t s, struct date_t date);

//read stock file to print
void report();

void buy();

void getStock(struct stock_t *s, char ticker[]);

void fillQueue(struct queue *q);

void enqueue(struct queue *q, stock_t item);

int dequeue(struct queue *q);

void getSharesToSell(struct queue *q, struct stock_t s, int totalShares);

void sellShares(struct queue *q, struct stock_t s, int numToSell, double stockPrice);

void writeNew(struct queue *q, struct stock_t s);

void killFile(struct queue *q, char ticker[]);
#endif
