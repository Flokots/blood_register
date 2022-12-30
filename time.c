#include <time.h>
#include <stdio.h>
#include "functions.h"

void replace_char(char *string, char replace, char new);
// The formulas for a and m can be distilled down to these tables.
int Julian_A[12] = {1, 1, 0};
int Julian_M[12] = {10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int julian_day(struct tm *date)
{
    int a = Julian_A[date->tm_mon];
    int m = Julian_M[date->tm_mon];
    int y = date->tm_year + 1900 + 4800 - a;

    return date->tm_mday + ((153 * m + 2) / 5) + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

int main()
{
    struct tm date1, date2;
    char dTemp[]= "2022.02.02.";
    replace_char(dTemp, '.', '-');
    printf("Date Result: %s\n", dTemp);

    strptime(dTemp, "%F", &date1);
    strptime("2023-01-01.", "%F", &date2);

    // 305 days
    printf("%d days\n", julian_day(&date2) - julian_day(&date1));
}



