#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

// Define donor struct
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
void list(donor *d, int l);
void copy(char *fromHere, char *toHere);

int main(int argc, char *argv[])
{
    donor *donors = NULL;
    int length = 0;
    int again;

    // Get name of the file as a command line argument
    if (argc == 2)
    {
        char *fileName = NULL;
        fileName = argv[1];
        readFile(&donors, fileName, &length);

        validateDate();

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
                printf("\n Which blood group do you need? ");
                break;
            default:
                printf("There are 3 options only: 1, 2 or 3. \n");
            }
        } while (continueProgram());
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

// Function to print the list
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

void copy(char *fromHere, char *toHere)
{
    int i = 0;
    while (fromHere[i])
    {
        toHere[i] = fromHere[i];
        i++;
    }
    toHere[i] = 0;
}

// Function to add new Donor
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

    // validate New Date
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
