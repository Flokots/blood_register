#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

//* Define donor struct
typedef struct donor
{
    char name[20];
    char blood_group[10];
    char email[20];
    int donations;
    char last_donation_date[20];

} donor;

int readFile(donor **d, char *fName, int *l);
int newDonor(donor **d, int *l);
int findDonors(donor *d, int l, char *dateCopy);
void list(donor *d, int l);
void copy(char *fromHere, char *toHere);

int main(int argc, char *argv[])
{
    donor *donors = NULL;
    int length = 0;

    //* Get name of the file as a command line argument
    if (argc == 2)
    {
        char *fileName = NULL;
        char dateTemp[20];
        char dateCopy[20];

        fileName = argv[1];
        FILE *fp = NULL;
        int i;

        readFile(&donors, fileName, &length);

        do
        {
            printf("Please enter the current date. (e.g. 2019.03.02. and press <ENTER> )");
            scanf("%s", dateTemp);
        } while ((dateCheck(dateTemp)));

        copy(dateTemp, dateCopy);

        printf("\n- Program name: %s, file to be processed (%s) is open.\n", argv[0], argv[1]);
        printf("\n- Number of blood donors in the list is checked. \n");
        printf("\n- Memory block required for the structure array has been allocated.\n");
        printf("\n- The content of the file (called \"%s\") has been read into the structure array.\n ", argv[1]);

        do
        {
            switch (options())
            {
            case 1:
                list(donors, length);
                break;

            case 2:
                do
                {
                    newDonor(&donors, &length);
                } while (addAgain());
                break;
            case 3:
                findDonors(donors, length, dateCopy);
                break;
            default:
                printf("There are 3 options only: 1, 2 or 3. \n");
            }
        } while (continueProgram());

        fp = fopen(fileName, "w");

        for (i = 0; i < length; i++)
        {
            fprintf(fp, "%-20s \t%-15s \t\t%-20s  \t\t%d \t\t\t\t %-20s\n", donors[i].name, donors[i].blood_group, donors[i].email, donors[i].donations, donors[i].last_donation_date);
        }
        fflush(fp);
        fclose(fp);

        free(donors);
        printf("Program exits. Have a nice day!\n");

        return 0;
    }
    else if (argc > 2)
    {
        printf("\nToo many arguments supplied. \n");
        return 0;
    }
    else
    {
        printf("\nPass the name of the file as a command line argument. \n");
        return 0;
    }
}

//* Print the list of registered blood donors.
void list(donor *d, int l)
{
    int i;
    printf("\n\t\t\t\t\t\t\t\t\tBLOOD DONORS' REGISTER \n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nID \t Name \t\t\tBlood Group \t\t\tEmail \t\t\tNumber of Donations\t\t\tDate of last Donation\t\t\t\n");
    for (i = 0; i < l; i++)
    {
        printf("\n%d \t %-20s \t%-15s \t\t%-20s  \t\t%d \t\t\t\t %-20s\n", i + 1, d[i].name, d[i].blood_group, d[i].email, d[i].donations, d[i].last_donation_date);
    }
}

//* Read content of the file into the dynamic structure array.
int readFile(donor **d, char *fName, int *l)
{
    printf("\nThis program helps you to calendar the blood donors\n\n");

    char ch;
    int i;

    FILE *fp = fopen(fName, "r");

    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            (*l)++;
        }
    }

    if (!(*d = (donor *)malloc(*l * sizeof(donor))))
    {
        printf("ERROR: there isn't enough memory. \n");
        if (overAgain())
        {
            return 1;
        }
        else
        {
            printf("Program exits.\n");
            return 2;
        }
    }

    rewind(fp);

    for (i = 0; i < *l; i++)
    {
        fscanf(fp, "%s %s %s %d %s", (*d)[i].name, (*d)[i].blood_group, (*d)[i].email, &(*d)[i].donations, (*d)[i].last_donation_date);
    }

    fclose(fp);

    return 0;
}

//* Add a new donor
int newDonor(donor **d, int *l)
{
    char emailTemp[20];
    char dateTemp[20];
    printf("Name: ");
    scanf("%s", (*d)[*l].name);

    printf("Blood Group: ");
    scanf("%s", (*d)[*l].blood_group);

    do
    {
        printf("Email: ");
        scanf("%s", emailTemp);
    } while (emailCheck(emailTemp));

    copy(emailTemp, (*d)[*l].email);

    printf("Number of blood donations: ");
    scanf("%d", &(*d)[*l].donations);

    //* Validate the date
    do
    {
        printf("Date: ");
        scanf("%s", dateTemp);
    } while (dateCheck(dateTemp));

    copy(dateTemp, (*d)[*l].last_donation_date);

    if (!(*d = (donor *)realloc(*d, ++(*l) * sizeof(donor))))
    {
        printf("ERROR: there isn't enough memory\n");
        if (overAgain())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

//* Find donors with the given blood group
int findDonors(donor *d, int l, char *dateCopy)
{
    char bloodGroup[10], lDDCopy[20];
    char *donationStatus;
    int i, j;
    int dateDiff;
    struct tm lastDD, currentDate;

    printf("\n Which blood group do you need? ");
    scanf("%s", bloodGroup);

    int bloodGroupLength = str_length(bloodGroup);

    printf("\n\t\t\t\t\t\t\t\t\tLIST OF MATCHES: \n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nID \t Name \t\tBlood Group \t\tEmail \t\t\tNumber of Donations\t\tDate of last Donation\t\tCan/Cannot donate\n");

    for (i = 0; i < l; i++)
    {
        if (bloodGroupLength == str_length(d[i].blood_group))
        {
            j = 0;
            while (j < bloodGroupLength && bloodGroup[j] == d[i].blood_group[j])
            {
                j++;
            }
            if (j == bloodGroupLength)
            {
                copy(d[i].last_donation_date, lDDCopy);

                replace_char(dateCopy, '.', '-');
                replace_char(lDDCopy, '.', '-');

                strptime(dateCopy, "%F", &currentDate);
                strptime(lDDCopy, "%F", &lastDD);

                dateDiff = julian_day(&currentDate) - julian_day(&lastDD);

                if (dateDiff >= 90)
                {
                    donationStatus = "Can donate.";
                }
                else
                {
                    donationStatus = "Cannot donate.";
                }

                printf("\n%d \t%-20s %-15s \t%-20s \t%d \t\t\t\t %-20s\t\t%s\n", i + 1, d[i].name, d[i].blood_group, d[i].email, d[i].donations, d[i].last_donation_date, donationStatus);
                d[i].donations++;
                replace_char(dateCopy, '-', '.');
                copy(dateCopy, d[i].last_donation_date);

                printf("E-mail(s) has been sent, number of blood donation has been incremented in both the structure array and the file");
            }
        }
    }
    return 0;
}
