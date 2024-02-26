#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_4_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s);
void check_3_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s);
void check_2_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s);
void check_1_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s);

void arabic_to_roman(int arabic_number, char *roman_number);
int roman_to_arabic(char *roman_number);
void puckxit();

int main(void) {
    int mode = -1;
    if (scanf("%d", &mode) != 1 && !(mode == 1 || mode == 2)) puckxit();
    getchar();

    if (mode == 1) {
        char roman_number[16] = {0};
        int i = 0;
        char c;
        while ((c = getchar()) != 10) {
            if ((c != 'I' && c != 'V' && c != 'X' && c != 'L' && c != 'C' && c != 'D' && c != 'M') ||
                i == 15) {
                printf("Puck you, Verter!");
                exit(EXIT_FAILURE);
            }
            roman_number[i++] = c;
        }

        printf("%d", roman_to_arabic(roman_number));
    }
    if (mode == 2) {
        int arabic_number = 0;
        if (scanf("%d", &arabic_number) != 1 && !(arabic_number >= 1 && arabic_number <= 3999)) puckxit();

        char roman_number[16] = {0};
        arabic_to_roman(arabic_number, roman_number);
        printf("%s", roman_number);
    }
    return 0;
}

void puckxit() {
    printf("Puck you, Verter!");
    exit(EXIT_FAILURE);
}

int roman_to_arabic(char *roman_number) {
    char src[16] = {0};
    strcpy(src, roman_number);
    char *curr = NULL;
    int arabic_number = 0;
    int flag_1s = 0;
    int flag_10s = 0;
    int flag_100s = 0;
    int flag_1000s = 0;

    check_4_len(curr, roman_number, &arabic_number, &flag_1s, &flag_10s, &flag_100s);
    check_3_len(curr, roman_number, &arabic_number, &flag_1s, &flag_10s, &flag_100s, &flag_1000s);
    check_2_len(curr, roman_number, &arabic_number, &flag_1s, &flag_10s, &flag_100s, &flag_1000s);
    check_1_len(curr, roman_number, &arabic_number, &flag_1s, &flag_10s, &flag_100s, &flag_1000s);

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

void check_4_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s) {
    curr = strstr(roman_number, "VIII");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 8;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
        *(curr + 3) = '-';
    }
    curr = strstr(roman_number, "LXXX");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 80;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
        *(curr + 3) = '-';
    }
    curr = strstr(roman_number, "DCCC");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 800;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
        *(curr + 3) = '-';
    }
}

void check_3_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s) {
    curr = strstr(roman_number, "III");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 3;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "XXX");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 30;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "CCC");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 300;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "MMM");
    if (curr != NULL) {
        if (*flag_1000s == 1) puckxit();
        *flag_1000s = 1;
        *arabic_number += 3000;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "VII");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 7;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "LXX");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 70;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
    curr = strstr(roman_number, "DCC");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 700;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }
}

void check_2_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s) {
    curr = strstr(roman_number, "II");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 2;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "XX");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 20;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "CC");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 200;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "MM");
    if (curr != NULL) {
        if (*flag_1000s == 1) puckxit();
        *flag_1000s = 1;
        *arabic_number += 2000;
        *curr = '-';
        *(curr + 1) = '-';
        *(curr + 2) = '-';
    }

    curr = strstr(roman_number, "IV");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 4;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "XL");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 40;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "CD");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 400;
        *curr = '-';
        *(curr + 1) = '-';
    }

    curr = strstr(roman_number, "VI");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 6;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "LX");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 60;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "DC");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 600;
        *curr = '-';
        *(curr + 1) = '-';
    }

    curr = strstr(roman_number, "IX");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 9;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "XC");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 90;
        *curr = '-';
        *(curr + 1) = '-';
    }
    curr = strstr(roman_number, "CM");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 900;
        *curr = '-';
        *(curr + 1) = '-';
    }
}

void check_1_len(char *curr, char *roman_number, int *arabic_number, int *flag_1s, int *flag_10s,
                 int *flag_100s, int *flag_1000s) {
    curr = strstr(roman_number, "I");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 1;
        *curr = '-';
    }
    curr = strstr(roman_number, "V");
    if (curr != NULL) {
        if (*flag_1s == 1) puckxit();
        *flag_1s = 1;
        *arabic_number += 5;
        *curr = '-';
    }
    curr = strstr(roman_number, "X");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 10;
        *curr = '-';
    }

    curr = strstr(roman_number, "L");
    if (curr != NULL) {
        if (*flag_10s == 1) puckxit();
        *flag_10s = 1;
        *arabic_number += 50;
        *curr = '-';
    }

    curr = strstr(roman_number, "C");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 100;
        *curr = '-';
    }

    curr = strstr(roman_number, "D");
    if (curr != NULL) {
        if (*flag_100s == 1) puckxit();
        *flag_100s = 1;
        *arabic_number += 500;
        *curr = '-';
    }

    curr = strstr(roman_number, "M");
    if (curr != NULL) {
        if (*flag_1000s == 1) puckxit();
        *flag_1000s = 1;
        *arabic_number += 1000;
        *curr = '-';
    }
};