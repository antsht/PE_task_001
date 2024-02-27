#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int f1;
    int f10;
    int f100;
    int f1000;
} flags;
typedef struct {
    int value;
    int token_length;
    char token[5];
    int multiplier;
} roman_token;

void init_tokens(roman_token *tokens);
void arabic_to_roman(int arabic_number, char *roman_number);
int roman_to_arabic(char *roman_number, roman_token *tokens);
void puckxit();
void check_roman_input(char *roman_number);

int main(void) {
    roman_token tokens[30];
    init_tokens(tokens);
    char roman_number[502] = {0};
    fgets(roman_number, 500, stdin);
    check_roman_input(roman_number);
    printf("%d", roman_to_arabic(roman_number, tokens));
    return 0;
}

void check_roman_input(char *roman_number) {
    if (roman_number[strlen(roman_number) - 1] == '\n') roman_number[strlen(roman_number) - 1] = '\0';

    if (strlen(roman_number) > 15) puckxit();
    if (strcmp(roman_number, "nihil") == 0 || strcmp(roman_number, "nulla") == 0 ||
        strcmp(roman_number, "N") == 0) {
        printf("%d", 0);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < (int)strlen(roman_number); ++i) {
        char c = roman_number[i];
        if ((c != 'I' && c != 'V' && c != 'X' && c != 'L' && c != 'C' && c != 'D' && c != 'M')) {
            fprintf(stderr, "Puck you, Verter!");
            exit(EXIT_FAILURE);
        }
    }
}
 
void puckxit() {
    fprintf(stderr, "Puck you, Verter!");
    exit(EXIT_FAILURE);
}

int roman_to_arabic(char *roman_number, roman_token *tokens) {
    char src[16] = {0};
    strcpy(src, roman_number);
    char *curr = NULL;
    int arabic_number = 0;
    flags flags = {0, 0, 0, 0};
    for (int i = 0; i < 30; ++i) {
        curr = strstr(roman_number, tokens[i].token);

        if (curr != NULL) {
            if (tokens[i].multiplier == 1 && flags.f1 == 1) puckxit();
            if (tokens[i].multiplier == 10 && flags.f10 == 1) puckxit();
            if (tokens[i].multiplier == 100 && flags.f100 == 1) puckxit();
            if (tokens[i].multiplier == 1000 && flags.f1000 == 1) puckxit();
            if (tokens[i].multiplier == 1) flags.f1 = 1;
            if (tokens[i].multiplier == 10) flags.f1 = 10;
            if (tokens[i].multiplier == 100) flags.f1 = 100;
            if (tokens[i].multiplier == 1000) flags.f1 = 1000;
            arabic_number += tokens[i].value;
            for (int c = 0; c < tokens[i].token_length; ++c) *(curr + c) = '-';
        }
    }

    char check[16] = {0};
    arabic_to_roman(arabic_number, check);
    // printf("DEBUG: %s %s %s\n", src, roman_number, check);
    if (strcmp(src, check) != 0) puckxit();
    return arabic_number;
}
void arabic_to_roman(int arabic_number, char *roman_number) {
    int num_1000s = arabic_number / 1000;
    int num_100s = (arabic_number % 1000) / 100;
    int num_10s = (arabic_number % 100) / 10;
    int num_1s = arabic_number % 10;
    if (num_1000s == 1) strcat(roman_number, "M");
    if (num_1000s == 2) strcat(roman_number, "MM");
    if (num_1000s == 3) strcat(roman_number, "MMM");
    if (num_100s == 1) strcat(roman_number, "C");
    if (num_100s == 2) strcat(roman_number, "CC");
    if (num_100s == 3) strcat(roman_number, "CCC");
    if (num_100s == 4) strcat(roman_number, "CD");
    if (num_100s == 5) strcat(roman_number, "D");
    if (num_100s == 6) strcat(roman_number, "DC");
    if (num_100s == 7) strcat(roman_number, "DCC");
    if (num_100s == 8) strcat(roman_number, "DCCC");
    if (num_100s == 9) strcat(roman_number, "CM");
    if (num_10s == 1) strcat(roman_number, "X");
    if (num_10s == 2) strcat(roman_number, "XX");
    if (num_10s == 3) strcat(roman_number, "XXX");
    if (num_10s == 4) strcat(roman_number, "XL");
    if (num_10s == 5) strcat(roman_number, "L");
    if (num_10s == 6) strcat(roman_number, "LX");
    if (num_10s == 7) strcat(roman_number, "LXX");
    if (num_10s == 8) strcat(roman_number, "LXXX");
    if (num_10s == 9) strcat(roman_number, "XC");
    if (num_1s == 1) strcat(roman_number, "I");
    if (num_1s == 2) strcat(roman_number, "II");
    if (num_1s == 3) strcat(roman_number, "III");
    if (num_1s == 4) strcat(roman_number, "IV");
    if (num_1s == 5) strcat(roman_number, "V");
    if (num_1s == 6) strcat(roman_number, "VI");
    if (num_1s == 7) strcat(roman_number, "VII");
    if (num_1s == 8) strcat(roman_number, "VIII");
    if (num_1s == 9) strcat(roman_number, "IX");
}

void init_tokens(roman_token *tokens) {
    roman_token t0 = {8, 4, "VIII", 1};
    tokens[0] = t0;
    roman_token t1 = {80, 4, "LXXX", 10};
    tokens[1] = t1;
    roman_token t2 = {800, 4, "DCCC", 100};
    tokens[2] = t2;
    roman_token t3 = {3, 3, "III", 1};
    tokens[3] = t3;
    roman_token t4 = {30, 3, "XXX", 10};
    tokens[4] = t4;
    roman_token t5 = {300, 3, "CCC", 100};
    tokens[5] = t5;
    roman_token t6 = {3000, 3, "MMM", 1000};
    tokens[6] = t6;
    roman_token t7 = {7, 3, "VII", 1};
    tokens[7] = t7;
    roman_token t8 = {70, 3, "LXX", 10};
    tokens[8] = t8;
    roman_token t9 = {700, 3, "DCC", 100};
    tokens[9] = t9;
    roman_token t10 = {2, 2, "II", 1};
    tokens[10] = t10;
    roman_token t11 = {20, 2, "XX", 10};
    tokens[11] = t11;
    roman_token t12 = {200, 2, "CC", 100};
    tokens[12] = t12;
    roman_token t13 = {2000, 2, "MM", 1000};
    tokens[13] = t13;
    roman_token t14 = {4, 2, "IV", 1};
    tokens[14] = t14;
    roman_token t15 = {40, 2, "XL", 10};
    tokens[15] = t15;
    roman_token t16 = {400, 2, "CD", 100};
    tokens[16] = t16;
    roman_token t17 = {6, 2, "VI", 1};
    tokens[17] = t17;
    roman_token t18 = {60, 2, "LX", 10};
    tokens[18] = t18;
    roman_token t19 = {600, 2, "DC", 100};
    tokens[19] = t19;
    roman_token t20 = {9, 2, "IX", 1};
    tokens[20] = t20;
    roman_token t21 = {90, 2, "XC", 10};
    tokens[21] = t21;
    roman_token t22 = {900, 2, "CM", 1000};
    tokens[22] = t22;
    roman_token t23 = {1, 1, "I", 1};
    tokens[23] = t23;
    roman_token t24 = {5, 1, "V", 1};
    tokens[24] = t24;
    roman_token t25 = {10, 1, "X", 10};
    tokens[25] = t25;
    roman_token t26 = {50, 1, "L", 10};
    tokens[26] = t26;
    roman_token t27 = {100, 1, "C", 100};
    tokens[27] = t27;
    roman_token t28 = {500, 1, "D", 100};
    tokens[28] = t28;
    roman_token t29 = {1000, 1, "M", 1000};
    tokens[29] = t29;
}