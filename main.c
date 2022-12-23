#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h" 

#define MAX_YR 9999
#define MIN_YR 1900

//Define structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

// Define donor struct
typedef struct donor
{
    char name[20];
    char blood_group[3];
    char email[20];
    int donations;
    char last_donation_date[11];

} donor;

void list(donor *d, int l);
int readFile(donor **d, char *fName, int *l);

int main(int argc, char *argv[])
{
    donor *donors = NULL;
    char dateString[11];
    int length = 0;
    int again;

    // Get name of the file as a command line argument
    if (argc == 2)
    {
        char *fileName = NULL;
        fileName = argv[1];
        readFile(&donors, fileName, &length);
    }
    else if (argc > 2)
    {
        printf("Too many arguments supplied. \n");
        return 0;
    }
    else
    {
        printf("Pass the name of the file as a command line argument. \n");
        return 0;
    }

    printf("Please enter the current date: ");
    scanf("%s", dateString);

    do 
     {
        switch (options())
        {
        case 1:
            list(donors, length);
            break;
        }
    }
    while (overAgain());
   
}

void list(donor *d, int l)
{
    int i;
    for (i = 0; i < l; i++)
    {
        printf("Name: %-20s bloodgroup: %-3s email: %-20s  donations: %d last_donation_date: %-11s\n", d[i].name, d[i].blood_group, d[i].email, d[i].donations, d[i].last_donation_date);
    }
}

int readFile(donor **d, char *fName, int *l)
{
     printf("This program helps you to register the blood donors\n\n");

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

        if (!(*d = (donor *)malloc(*l*sizeof(donor))))
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
            fscanf(fp, "%s%s%s%d%s", (*d)[i].name, (*d)[i].blood_group, (*d)[i].email, &(*d)[i].donations, (*d)[i].last_donation_date);
        }

        fclose(fp);

        printf("The data has been read into the list.\n");

        return 0;
}
