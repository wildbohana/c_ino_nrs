#include "list.h"
#include <stdlib.h>

void init(node **head)
{
    *head = (node*) malloc(sizeof(node));
    (*head) -> next = *head;
}

void addBegin(node* head, student s)
{
    node* temp = (node*) malloc(sizeof(node));

    temp -> data = s;
    temp -> next = head -> next;
    head -> next = temp;
}

void addEnd(node **head, student s)
{
    node* temp = (node*) malloc(sizeof(node));

    (*head) -> data = s;
    temp -> next = (*head) -> next;
    (*head) -> next = temp;
    *head = temp;
}
