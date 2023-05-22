#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"

void print_menu(void) {
    printf("\n[ 가계부 프로그램 ]\n");
    printf("1. 내용 추가\n");
    printf("2. 전체 읽기\n");
    printf("3. 수정하기\n");
    printf("4. 삭제하기\n");
    printf("5. 찾기\n");
    printf("6. 전체 읽기(USD)\n");
    printf("7. 월별 지출\n");
    printf("8. 카테고리 검색하기\n");
    printf("9. 금액순 정렬\n");
    printf("10. 가장 돈을 많이 쓴 카테고리\n");
    printf("11. 연도 총 정리\n");
    printf("0. 종료\n");
    printf("\n");
}

int main() {
    Transaction *t[100];
    int count = 0;

    count = loadTransaction(t, &count);

    int menu;
    while(1) {
        print_menu();
        printf("메뉴 선택 > ");
        scanf("%d", &menu);
        switch(menu) {
            case 0:
                saveTransaction(t, count);
                printf("프로그램 종료.\n");
                return 0;
            case 1:
                t[count] = (Transaction *)malloc(sizeof(Transaction));
                addTransaction(t, &count);
                break;
            case 2:
                readTransaction(t, count);
                break;
            case 3:
                updateTransaction(t, count);
                break;
            case 4:
                removeTransaction(t, &count);
                break;
            case 5:
                searchTransaction(t, count);
                break;
            case 6:
                exchageTransaction(t, count);
                break;
            case 7:
                monthlySpend(t, count);
                break;
            case 8:
                searchByCategory(t, count);
                break;
            case 9:
                amountSorting(t, count);
                break;
            case 10:
                mostSpendCategory(t, count);
                break;
            case 11:
                yearSummary(t, count);
                break;
            default:
                printf("다시 입력해주세요.\n");
                break;
        }
    }
    return 0;
}

