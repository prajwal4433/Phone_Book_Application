#include "phone_book.h"

void displayMenu()
{
	printf("\n------------------MENU--------------------------\n");
	printf("c/C: Create a new contact\n");
	printf("p/P: Print all contacts\n");
	printf("d/D: Delete contact\n");
	printf("f/F: Find contact\n");
	printf("e/E: Edit a contact\n");
	printf("s/S: To save the contacts in the file\n");
	printf("q/Q: Quit from app\n");
	printf("------------------------------------------------\n");
}

void toLowerCase(char *str)
{
	for(int i=0; str[i]; i++)
	{
		str[i]=tolower(str[i]);
	}
}

Contact* createContact()
{
	Contact *newContact=(Contact*)malloc(sizeof(Contact));
	if(newContact==NULL)       
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	// Initialize all fields
	newContact->phoneHead=NULL;
	newContact->next=NULL;
	newContact->email[0]='\0';
	newContact->address[0]='\0';

	printf("Enter contact name: ");
	__fpurge(stdin);
	fgets(newContact->name, MAX_NAME_LENGTH, stdin);
	newContact->name[strcspn(newContact->name, "\n")]='\0';

	// Add first phone number
	addPhoneNumber(newContact);

	char choice;
	// Add email
	printf("Do you want to add email? (Y/N): ");
	__fpurge(stdin);
	scanf(" %c", &choice);
	getchar();
	if(tolower(choice)=='y') 
	{
		printf("Enter email: ");
		__fpurge(stdin);
		fgets(newContact->email, MAX_EMAIL_LENGTH, stdin);
		newContact->email[strcspn(newContact->email, "\n")]='\0';
	}

	// Add address
	printf("Do you want to add address? (Y/N): ");
	__fpurge(stdin);
	scanf(" %c", &choice);
	getchar();
	if(tolower(choice)=='y')
	{
		printf("Enter address: ");
		__fpurge(stdin);
		fgets(newContact->address, MAX_ADDRESS_LENGTH, stdin);
		newContact->address[strcspn(newContact->address, "\n")]='\0';
	}

	return newContact;
}

void addPhoneNumber(Contact *contact)
{
	char choice;
	do
	{
		PhoneNumber *newNumber=(PhoneNumber*)malloc(sizeof(PhoneNumber));
		if(newNumber==NULL)
		{
			printf("Memory allocation failed!\n");
			return;
		}

		printf("Enter phone number: ");
		__fpurge(stdin);
		fgets(newNumber->number, MAX_PHONE_LENGTH, stdin);
		newNumber->number[strcspn(newNumber->number, "\n")]='\0';
		newNumber->next = contact->phoneHead;
		contact->phoneHead=newNumber;

		printf("Do you want to add another number to the same name? (Y/N): ");
		__fpurge(stdin);
		scanf(" %c", &choice);
		getchar();
	}while(tolower(choice)=='y');
}

void printContacts(Contact *head)
{
	if(head==NULL)
	{
		printf("No contacts available!\n");
		return;
	}

	printf("\nCONTACT LIST:\n");
	printf("------------------------------------------------\n");
	Contact *current=head;
	while(current!=NULL)
	{
		printf("Name: %s\n", current->name);
		PhoneNumber *phone=current->phoneHead;
		int count=1;
		while(phone!=NULL)
	       	{
			printf("Phone %d: %s\n", count++, phone->number);
			phone=phone->next;
		}

		if(current->email[0] != '\0')
	       	{
			printf("Email: %s\n", current->email);
		}

		if(current->address[0] != '\0')
	       	{
			printf("Address: %s\n", current->address);
		}

		printf("------------------------------------------------\n");
		current=current->next;
	}
}

Contact* deleteContact(Contact *head, const char *name)
{
	if(head==NULL)
       	{
		printf("Contact list is empty!\n");
		return NULL;
	}

	Contact *current=head;
	Contact *prev=NULL;

	while(current!=NULL)
	{
		if(strcasecmp(current->name,name)==0)
	       	{
			if(prev==NULL)
			{
				// Deleting head
				head=current->next;
			}
			else
			{
				prev->next=current->next;
			}

			// Free phone numbers
			PhoneNumber *phone=current->phoneHead;
			while(phone!= NULL)
			{
				PhoneNumber *temp=phone;
				phone=phone->next;
				free(temp);
			}

			free(current);
			printf("Contact '%s' deleted successfully!\n", name);
			return head;
		}
		prev=current;
		current=current->next;
	}

	printf("Contact '%s' not found!\n", name);
	return head;
}

Contact* findContact(Contact *head, const char *name) {
	Contact *current=head;
	while(current!=NULL)
	{
		if(strcasecmp(current->name, name)==0)
		{
			printf("\nContact Found:\n");
			printf("------------------------------------------------\n");
			printf("Name: %s\n", current->name);

			PhoneNumber *phone=current->phoneHead;
			int count=1;
			while(phone!=NULL)
			{
				printf("Phone %d: %s\n", count++, phone->number);
				phone=phone->next;
			}

			if(current->email[0] != '\0')
			{
				printf("Email: %s\n", current->email);
			}

			if(current->address[0] != '\0')
			{
				printf("Address: %s\n", current->address);
			}

			printf("------------------------------------------------\n");
			return current;
		}
		current=current->next;
	}
	return NULL;
}

void editContact(Contact *head, const char *name)
{
	Contact *contact=findContact(head, name);
	if(contact==NULL)
	{
		printf("Contact not found!\n");
		return;
	}

	printf("\nEditing Contact: %s\n", contact->name);
	printf("What do you want to edit?\n");
	printf("1. Name\n");
	printf("2. Phone numbers\n");
	printf("3. Email\n");
	printf("4. Address\n");
	printf("Enter your choice: ");

	int choice;
	__fpurge(stdin);
	scanf("%d", &choice);
	getchar();

	switch(choice)
	{
		case 1:
			{
				printf("Enter new name: ");
				__fpurge(stdin);
				fgets(contact->name, MAX_NAME_LENGTH, stdin);
				contact->name[strcspn(contact->name, "\n")]= '\0';
				printf("Name updated successfully!\n");
				break;
			}
		case 2: 
			{
				// Free existing phone numbers
				PhoneNumber *phone=contact->phoneHead;
				while(phone!=NULL)
			       	{
					PhoneNumber *temp=phone;
					phone=phone->next;
					free(temp);
				}
				contact->phoneHead=NULL;

				// Add new phone numbers
				addPhoneNumber(contact);
				printf("Phone numbers updated successfully!\n");
				break;
			}
		case 3: 
			{
				printf("Enter new email (leave empty to remove): ");
				__fpurge(stdin);
				fgets(contact->email, MAX_EMAIL_LENGTH, stdin);
				contact->email[strcspn(contact->email, "\n")]='\0';
				printf("Email updated successfully!\n");
				break;
			}
		case 4: 
			{
				printf("Enter new address (leave empty to remove): ");
				__fpurge(stdin);
				fgets(contact->address, MAX_ADDRESS_LENGTH, stdin);
				contact->address[strcspn(contact->address, "\n")]='\0';
				printf("Address updated successfully!\n");
				break;
			}
		default:
			printf("Invalid choice!\n");
	}
}

int isDuplicateContact(Contact *head, const char *name)
{
	Contact *current=head;
	while (current!=NULL)
	{
		if(strcasecmp(current->name, name)==0)
		{
			return 1;
		}
		current=current->next;
	}
	return 0;
}

