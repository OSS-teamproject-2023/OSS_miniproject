#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"


void addTransaction(Transaction *t[], int *count) {
    printf("날짜를 입력하세요(2023 5 12): ");
    scanf("%d %d %d", &t[*count]->year, &t[*count]->month, &t[*count]->day);
    printf("구분을 입력하세요(수입: 1, 지출: -1) : ");
    scanf("%d", &t[*count]->identify);
    printf("카테고리를 입력하세요: ");
    scanf("%s", t[*count]->category);
    printf("세부내용을 입력하세요: ");
    scanf("%s", t[*count]->description);
    printf("금액을 입력하세요: ");
    scanf("%d", &t[*count]->amount);
    (*count)++;
}

void readTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("내용이 없습니다.\n");
        return;
    }
    printf("==================================================\n");
    printf("    날짜    | 구분 |  카테고리  |  금액  | 내용  \n");
    printf("==================================================\n");
    for (int i = 0; i < count; i++) {
        if(t[i]->identify == 1) {
            printf("%04d-%02d-%02d | 수입 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->amount, t[i]->description);
        } else {
            printf("%04d-%02d-%02d | 지출 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->amount, t[i]->description);

        }
    }
    printf("==================================================\n");
}

void updateTransaction(Transaction *t[], int count) {
    int index;
    printf("번호를 입력해주세요: ");
    scanf("%d", &index);
    if (index < 0 || index >= count) {
        printf("다시 입력해주세요.\n");
        return;
    }
    printf("날짜를 입력하세요(2023 5 12): ");
    scanf("%d %d %d", &t[index]->year, &t[index]->month, &t[index]->day);
    printf("구분을 입력하세요(수입: 1, 지출: -1) : ");
    scanf("%d", &t[index]->identify);
    printf("카테고리를 입력하세요: ");
    scanf("%s", t[index]->category);
    printf("세부내용을 입력하세요: ");
    scanf("%s", t[index]->description);
    printf("금액을 입력하세요: ");
    scanf("%d", &t[index]->amount);
}

void removeTransaction(Transaction *t[], int *count) {
    int index;
    printf("번호를 입력하세요: ");
    scanf("%d", &index);
    if (index < 0 || index >= *count) {
        printf("다시 입력해주세요.\n");
        return;
    }
    
    for (int i = index; i < (*count) - 1; i++) {
        t[i]->amount = t[i+1]->amount;
        strcpy(t[i]->category, t[i+1]->category);
        strcpy(t[i]->description, t[i+1]->description);
        t[i]->identify = t[i+1]->identify;
        t[i]->day = t[i+1]->day;
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
        printf("저장 실패.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %d %d %d %d %s %s\n", t[i]->year, t[i]->month, t[i]->day, t[i]->identify, t[i]->amount, t[i]->category, t[i]->description);
    }
    fclose(fp);
    printf("파일 저장 성공.\n");
}

int loadTransaction(Transaction *t[], int *count) {
    FILE *fp = fopen("transactions.txt", "rw");
    if (fp == NULL) {
        printf("파일 불러오기 실패!\n");
        return 0;
    }

    int i = 0;
    while (!feof(fp)) {
        int result = fscanf(fp, "%d %d %d %d %d %s\n", &t[i]->year, &t[i]->month, &t[i]->day, &t[i]->identify, &t[i]->amount, &t[i]->category, &t[i]->description);
        if (result == EOF || result != 6) {
            break;
        }
        i++;
    }
    fclose(fp);
    *count = i;

    printf("%d 파일 불러오기 성공!\n", *count);
    return *count;
}



// 거래 내역 검색
void searchTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("해당 내용이 없습니다.\n");
        return;
    }
    char keyword[100];
    printf("키워드를 입력하세요: ");
    scanf("%s", keyword);
    printf("==================================================\n");
    printf("    날짜    | 구분 |  카테고리  |  금액  | 내용  \n");
    printf("==================================================\n");
    for (int i = 0; i < count; i++) {
        if (strstr(t[i]->description, keyword)) {
            if(t[i]->identify == 1) {
                printf("%04d-%02d-%02d | 수입 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->amount, t[i]->description);
            } else {
                printf("%04d-%02d-%02d | 지출 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, t[i]->amount, t[i]->description);

            }
        }
    }
    printf("==================================================\n");

}


void yearSummary(Transaction *t[], int count) {
    int totalExpense = 0;
    int totalIncome = 0;
    int targetYear;
    printf("연도를 입력하세요: ");
    scanf("%d", &targetYear);


    for (int i = 0; i < count; i++) {
        if (t[i]->year == 2023) {
            if (t[i]->identify == -1) {
                // identify가 -1인 경우, 지출로 처리
                totalExpense += t[i]->amount;
            } else if (t[i]->identify == 1) {
                // identify가 1인 경우, 수입으로 처리
                totalIncome += t[i]->amount;
            }
        }
    }

    printf("%d년도의 총 지출: %d\n", targetYear, totalExpense);
    printf("%d년도의 총 수입: %d\n", targetYear, totalIncome);
}


double krw_to_usd(double krw) {
    double exchange_rate = 0.00088; // 1 USD = 1136.36 KRW
    return krw * exchange_rate;
}

void exchageTransaction(Transaction *t[], int count) {
    if (count == 0) {
        printf("내용이 없습니다.\n");
        return;
    }
    printf("==================================================\n");
    printf("  날짜   | 카테고리 | 구분 | 금액 | 내용 \n");
    printf("==================================================\n");
    for (int i = 0; i < count; i++) {
        double usd = krw_to_usd(t[i]->amount);
        if(t[i]->identify == 1) {
            printf("%04d-%02d-%02d | 수입 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, usd, t[i]->description);
        } else {
            printf("%04d-%02d-%02d | 지출 | %-8s | %5d | %-11s \n", t[i]->year, t[i]->month, t[i]->day, t[i]->category, usd, t[i]->description);

        }
    }
    printf("==================================================\n");
}


void mostSpendCategory(Transaction *t[], int count) {
    // 카테고리별 지출액 총합을 저장할 배열
    int categoryTotal[MAX_SIZE] = {0};

    // 각 카테고리별 지출액 총합 계산
    for (int i = 0; i < count; i++) {
        Transaction *transaction = t[i];
        int categoryIndex = -1;

        // 이미 계산된 카테고리인지 확인
        for (int j = 0; j < i; j++) {
            if (transaction->identify == -1 && ((t[j]->category, transaction->category) == 0)) {
                categoryIndex = j;
                break;
            }
        }

        if (t[i]->identify == -1 && categoryIndex == -1) {
            // 새로운 카테고리인 경우
            strcpy(t[i]->category, transaction->category);
            categoryTotal[i] = transaction->amount;
        } else if(t[i]->identify == -1 && categoryIndex != -1) {
            // 이미 계산된 카테고리인 경우
            categoryTotal[categoryIndex] += transaction->amount;
        }
    }

    // 상위 세 개의 카테고리 출력
    printf("가장 돈을 많이 쓴 카테고리 세 개:\n");
    for (int i = 0; i < 3; i++) {
        int maxIndex = -1;
        int maxTotal = -1;

        // 최대 지출액을 가진 카테고리 찾기
        for (int j = 0; j < count; j++) {
            if (categoryTotal[j] > maxTotal) {
                maxIndex = j;
                maxTotal = categoryTotal[j];
            }
        }

        // 최대 지출액 카테고리 출력
        printf("%d. 카테고리: %s, 총 지출액: %d\n", i + 1, t[maxIndex]->category, maxTotal);

        // 출력된 카테고리의 지출액 총합을 0으로 설정하여 다음으로 큰 값을 찾음
        categoryTotal[maxIndex] = 0;
    }
}
