#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"

typedef struct node
{
    student data;
    struct node* next;
} node;

void init(node **head);

void addBegin(node *head, student s);

void addEnd(node **head, student s);

#endif
