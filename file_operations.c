#include "phone_book.h"

void saveContactsToFile(Contact *head)
{
	FILE *file=fopen(FILENAME, "wb");
	if(file == NULL) 
	{
		printf("Error opening file for writing!\n");
		return;
	}

	Contact *current = head;
	while(current!=NULL) 
	{
		// Write contact info
		fwrite(current, sizeof(Contact) - sizeof(Contact*), 1, file);

		// Write phone numbers
		PhoneNumber *phone=current->phoneHead;
		int phoneCount=0;
		while(phone!=NULL)
		{
			phoneCount++;
			phone=phone->next;
		}

		fwrite(&phoneCount, sizeof(int), 1, file);

		phone=current->phoneHead;
		while(phone!=NULL)
		{
			fwrite(phone, sizeof(PhoneNumber) - sizeof(PhoneNumber*), 1, file);
			phone=phone->next;
		}

		current=current->next;
	}

	fclose(file);
}

Contact* loadContactsFromFile()
{
	FILE *file=fopen(FILENAME, "rb");
	if(file==NULL)
       	{
		return NULL;
	}

	Contact *head=NULL;
	Contact *tail=NULL;

	while(1)
	{
		Contact *contact=(Contact*)malloc(sizeof(Contact));
		if(contact==NULL)
		{
			printf("Memory allocation failed!\n");
			break;
		}

		if(fread(contact, sizeof(Contact) - sizeof(Contact*), 1, file)!=1)
	       	{
			free(contact);
			break;
		}

		contact->next=NULL;
		contact->phoneHead=NULL;

		// Read phone numbers
		int phoneCount;
		if (fread(&phoneCount, sizeof(int), 1, file)!= 1) 
		{
			free(contact);
			break;
		}

		PhoneNumber *phoneTail=NULL;
		for(int i=0; i<phoneCount; i++)
	       	{
			PhoneNumber *phone=(PhoneNumber*)malloc(sizeof(PhoneNumber));
			if(phone==NULL)
		       	{
				printf("Memory allocation failed!\n");
				break;
			}

			if(fread(phone, sizeof(PhoneNumber) - sizeof(PhoneNumber*), 1, file)!=1)
		       	{
				free(phone);
				break;
			}

			phone->next=NULL;

			if(contact->phoneHead==NULL)
			{
				contact->phoneHead=phone;
				phoneTail=phone;
			}
			else
			{
				phoneTail->next=phone;
				phoneTail=phone;
			}
		}

		if(head==NULL)
		{
			head=contact;
			tail=contact;
		} 
		else 
		{
			tail->next=contact;
			tail=contact;
		}
	}

	fclose(file);
	return head;
}

void freeContacts(Contact *head)
{
	Contact *current=head;
	while(current!=NULL)
	{
		Contact *nextContact=current->next;

		// Free phone numbers
		PhoneNumber *phone=current->phoneHead;
		while(phone!=NULL)
	       	{
			PhoneNumber *nextPhone=phone->next;
			free(phone);
			phone = nextPhone;
		}

		free(current);
		current = nextContact;
	}
}
