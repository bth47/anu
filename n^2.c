#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

typedef struct {
    unsigned int state;
    unsigned int a;
    unsigned int c;
    unsigned int m;
} linear_congruential_generator;

void init_lcg(linear_congruential_generator* lcg, unsigned int seed, unsigned int a, unsigned int c, unsigned int m);
unsigned int generate_random_number(linear_congruential_generator* lcg);
unsigned int my_rand(linear_congruential_generator* lcg, unsigned int range);

int solution(int* cards, int cards_amount);
int* shuffle_cards(int* cards, int cards_amount, int seed);
void print_cards(int* cards, int cards_amount);

int main() {

    int cards_amount;

    printf("카드 개수 입력 (2 이상의 자연수) : ");
    scanf("%d", &cards_amount);
    if (cards_amount == 1 || cards_amount <= 0) {
        exit(0);
    }

    int* cards = (int*)malloc(cards_amount * sizeof(int));

    unsigned int seed;
    printf("시드 값을 입력하세요 (1 ~ 1000) : ");
    scanf("%u", &seed);
    if (seed <= 1 || seed >= 1000) {
        exit(0);
    }

    clock_t start, finish;
    double runtime;

    start = clock();

    shuffle_cards(cards, cards_amount, seed);
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

    for (int j = 0; j < cards_amount; j++) {  
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

int* shuffle_cards(int* cards, int cards_amount, int seed) {

    linear_congruential_generator lcg;
    init_lcg(&lcg, seed, 1664525, 1013904223, (unsigned int)RAND_MAX + 1);

    for (int i = 0; i < cards_amount; i++) {
        cards[i] = i + 1;
    }

    for (int i = 0; i < cards_amount; i++) {
        int tmp = cards[i];
        int random_index = my_rand(&lcg, cards_amount);
        cards[i] = cards[random_index];
        cards[random_index] = tmp;
    }

    return cards;
}


void print_cards(int* cards, int cards_amount) {
    for (int i = 0; i < cards_amount; i++) {
        printf("%d ", cards[i]);
    }
    printf("\n");
}

void init_lcg(linear_congruential_generator* lcg, unsigned int seed, unsigned int a, unsigned int c, unsigned int m) {
    lcg->state = seed;
    lcg->a = a;
    lcg->c = c;
    lcg->m = m;
}

unsigned int generate_random_number(linear_congruential_generator* lcg) {
    lcg->state = (lcg->a * lcg->state + lcg->c) % lcg->m;
    return lcg->state;
}

unsigned int my_rand(linear_congruential_generator* lcg, unsigned int range) {
    unsigned int random_value = generate_random_number(lcg);
    return random_value % range;
}