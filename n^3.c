#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

int solution(int* cards, int cards_amount);
int* shuffle_cards(int* cards, int cards_amount);
void print_cards(int* cards, int cards_amount);

int main() {

    int cards_amount;

    printf("카드 개수 입력 (2 이상의 자연수) : ");
    scanf("%d", &cards_amount);
    if (cards_amount == 1 || cards_amount <= 0) {
        exit(0);
    }

    int* cards = (int*)malloc(cards_amount * sizeof(int));

    clock_t start, finish;
    double runtime;

    start = clock();

    shuffle_cards(cards, cards_amount);
    print_cards(cards, cards_amount);
    int final_score = solution(cards, cards_amount);
    printf("최종 점수: %d\n", final_score);

    finish = clock();
    runtime = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f초 입니다.", runtime);

    free(cards);
    return 0;
}

int solution(int* cards, int cards_amount) {
    int index = 0;
    int first_group_score = 0;
    int second_group_score = 0;
    int final_score = 0;

    int* first_group_flag = (int*)malloc(cards_amount * sizeof(int));
    int* second_group_flag = (int*)malloc(cards_amount * sizeof(int));

    first_group_score = 0;

    for (int j = 0; j < cards_amount; j++) {
        first_group_flag[j] = 0;
    }

    first_group_flag[0] = 1;
    index = cards[0] - 1;
    first_group_score++;

    while (first_group_flag[index] != 1) {
        first_group_flag[index] = 1;
        index = cards[index] - 1;
        first_group_score++;
    }

    if (first_group_score == cards_amount) {
        final_score = first_group_score;
        return final_score;
    }

    for (int j = 0; j < cards_amount; j++) {  //수정된 부분입니다.
        second_group_flag[j] = first_group_flag[j];
    }

    for (int b = 0; b < cards_amount; b++) {
        second_group_score = 0;
        if (second_group_flag[b] == 0) {
            second_group_flag[b] = 1;
            index = cards[b] - 1;
            second_group_score++;

            while (second_group_flag[index] != 1) {
                index = cards[index] - 1;
                second_group_score++;
            }
            if (final_score < second_group_score + first_group_score)
                final_score = second_group_score + first_group_score;
        }
    }
    free(first_group_flag);
    free(second_group_flag);
    return final_score;
}

int* shuffle_cards(int* cards, int cards_amount) {
    int equal_flag;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < cards_amount; i++) {
        while (1) {
            cards[i] = rand() % cards_amount + 1;
            equal_flag = 0;

            for (int j = 0; j < i; j++) {
                if (cards[j] == cards[i]) {
                    equal_flag = 1;
                    break;
                }
            }
            if (!equal_flag) break;
        }
    }
    return cards;
}

void print_cards(int* cards, int cards_amount) {
    for (int i = 0; i < cards_amount; i++) {
        printf("%d ", cards[i]);
    }
    printf("\n");
}