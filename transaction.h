#define MAX_SIZE 100

typedef struct {
    int year;
    int month;
    int day;
    char category[MAX_SIZE];
    char description[MAX_SIZE];
    int amount;
} Transaction;

void addTransaction(Transaction *t[], int *count);
void readTransaction(Transaction *t[], int count);
void updateTransaction(Transaction *t[], int count);
void removeTransaction(Transaction *t[], int *count);
void saveTransaction(Transaction *t[], int count);
int loadTransaction(Transaction *t[], int *count);
void searchTransaction(Transaction *t[], int count);
double krw_to_usd(double krw);
void exchageTransaction(Transaction *t[], int count);
void monthlySpend(Transaction *t[], int count);
void searchByCategory(Transaction *t[], int count);
void swap(Transaction **a, Transaction **b);
void amountSorting(Transaction *t [], int count);
void mostSpendCategory(Transaction *t [], int count);
void yearSummary(Transaction *t [], int count);

