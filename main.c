#include "phone_book.h"

int main()
{
	Contact *head=loadContactsFromFile();
	char choice;
	char name[MAX_NAME_LENGTH];

	do
	{
		displayMenu();
		printf("Enter your choice: ");
		scanf(" %c", &choice);
		getchar(); // Consume newline

		switch(tolower(choice))
		{
			case 'c':
				{
					Contact *newContact=createContact();
					if(newContact!=NULL)
					{
						if(isDuplicateContact(head, newContact->name))
						{
							printf("Contact with name '%s' already exists!\n", newContact->name);
							freeContacts(newContact);
						}
						else
						{
							newContact->next=head;
							head=newContact;
							printf("Contact added successfully!\n");
						}
					}
					break;
				}
			case 'p':
				printContacts(head);
				break;
			case 'd':
				printf("Enter name to delete: ");
				fgets(name, MAX_NAME_LENGTH, stdin);
				name[strcspn(name, "\n")]='\0';
				head=deleteContact(head, name);
				break;
			case 'f':
				printf("Enter name to find: ");
				fgets(name, MAX_NAME_LENGTH, stdin);
				name[strcspn(name, "\n")] = '\0';
				Contact *found = findContact(head, name);
				if (found == NULL) {
					printf("Contact not found!\n");
				}
				break;
			case 'e':
				printf("Enter name to edit: ");
				fgets(name, MAX_NAME_LENGTH, stdin);
				name[strcspn(name, "\n")]='\0';
				editContact(head, name);
				break;
			case 's':
				saveContactsToFile(head);
				printf("Contacts saved to file successfully!\n");
				break;
			case 'q':
				printf("Quitting application...\n");
				break;
			default:
				printf("Invalid choice! Please try again.\n");
		}
		printf("\n");
	}while(tolower(choice)!='q');

	saveContactsToFile(head);
	freeContacts(head);
	return 0;
}
