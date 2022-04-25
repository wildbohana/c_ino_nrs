#include "list.h"
#include <stdlib.h>

void init(node **l)
{
	*l = (node*) malloc(sizeof(node));
	(*l)->next = *l;
};

void addBegin(node *l, int s)
{
	node *temp = (node*) malloc(sizeof(node));
	temp->data = s;
	temp->next = l->next;
	l->next = temp;
};

void addEnd(node **l, int s)
{
	node *temp = (node*) malloc(sizeof(node));
	(*l)->data = s;
	temp->next = (*l)->next;
	(*l)->next = temp;
	*l = temp;
};
