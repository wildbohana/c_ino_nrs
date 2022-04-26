#include "list.h"
#include <stdlib.h>

// cvor l je granicnik u ovoj listi
// cvor l je prazan

void init(node **l)
{
    *l = (node*) malloc(sizeof(node));
    (*l) -> next = *l;  // sam na sebe pokazuje
}


void addBegin(node *l, student s)
{
    node* temp = (node*) malloc(sizeof(node));
    temp -> data = s;
    temp -> next = l -> next;
    l -> next = temp;   // pokazuje na novododati
}

void addEnd(node **l, student s)
{
    node* temp = (node*) malloc(sizeof(node));
    (*l) -> data = s;   // granicnik dobija podatke

    temp -> next = (*l) -> next;
    (*l) -> next = temp;

    *l = temp;          // novi granicnik je novododati
}
