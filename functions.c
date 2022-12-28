#include <stdio.h>
#include<stdlib.h>

int overAgain();
int emailCheck(char *eTemp);

// TODO: Check the string length
int str_length(char str[])
{
    int i;
    int count = 0;

    for (i = 0; str[i] != 0; i++)
    {
        count++;
    }
    return count;
}
//! Function to check that the date is valid
int dateCheck(char *dTemp)
{
    int yearDotIndex, monthDotIndex, dayDotIndex, dotIndex;
    int numberOfDots = -3;

    int count;
    count = str_length(dTemp);

    if (count == 11)
    {
        for (int i = 0; i < count; i++)
        {
            if (dTemp[i] == '.')
            {
                if (i == 4)
                {
                    yearDotIndex = i;
                }
                if (i == 7)
                {
                    monthDotIndex = i;
                }
                if (i == 10)
                {
                    dayDotIndex = i;
                }

                numberOfDots++;
                dotIndex = i;
            }
        }

        if (numberOfDots)
        {
            printf("Invalid date!\n");
            return 1;
        }

        if (!yearDotIndex || !monthDotIndex || !dayDotIndex || !dotIndex)
        {
            printf("Invalid date!\n");
            return 1;
        }
    }
    else if (count < 11)
    {
        printf("Invalid date!\n");
        return 1;
    }
    else if (count > 11)
    {
        printf("Invalid date!\n");
        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

int validateDate()
{
    char dateTemp[20];
    do
    {
        printf("Please enter the current date. (e.g. 2019.03.02. and press <ENTER> )");
        scanf("%s", dateTemp);

    } while ((dateCheck(dateTemp)));

    return 0;
}

// Print options to the user
int options()
{
    int option;
    printf("\n You can choose the following options:\n\n");
    printf("- 1: Print the list \n- 2: Add a new member to the list \n- 3: Search for a given blood group and alert the member found in the list by sending her/him an e-mail. \nIncrement the number of blood donations of the person in the list and overwrite his/her date of last blood donation in both the structure array and the file \n\n ");
    printf("Your choice: ");
    scanf("%d", &option);
    system("clear");
    return option;
}

//! Check Valid Email
int emailCheck(char *eTemp)
{
    int i = 0, dotIndex, atIndex, numberOfDots = -1, numberOfAts = -1, diff;

    while (eTemp[i])
    {
        if (eTemp[i] == '.')
        {
            dotIndex = i;
            numberOfDots++;
        }
        if (eTemp[i] == '@')
        {
            atIndex = i;
            numberOfAts++;
        }
        i++;
    }

    if ((diff = dotIndex - atIndex) < 0)
    {
        printf("Invalid email!\n");
        return 1;
    }
    if (numberOfDots || numberOfAts)
    {
        printf("Invalid email!\n");
        return 1;
    }
    if (!dotIndex || !atIndex || dotIndex == i - 1 || atIndex == i - 1 || diff == 1)
    {
        printf("Invalid email!\n");
        return 1;
    }

    return 0;
}

int overAgain()
{
    char again;

    printf("\nDo you want to try again? (y/n) ");
    scanf(" %c", &again);

    if (again == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int addAgain()
{
    char add;

    printf("One more new donor (y/n)? ");
    scanf(" %c", &add);

    if (add == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int continueProgram()
{
    char cont;

    printf("\nDo you want to keep the program running ? (y/n) ");
    scanf(" %c", &cont);

    if (cont == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to add new member

// If else statement to add another member
// Function to accept blood group as input and check and print who can/cannot donate blood
// Send email and notify the user
// If else to check if the user wants to continue
// Print Goodbye
// Exit the program
