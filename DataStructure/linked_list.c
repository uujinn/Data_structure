#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{

	struct node *left;
	int win;
	int lose;
	struct node *right;

} node;

typedef struct linkedlist
{

	node *head;
	node *computer_ptr;

} linkedlist;

typedef linkedlist List;

node *CreateNode(void)
{

	node *newNode = (node *)malloc(sizeof(node));
	newNode->win = 0;
	newNode->lose = 0;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void InitList(List *plist, int a)
{

	int i = 0;
	plist->head = CreateNode();
	node *curhead = plist->head;

	for (i = 0; i < a - 1; i++)
	{

		if (curhead == plist->head)
		{
			node *newNode = CreateNode();
			curhead->right = newNode;
			newNode->left = curhead;
			newNode->right = plist->head;
			plist->head->left = newNode;

			curhead = newNode;
		}

		else
		{

			node *newNode = CreateNode();
			curhead->right = newNode;
			newNode->left = curhead;
			curhead = newNode;
			newNode->right = plist->head;
			plist->head->left = newNode;
		}
	}
}

void win(List *plist)
{

	plist->computer_ptr->win += 1;

	if (plist->computer_ptr->win >= 3)
	{
		plist->computer_ptr->win = 0;
		node *newNode;
		newNode = CreateNode();
		plist->computer_ptr->right->left = newNode;
		newNode->right = plist->computer_ptr->right;
		plist->computer_ptr->right = newNode;
		newNode->left = plist->computer_ptr;
	}

	plist->computer_ptr = plist->computer_ptr->right;
}

void lose(List *plist)
{

	plist->computer_ptr->lose += 1;

	if (plist->computer_ptr->lose >= 3)
	{

		if (plist->computer_ptr == plist->head)
		{

			plist->head->left->right = plist->head->right;
			plist->head->right->left = plist->head->left;
			plist->head = plist->head->right;
		}

		else
		{

			plist->computer_ptr->left->right = plist->computer_ptr->right;
			plist->computer_ptr->right->left = plist->computer_ptr->left;
		}
	}

	plist->computer_ptr = plist->computer_ptr->left;
}

void printList(List *plist)
{

	int i = 1, m = 1;
	node *temp;
	printf("%d NODE -> left: %p, win: %d, lose: %d right: %p \n", m,
		   plist->head->left, plist->head->win, plist->head->lose, plist->head->right);

	for (temp = plist->head->right; temp != plist->head; temp = temp->right)
	{

		m++;
		printf("%d NODE -> left: %p, win: %d, lose: %d right: %p \n", m,
			   temp->left, temp->win, temp->lose, temp->right);
	}

	printf("\n");
	printf("%d NODEAddress = %p\n", i, plist->head);

	for (temp = plist->head->right; temp != plist->head; temp = temp->right)
	{

		i++;
		printf("%d NODEAddress = %p\n", i, temp);
	}
}

int main(int argc, char *argv[])
{

	int a = atoi(*(argv + 1));
	int userPick = 0;
	int computerPick = 0;
	List *plist = (List *)malloc(sizeof(List));
	InitList(plist, a);
	plist->computer_ptr = plist->head;
	printList(plist);
	srand((unsigned)time(NULL));

	while (1)
	{

		printf("\n>Please select a number. (1.Scissors 2.Rock 3.Paper 4. Exit) ");
		printf("? ");
		scanf("%d", &userPick);
		computerPick = 1 + rand() % 3;

		if (userPick == 4)
		{
			printList(plist);
			break;
		}

		else if (computerPick == userPick + 1 || computerPick == userPick - 2)
		{
 printf("Result : Computer win. The computer will move to the right node.\n");
 win(plist);
 printList(plist);
		}

		else if (computerPick == userPick - 1 || computerPick == userPick + 2)
		{
 printf("Result: Computer lose. The computer will move to the left node.\n");
 lose(plist);
 printList(plist);
		}

		else
		{
			printf("Result: Draw! Play the game again.\n");
			printList(plist);
		}
	}

	free(plist);

	return 0;
}
