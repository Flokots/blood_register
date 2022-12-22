#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

// Define donor struct
typedef struct donor {
    char name[20];
    char blood_group[3];
    char email[20];
    int donations;

} donor;

// Get name of the file as a command line argument
int input(donor **d, char *fName, int *l);

int main () 
{
    donor *donors = NULL; 
    char fileName[100]; 
    int length = 0, again;

    again = input(&donors, fileName, &length);

    while (again)
    {
        if (again == 2)
        {
            return 0;
        }
    }

   
    options();
}

int input(donor **d, char *fName, int *l)
{
    FILE *fp = NULL;
    char ch;
    int i;

    printf("Type the name of the text file you want to open: ");
    scanf("%s", fName);

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
        fscanf(fp, "%s%s%s%d", (*d)[i].name, (*d)[i].blood_group, (*d)[i].email, &(*d)[i].donations);
    }

    fclose(fp);
    printf("The data has been into the list.\n");

    return 0;
}
