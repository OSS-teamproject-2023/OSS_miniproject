#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"



void addTransaction(Transaction *t[], int *count) {
    printf("Input year: ");
    scanf("%d", &t[*count]->year);
    printf("Input month: ");
    scanf("%d", &t[*count]->month);
    printf("Input day: ");
    scanf("%d", &t[*count]->day);
    printf("Input category: ");
    scanf("%s", t[*count]->category);
    printf("Input description: ");
    scanf("%s", t[*count]->description);
    printf("Input amount: ");
    scanf("%d", &t[*count]->amount);
    (*count)++;
}

void readTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("There are no transactions yet.\n");
        return;
    }
    printf("==================================================\n");
    printf("  Date   | Category | Description | Amount \n");
    printf("==================================================\n");
    for (int i = 0; i < count; i++) {
        printf("%04d-%02d-%02d | %-8s | %-11s | %5d \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->description, t[i]->amount);
    }
    printf("==================================================\n");
}

void updateTransaction(Transaction *t[], int count) {
    int index;
    printf("Input index: ");
    scanf("%d", &index);
    if (index < 0 || index >= count) {
        printf("Invalid index.\n");
        return;
    }
    printf("Input year: ");
    scanf("%d", &t[index]->year);
    printf("Input month: ");
    scanf("%d", &t[index]->month);
    printf("Input day: ");
    scanf("%d", &t[index]->day);
    printf("Input category: ");
    scanf("%s", t[index]->category);
    printf("Input description: ");
    scanf("%s", t[index]->description);
    printf("Input amount: ");
    scanf("%d", &t[index]->amount);
}

void removeTransaction(Transaction *t[], int *count) {
    int index;
    printf("Input index: ");
    scanf("%d", &index);
    if (index < 0 || index >= *count) {
        printf("Invalid index.\n");
        return;
    }
    
    for (int i = index; i < (*count) - 1; i++) {
        t[i]->amount = t[i+1]->amount;
        strcpy(t[i]->category, t[i+1]->category);
        t[i]->day = t[i+1]->day;
        strcpy(t[i]->description, t[i+1]->description);
        t[i]->month = t[i+1]->month;
        t[i]->year = t[i+1]->year;
    }
    (*count)--;

    if (t[*count]) free(t[*count]);
    t[*count] = NULL;
}

void saveTransaction(Transaction *t[], int count) {
    FILE *fp = fopen("transaction.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%d,%d,%s,%s,%d\n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->description, t[i]->amount);
    }
    fclose(fp);
    printf("Successfully saved.\n");
}

int loadTransaction(Transaction *t[], int *count) {
    FILE *fp = fopen("transactions.txt", "r");
    if (fp == NULL) {
        printf("File open failed!\n");
        return 0;
    }

    int i = 0;
    while (!feof(fp)) {
        int result = fscanf(fp, "%d %d %d %d %s\n", &t[i]->year, &t[i]->month, &t[i]->day, &t[i]->amount, t[i]->description);
        if (result == EOF || result != 5) {
            break;
        }
        i++;
    }
    fclose(fp);
    *count = i;

    printf("%d records read from file!\n", *count);
    return *count;
}



// 거래 내역 검색
void searchTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("No transaction history.\n");
        return;
    }
    char keyword[100];
    printf("Enter keyword to search: ");
    scanf("%s", keyword);
    printf("   Date     |  Category  |   Description   |  Amount  \n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strstr(t[i]->category, keyword) || strstr(t[i]->description, keyword)) {
            printf("%04d-%02d-%02d | %10s | %15s | %8d\n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->description, t[i]->amount);
        }
    }
}

//
double krw_to_usd(double krw) {
    double exchange_rate = 0.00088; // 1 USD = 1136.36 KRW
    return krw * exchange_rate;
}

void exchageTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("There are no transactions yet.\n");
        return;
    }
    printf("==================================================\n");
    printf("  Date   | Category | Description | Amount \n");
    printf("==================================================\n");
    for (int i = 0; i < count; i++) {
        double usd = krw_to_usd(t[i]->amount);
        printf("%04d-%02d-%02d | %-8s | %-11s | %.5f \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->description, usd);
    }
    printf("==================================================\n");
}