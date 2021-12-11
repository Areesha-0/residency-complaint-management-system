#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>

//macros
#define ENTER 13
#define TAB 9
#define BKSP 8
#define COORDINATE1 48
#define COORDINATE2 43
#define SPACE 32

void title();					//title to be printed 
void user_type();				//select user type
void admin_login();				//verifies user 
void admin_menu();				//selection of menu options
int admin_search();				//search for complaint
void admin_view_complaint();	//view complaints
int add_complaint();			//add complaints
int resident_registration();    //resident registration
void verify_resident();			//resident verification
void resident_menu();			//selection of menu options
int _helpline();				//searching for helplines
int register_help();			//registration of helpers
void ex_it(void);			    //exit program
void gotoxy(int, int);			//using coordinates for console representation

int user;						//global variable for user type selected

//complaint stores variables required to store compaint data
struct complaint 
{
	char name[30];
	int house;
	int street;
	char contact_num[12];
	char complaint[1000];
};

struct complaint c;

//resident stores variables required to store data of residents
struct resident
{
	char name[30];
	int house;
	int street;
	char contact_num[12];
};

struct resident r;

//helpline stores variables required to store data of helpers
struct helpline
{
	char name[30];
	char contact_num[12];
	char category[12];
};

struct helpline h;

int main()
{
	title(); //prints the title

	user_type(); //initiates the program after user-type selection
}

void title()
{
	gotoxy(0, 0);
	printf("________________________________________________________________________________________________________________________");//printing title
	gotoxy(45, 2);
	printf("C O M P L A I N T   P O R T A L");
	gotoxy(50,3);
	printf("Housing  Society  ABC");
	gotoxy(0, 4);
	printf("________________________________________________________________________________________________________________________");
}

void user_type()
{
	gotoxy(45, 6);
	printf("Welcome to the complaint portal\n");
	gotoxy(45, 7);
	printf("Please select user type\n");
	gotoxy(45, 8);
	printf("1. Administrator\n");
	gotoxy(45, 9);
	printf("2. Resident\n");
	gotoxy(45, 10);
	printf("3. Exit\n");
	gotoxy(45, 12);
	printf("Enter user type: ");
	scanf_s("%d", &user);

	//selecting user type
	switch (user)
	{  
	case 1:
		admin_login();
		break;
	case 2:
		verify_resident();
		break;
	case 3:
		ex_it();
		exit(1);
	}
}

void admin_login()
{
	system("cls");
	title();

	int tries = 0, i = 0;					 //tries to keep track of login details being entered, i counter for each character in password	 
	char password[10] = { '\0' };            //password array to be inputted by the user
	char username[7] = { '\0' };			 //username array to be inputted by the user
	char orignal_username[] = "admin";		 //the correct username given by the program
	char orignal_password[] = "password";	 //the correct password given by the program
	char asterisk='a', ignore;				 //char inputted to be converted to asterisk
							  
	//printing the headers
	gotoxy(40, 6);
	printf("\tA D M I N  T E R M I N A L");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	do {
	
		//Prompting the user to enter login details
		printf("Please enter login details\n");
		ignore=getchar();

		printf("\nUsername:  ");
		gets(username);

		printf("\nPassword (Please press ENTER to confirm your response):  ");

		i = 0;                             //each time the loop is run, the counter is set to 0
		while (i < 10)                     //masks the password with asterisk
		{
			asterisk = _getch();           //taking password from user as a series of characters

			if (asterisk == ENTER || asterisk == TAB) /*if tab or enter is pressed the program is signalled to
														terminate the password array*/
			{
				password[i] = '\0';        //initialising that enter or tab key to terminating point so that loop breaks and no more input is taken
				break;
			}

			else if (asterisk == BKSP)     //if backspace is pressed then we remove the previous character entered
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");       //character entered is removed and then the second \b removes the previous \b so a new char can be added
				}
			}
			else
			{
				password[i++] = asterisk;  //each time i is incremented asterisk is printed in place of it
				printf("*");
			}
		}

		//if the password and user name match then the system continues
		if (strcmp(username, orignal_username) == NULL && strcmp(password, orignal_password) == NULL) 
		{																							 
			printf("\n\nLogin is successful! Press any key to continue....\n");
			ignore=getchar();
			admin_menu();
			break;
		}
		else    
		{
			if (tries < 3)  //gives user chance to try again
			{
				printf("\n\nLogin is unsuccessful, Please try again!\n");
				tries++;
			}

			if (tries == 3) //if three tries are availed then system locked
			{
				printf("\n\nYou have tried too many times. Account blocked!");
				return;
			}
		}
	} while (tries <= 3);  //After three tries the user can no longer login
}

void admin_menu()
{
	system("cls");
	title();

	int menu_select; //stores the menu item selected by the user

	//printing headers and menu items
	gotoxy(40, 6);
	printf("\t  A D M I N  M E N U");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	gotoxy(COORDINATE1, 8);
	printf("Please select from below\n");
	gotoxy(COORDINATE1, 9);
	printf("1. Add complaint");
	gotoxy(COORDINATE1, 10);
	printf("2. Search complaint");
	gotoxy(COORDINATE1, 11);
	printf("3. View complaints");
	gotoxy(COORDINATE1, 12);
	printf("4. Resident Registration");
	gotoxy(COORDINATE1, 13);
	printf("5. Help Registration");
	gotoxy(COORDINATE1, 14);
	printf("6. Exit");
	gotoxy(COORDINATE1, 16);
	printf("Enter your choice: ");
	scanf_s("%d", &menu_select);

	//selecting from the menu to proceed
	switch (menu_select)
	{
	case 1:
		add_complaint();

		//decides further action based on user input
		printf("Do you want to add another complaint?(Y/N)"); 
		char ans = getchar();
		ans == 'Y' || ans == 'y' ? add_complaint() : admin_menu();

		break;
	case 2:
		admin_search();
		break;
	case 3:
		admin_view_complaint();
		break;
	case 6:
		ex_it();
		exit(0);
	case 4:
		resident_registration();
		break;
	case 5:
		register_help();
		break;
	default:
		printf("Please select from the given options\n");
		Sleep(1000);   //stops the program for a second
		admin_menu();  //takes the program to admin's menu screen
		break;
	}
}

int add_complaint()
{

	system("cls");
	title();

	FILE* complaint_data = fopen("complaint_data.txt", "a");  //opening the file in append mode

	char ignore;  //vairable for storing getchar() value to prevent warnings

	//printing headers
	gotoxy(40, 6);
	printf("\tA D D   C O M P L A I N T");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	ignore = getchar();

	printf("\nEnter the following details\n");

//INPUTTING CONTACT NUMBER FROM THE USER
D:
	printf("\nEnter contact number: ");
	gets(c.contact_num);

	//verifying the contact number length i.e. supposed to be 11 numbers
	if (strlen(c.contact_num) > 12 || strlen(c.contact_num) < 11)
	{
		printf("Invalid. Contact number must be exact 11 numbers.");
		goto D;
	}

	else
	{
		//verifying that the number consists of all numbers
		for (unsigned int j = 0; j < strlen(c.contact_num); j++) 
		{
			if (!(isalpha(c.contact_num[j])));
			else
			{
				printf("Invalid phone number.\n");
				fflush(stdin);
				goto D;
				break;
			}
		}
	}

//INPUTTING THE NAME FROM USER
B:
	printf("\nName:");
	gets(c.name);

	//checking length of the name
	if (strlen(c.name) > 30 || strlen(c.name) < 3)
	{
		printf("Invalid. Enter a name in range of 3 to 30 characters.\n");
		goto B;
	}

	else
	{
		//making sure the name entered has no digits
		for (unsigned int i = 0; i < strlen(c.name); i++) 
		{
			if (isalpha(c.name[i]) || c.name[i] == SPACE);
			else                   
			{
				printf("Invalid. Enter your name in aplhabets ONLY\n");
				goto B;
				break;
			}
		}
	}

//INPUTTING STREET NUMBER FROM USER
	printf("\nStreet: ");
	scanf_s("%d", &c.street);

//INPUTTING HOUSE NUMBER FROM USER
	printf("\nHouse: ");
	scanf_s("%d", &c.house);

//INPUTTING COMPLAINT DETAILS FROM USER
E:
	printf("\nType your complaint details(word limit: 1000): ");
	ignore=getchar();
	gets(c.complaint);

	//Verifying eligibility of complaint by checking its length
	if (strlen(c.complaint) > 1000 || strlen(c.complaint) < 5) 
	{
		printf("Invalid. Word limit is in range of 5 to characters.\n");
		goto E;
	}

	//printing above inputted data in the file
	fprintf(complaint_data, "%s\t\t%s\t%d\t%d\t%s\n", c.contact_num, c.name, c.street, c.house, c.complaint);

	printf("\nComplaint submitted successfully!\n");

	//closing the file
	fclose(complaint_data);

	return 0;
}

int admin_search()
{
	system("cls");
	title();

	FILE* complaint_data = fopen("complaint_data.txt", "r"); //opening file in read mode

	char singleline[1000];		//a string array to read characters from each line of the file
	char* z = 'j';				//pointer character to verify file existence
	int match = 0;				//keeping track of the records being searched from the file 
	char ignore;				//stores getchar() to avoid warnings
	char num[11] = { 0 };		//character array to store the contact number inputted by the user

	//printing headers
	gotoxy(40, 6);
	printf("     S E A R C H   C O M P L A I N T");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

F:
D:
	//prompting the user to input their contact to look for their comlaint in the file
	printf("\nEnter contact number: ");
	ignore = getchar();
	gets(num);

	//verifying the contact number length i.e. supposed to be 11 numbers
	if (strlen(num) >= 12 || strlen(num) < 11)
	{
		printf("Invalid. Contact number must be exact 11 numbers.");
		fflush(stdin);
		goto D;
	}

	else
	{
		//making sure no aplhabet is entered
		for (unsigned int j = 0; j < strlen(num); j++)
		{
			if (!(isalpha(num[j])));
			else
			{
				printf("Invalid phone number.\n");
				fflush(stdin);
				goto D;
				break;
			}
		}
	}

	printf("Contact Number\t\tName\t\t\tStreet\t\tHouse\t\tComplaint\n");
	printf("****************************************************************************************************************\n");

	//scans file until the end looking for the contact number entered
	while (!feof(complaint_data))
	{
		//scans the file line by line
		z = fgets(singleline, 1000, complaint_data);

		//loop breaks if file doesnt exist
		if (z == NULL)
			break;

		//uses the buffer to compare it to the inputted contact to look for the record
		if (strstr(singleline, num) != NULL)
		{
			puts(singleline); //printing the line that contains the contact number admin asked for
			match++;
		}
	}

	//file is closed
	fclose(complaint_data);

	//if no entry is matched then admin is prompted to repeat the above procedure again
	if (match == 0)
	{
		printf("No record found.Please try again\n");
		goto F;
	}

	//asking the admin if he/she wants to keep seaching for complaints or not
	printf("Do you want to search another complaint?(Y/N)");
	char ans = getchar();
	ans == 'Y' || ans == 'y' ? admin_search() : admin_menu();

	return 0;
}

void admin_view_complaint()
{
	system("cls");
	title();

	FILE* complaint_data = fopen("complaint_data.txt", "r"); //opening file in read mode

	char singleLine[1000];		//a string array to read characters from each line of the file
	char* z = 1;				//character pointer to make sure the file exists

	//printing headers
	gotoxy(40, 6);
	printf("\tV I E W   C O M P L A I N T");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	printf("\nContact Number\t\tName\t\t\tStreet\t\tHouse\t\tComplaint\n");
	printf("****************************************************************************************************************\n");

	while (1)										
	{
		z = fgets(singleLine, 1000, complaint_data); //using fgets function to scan the file line by line

		if (z == NULL)								 //if character value returned is NULL then the loop breaks
			break;

		puts(singleLine);							 //printing the lines read
	}

	//file is closed
	fclose(complaint_data); 

	//making sure if the admin wants to keep viewing complaints or not
	printf("\nDo you want to continue looking at the complaints? (Y/N)");
	char ans = _getch();
	ans == 'Y' || ans == 'y' ? admin_view_complaint() : admin_menu();
}

int resident_registration()
{
	system("cls");
	title();

	FILE* resident_data = fopen("resident_data.txt", "a"); //opening the file in append mode

	char ignore; //vairable for storing getchar() value to prevent warnings

	//printing headers
	gotoxy(40, 6);
	printf("\tR E G I S T R A T I O N");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	printf("\nEnter the following details\n");

//INPUTTING CONTACT NUMBER FROM THE ADMIN
D:
	printf("\nEnter contact number: ");
	ignore = getchar();
	gets(r.contact_num);

	//verifying the contact number length i.e. supposed to be 11 numbers
	if (strlen(r.contact_num) >= 12 || strlen(r.contact_num) < 11)
	{
		printf("Invalid. Contact number must be exact 10 numbers.");
		fflush(stdin);
		goto D;
	}
	else
	{
		//verifying that the number consists of all numbers
		for (unsigned int j = 0; j < strlen(r.contact_num); j++)
		{
			if (!(isalpha(r.contact_num[j])));
			else
			{
				printf("Invalid phone number.\n");
				fflush(stdin);
				goto D;
				break;
			}
		}
	}

//INPUTTING THE NAME FROM ADMIN
B:
	printf("\nName:");
	gets(r.name);

	//checking length of the name
	if (strlen(r.name) > 30 || strlen(r.name) < 3)
	{
		printf("Invalid. Enter a name in range of 3 to 30 characters.\n");
		goto B;
	}
	else
	{
		//making sure the name entered has no digits
		for (unsigned int i = 0; i < strlen(c.name); i++)
		{
			if (isalpha(r.name[i]) || r.name[i] == SPACE);

			else
			{
				printf("Invalid. Enter your name in aplhabets ONLY\n");
				fflush(stdin);
				goto B;
				break;
			}
		}
	}

//INPUTTING STREET NUMBER FROM ADMIN
	printf("\nStreet: ");
	scanf_s("%d", &r.street);

//INPUTTING HOUSE NUMBER FROM ADMIN
	printf("\nHouse: ");
	scanf_s("%d", &r.house);

	//printing above inputted data in the file
	fprintf(resident_data, "%s\t\t%s\t\t%d\t\t%d\n", r.contact_num, r.name, r.street, r.house);

	printf("\nRegistration successfull!\n");

	//closing the file
	fclose(resident_data);

	//making sure if the admin wants to keep registering residents or not
	printf("Do you want to continue registration?(Y/N)");
	char ans = getchar();
	ignore = getchar();
	ans == 'Y' || ans == 'y' ? resident_registration() : admin_menu();

	return 0;
}

int register_help()
{
	system("cls");
	title();

	//printing headers
	gotoxy(40, 6);
	printf("\tR E G I S T R A T I O N");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	char ignore;                                  //vairable for storing getchar() value to prevent warnings

	FILE* helpline = fopen("helpline.txt", "a");  //opening the file in append mode

	printf("Please enter the following details\n");

//INPUTTING CATEGORY FROM THE ADMIN
	printf("Which category do you fit in?\n1. Plumber\n2. Electrician\n3. Garbage Collector\n4. Gardner\n5. Carpenter\n6. Mason\n7. Janitor\n8. Painter\n\t: ");
	ignore = getchar();
	gets(h.category);

//INPUTTING THE NAME FROM ADMIN
B:
	printf("\nName:");
	gets(h.name);

	//making sure the name entered has no digits
	if (strlen(h.name) > 30 || strlen(h.name) < 3)
	{
		printf("Invalid. Enter a name in range of 3 to 30 characters.\n");
		goto B;
	}
	else
	{
		//making sure the name entered has no digits
		for (unsigned int i = 0; i < strlen(h.name); i++)
		{
			if (isalpha(h.name[i]) || h.name[i] == SPACE);
			else
			{
				printf("Invalid. Enter your name in aplhabets ONLY\n");
				fflush(stdin);
				goto B;
				break;
			}
		}
	}

//INPUTTING CONTACT NUMBER FROM THE ADMIN
D:
	printf("\nEnter contact number: ");
	gets(h.contact_num);

	//verifying the contact number length i.e. supposed to be 11 numbers
	if (strlen(h.contact_num) > 12 || strlen(h.contact_num) < 11)
	{
		printf("Invalid. Contact number must be exact 11 numbers.\n");
		goto D;
	}
	else
	{
		//verifying that the number consists of all numbers
		for (unsigned int j = 0; j < strlen(h.contact_num); j++)
		{
			if (!(isalpha(h.contact_num[j])));
			else
			{
				printf("Invalid phone number.\n");
				fflush(stdin);
				goto D;
				break;
			}
		}
	}

	//printing above inputted data in the file
	fprintf(helpline, "%s\t\t%s\t\t%s\n", h.category, h.name, h.contact_num);

	printf("\nRegistration successfull!\n");

	//closing the file
	fclose(helpline);

	//making sure if the admin wants to keep registering helpers or not
	printf("Do you want to continue registration?(Y/N)");
	char ans = getchar();
	ans == 'Y' || ans == 'y' ? register_help() : admin_menu();

	return 0;
}

void resident_menu()
{
	system("cls");
	title();

	int choice; //stores the menu item serial number selected by the resident

	//printing headers and menu items
	gotoxy(36, 6);
	printf("\t    R E S I D E N T   T E R M I N A L");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	gotoxy(COORDINATE2, 9);
	printf("Welcome to the complaint portal");
	gotoxy(COORDINATE2, 10);
	printf("Please select from below");
	gotoxy(COORDINATE2, 11);
	printf("1. Add complaint");
	gotoxy(COORDINATE2, 12);
	printf("2. Search Help");
	gotoxy(COORDINATE2, 13);
	printf("3. Exit");
	gotoxy(COORDINATE2, 15);
	printf("Enter your choice: ");
	scanf_s("%d", &choice);

	//application of selection of above menu items
	switch (choice) 
	{
	case 1:
		add_complaint();

		//verifying if the resident wishes to keep registering complaints
		printf("Do you want to add another complaint?(Y/N)");
		char ans = getchar();
		ans == 'Y' || ans == 'y' ? add_complaint() : resident_menu();

		break;
	case 2:
		_helpline();
		break;
	case 3:
		ex_it();
		exit(0);
		break;
	default:
		gotoxy(43, 18);
		printf("\nPlease select from the given options!");

		Sleep(1000);     //pauses the system for a second

		resident_menu(); //leads the resident to the menu once again
		break;
	}
}

void verify_resident()
{

	system("cls");
	title();

	FILE* resident_data = fopen("resident_data.txt", "r"); //opening file in read mode

	//printing headers
	gotoxy(40, 6);
	printf("\tV E R I F I C A T I O N");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");


	char singleline[1000];			//a string array to read characters from each line of the file
	char num[11] = { '\0' };		//character array to store the contact number inputted by the user
	char* z = 'j';					//pointer character to verify file existence
	char ignore;					//stores getchar() to avoid warnings
	int match = 0;					//keeping track of the records being searched from the file 

	ignore = getchar();

	printf("\n\nKindly verify yourself.\n\n");

//INPUTTING CONTACT NUMBER FROM THE RESIDENT
D:
	printf("\nEnter contact number: ");
	gets(num);

	//verifying the contact number length i.e. supposed to be 11 numbers
	if (strlen(num) > 12 || strlen(num) < 11)
	{
		printf("Invalid. Contact number must be exact 11 numbers.");
		fflush(stdin);
		goto D;
	}
	else
	{
		//verifying that the number consists of all numbers
		for (unsigned int j = 0; j < strlen(num); j++)
		{
			if (!(isalpha(num[j])));
			else
			{
				printf("Invalid phone number.\n");
				goto D;
				break;
			}
		}
	}

	while (1)
	{
		//loop breaks if file doesnt exist
		if (z == NULL)
			break;

		//scans the file line by line 
		z = fgets(singleline, 1000, resident_data);

		//if both strings match, access to the portal is allowed
		if (strstr(singleline, num) != 0)
		{
			printf("Record found! You can now use the portal.\nPress any key to continue\n");
			_getch();
			Sleep(2000);
			resident_menu();
			match++;
			break;
		}
	}

	//if no record of the resident is found, resident is prompted to get registered first
	if (match == 0)
	{
		printf("No record found.You cannot use the complaint portal. Please contact the adminiteration to registered.\n");
		_getch();
		Sleep(1000);	//pauses the system for a second
		system("cls");	//clears the screen
		title();        //prints the title
		user_type();    //above procedure is repeated again
	}

	//file is closed
	fclose(resident_data);
}

int _helpline()
{
F:
	system("cls");
	title();

	//printing headers
	gotoxy(40, 6);
	printf("\t     H E L P L I N E");
	gotoxy(0, 7);
	printf("________________________________________________________________________________________________________________________");

	char ignore;					//stores getchar() to avoid warnings
	char category[12] = {'\0'};		//character array to store the category inputted by the user
	char singleline[1000];			//a string array to read characters from each line of the file
	char* z = 'a';					//pointer character to verify file existence
	int match = 0;					//keeping track of the records being searched from the file

	FILE* helpline = fopen("helpline.txt", "r"); //opening file in read mode

	printf("\n\nPlease enter the following details\n");

//INPUTTING CATEGORY FROM THE RESIDENT
	printf("Who are you looking for?\n1. Plumber\n2. Electrician\n3. Garbage Collector\n4. Gardner\n5. Carpenter\n6. Mason\n7. Janitor\n8. Painter\n\t: ");
	ignore=getchar();
	gets(category);

	printf("Category\tName\t   \t\tContact Number\n");
	printf("****************************************************************************************************************\n");

	//scans file until the end looking for the categories entered
	while (!feof(helpline))
	{
		//scans the file line by line
		z = fgets(singleline, 1000, helpline);

		//loop breaks if file doesnt exist
		if (z == NULL)
			break;
		//uses the buffer to compare it to the inputted category to look for the record
		if (strstr(singleline, category) != NULL)
		{
			puts(singleline);	//printing the line that contains the category user asked for
			match++;
		}
	}
	
	//file is closed
	fclose(helpline);

	//if no entry is matched then resident is prompted to repeat the above procedure again
	if (match == 0)
	{
		printf("No record found.Please try again\n");

		Sleep(1000); //pauses the program for a second
		 
		goto F;
	}

	//asking the resident if he/she wants to keep seaching for more categories or not
	printf("Do you want to search for another category?(Y/N)");
	char ans = getchar();
	ans == 'Y' || ans == 'y' ? _helpline() : resident_menu();

	return 0;
}

void ex_it(void)
{
	char ignore;         

	printf("Press any key to exit\n");

	ignore = _getch();	 //stores and ignores the value of the key pressed to exit the program
}

void gotoxy(int x, int y)
{
	COORD position = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}