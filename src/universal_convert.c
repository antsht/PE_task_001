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
roman_token new_token(int value, int token_length, char *token, int multiplier);

int main(void) {
    roman_token tokens[30];
    init_tokens(tokens);

    int mode = -1;
    if (scanf("%d", &mode) != 1 || !(mode == 1 || mode == 2)) puckxit();
    getchar();

    if (mode == 1) {
        char roman_number[502] = {0};
        fgets(roman_number, 500, stdin);
        check_roman_input(roman_number);
        printf("%d", roman_to_arabic(roman_number, tokens));
    }
    if (mode == 2) {
        int arabic_number = 0;
        if (scanf("%d", &arabic_number) != 1 || !(arabic_number >= 1 && arabic_number <= 3999)) puckxit();

        char roman_number[16] = {0};
        arabic_to_roman(arabic_number, roman_number);
        printf("%s", roman_number);
    }
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

roman_token new_token(int value, int token_length, char *token, int multiplier) {
    roman_token r_token;
    r_token.value = value;
    r_token.token_length = token_length;
    strcpy(r_token.token, token);
    r_token.multiplier = multiplier;
    return r_token;
}

void init_tokens(roman_token *tokens) {
    tokens[0] = new_token(8, 4, "VIII", 1);
    tokens[1] = new_token(80, 4, "LXXX", 10);
    tokens[2] = new_token(800, 4, "DCCC", 100);
    tokens[3] = new_token(3, 3, "III", 1);
    tokens[4] = new_token(30, 3, "XXX", 10);
    tokens[5] = new_token(300, 3, "CCC", 100);
    tokens[6] = new_token(3000, 3, "MMM", 1000);
    tokens[7] = new_token(7, 3, "VII", 1);
    tokens[8] = new_token(70, 3, "LXX", 10);
    tokens[9] = new_token(700, 3, "DCC", 100);
    tokens[10] = new_token(2, 2, "II", 1);
    tokens[11] = new_token(20, 2, "XX", 10);
    tokens[12] = new_token(200, 2, "CC", 100);
    tokens[13] = new_token(2000, 2, "MM", 1000);
    tokens[14] = new_token(4, 2, "IV", 1);
    tokens[15] = new_token(40, 2, "XL", 10);
    tokens[16] = new_token(400, 2, "CD", 100);
    tokens[17] = new_token(6, 2, "VI", 1);
    tokens[18] = new_token(60, 2, "LX", 10);
    tokens[19] = new_token(600, 2, "DC", 100);
    tokens[20] = new_token(9, 2, "IX", 1);
    tokens[21] = new_token(90, 2, "XC", 10);
    tokens[22] = new_token(900, 2, "CM", 1000);
    tokens[23] = new_token(1, 1, "I", 1);
    tokens[24] = new_token(5, 1, "V", 1);
    tokens[25] = new_token(10, 1, "X", 10);
    tokens[26] = new_token(50, 1, "L", 10);
    tokens[27] = new_token(100, 1, "C", 100);
    tokens[28] = new_token(500, 1, "D", 100);
    tokens[29] = new_token(1000, 1, "M", 1000);
}