#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
} *head,*temp,*new;

void create_clist(int);
void display();

int main()
{
	create_clist(5);
	display();
}

void create_clist(int n)
{
	int i;

	head = (struct node*)malloc(sizeof(struct node));
	new = (struct node*)malloc(sizeof(struct node));
	temp = (struct node*)malloc(sizeof(struct node));

	head = NULL;
	
	for (i=0;i<n;i++)
	{
		printf("i = %d ",i);
		if (head == NULL)
		{
			printf("\ninside if");
			new->data = i;
			new->next = NULL;
		
			head = new;
			new->next = head;
//			head->next = head;
			
			
		}

		else
		{
			printf("\ninside else");
			temp = head;
			
			new->data = i;
			new->next = NULL;
			
			while (temp->next != temp)
				temp = temp->next;

			temp->next = new;
			new->next = head;
		}
	}
	printf("\n");
}

void display()
{
	int i;
	temp = head;
	printf("inside display\n");
	while (temp->next != temp)
//	for (i=0;i<5;i++)
	{
		printf("%d ",temp->data);
		temp = temp->next;
	}
}
