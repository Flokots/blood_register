#include <stdio.h>


// Enter the current date
//! Function to check that the date is valid
// Print options to the user
int options()
{
    int option;
    printf("\n You can choose the following options:\n\n");
    printf(" 1: Print the list \n 2: Add a new member to the list \n 3: Search for a given blood group and alert the member found in the list by sending her/him an e-mail. \nIncrement the number of blood donations of the person in the list and overwrite his/her date of last blood donation in both the structure array and the file \n\n ");
    printf("Your choice: ");
    scanf("%d", &option);
    system("clear");
    return option;
}
// Use a case switch to process user options
// Function to print the list
// Function to add new member
//! Check Valid Email 
int emailCheck(char *eTemp){
	int i = 0, dotIndex, atIndex, numberOfDots = -1, numberOfAts = -1, diff;

	while(eTemp[i])
	{
		if(eTemp[i] == '.'){	dotIndex = i; numberOfDots++;	}
		if(eTemp[i] == '@'){	atIndex = i; numberOfAts++;	}
		i++;
	}
	
	if((diff = dotIndex - atIndex) < 0){ return 1; }
	if(numberOfDots || numberOfAts){ return 1; }
	if(!dotIndex || !atIndex || dotIndex == i-1 || atIndex == i-1 || diff == 1){ return 1; }
	
	
	return 0;
}


int overAgain()
{
    char again;

    printf("Do you want to try again? (y/n) ");
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
// If else statement to add another member
// Function to accept blood group as input and check and print who can/cannot donate blood
// Send email and notify the user
// If else to check if the user wants to continue
// Print Goodbye
// Exit the program