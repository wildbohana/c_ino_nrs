#include "list.h"
#include <stdlib.h>

void init(node **l){
	*l = (student*)malloc(sizeof(node));
	(*l)->next = *l;
};

void addBegin(node *l, student s){
	node *temp = (student*)malloc(sizeof(node));
	temp->data = s;
	temp->next = l->next;
	l->next = temp;
};

void addEnd(node **l, student s){
	node *temp = (student*) malloc(sizeof(node));
	// dodajemo podatak u granicnik
	(*l)->data = s;
	temp->next = (*l)->next;
	(*l)->next = temp;
	*l = temp;
};
