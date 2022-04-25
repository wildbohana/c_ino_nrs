#include "list.h"
#include <stdlib.h>

// inicijalizacija
void init(node **l)
{
	*l = (node*) malloc(sizeof(node));
	(*l)->next = *l;
};

// dodavanje na pocetak
void addBegin(node *l, student s)
{
	node *temp = (node*) malloc(sizeof(node));
	temp->data = s;
	temp->next = l->next;
	l->next = temp;
};

// dodavanje na kraj - dodajemo podatak u granicnik
void addEnd(node **l, student s)
{
	node *temp = (node*) malloc(sizeof(node));
	(*l)->data = s;
	temp->next = (*l)->next;
	(*l)->next = temp;
	*l = temp;
};

