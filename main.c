#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

// Define donor struct
typedef struct donor {
    char name[20];
    char blood_group[3];
    char email[20];
    int donations;
    char last_donation_date[11];

} donor;

// Get name of the file as a command line argument
int input(donor **d, char *fName, char *dateString, int *l);
void list(donor *d, int l);

int main () 
{
    donor *donors = NULL; 
    char fileName[100]; 
    char dateString[11];
    int length = 0, again;


    while ((again = input(&donors, fileName, dateString, &length)))
    {
        if (again == 2)
        {
            return 0;
        }
    }

    while (1)
    {
        switch(options())
        {
            case 1: 
                list(donors, length);
                break;
            

        }
    }
   
    options();
}

int input(donor **d, char *fName, char *dateString, int *l)
{
    FILE *fp = NULL;
    char ch;
    int i;

    printf("Type the name of the text file you want to open: ");
    scanf("%s", fName);

    printf("Please enter the current date: ");
    scanf("%s", dateString);

    if (!(fp = fopen(fName, "r")))
    {
        printf("ERROR: file cannot be opened. (Its path may be wrong). \n");
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

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            (*l)++;
        }
    }

    if (!(*d = (donor *) malloc(*l*sizeof(donor))))
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
        fscanf(fp, "%s%s%s%d%s", (*d)[i].name,  (*d)[i].blood_group, (*d)[i].email, &(*d)[i].donations, (*d)[i].last_donation_date);
    }

    fclose(fp);
    printf("The data has been into the list.\n");

    return 0;
}

void list(donor *d, int l)
{
    int i;
    for (i = 0; i < l; i++)
    {
        printf("Name: %-20s bloodgroup: %-3s email: %-20s  donations: %d last_donation_date: %-11s\n", d[i].name, d[i].blood_group, d[i].email, d[i].donations, d[i].last_donation_date);
    }
}

