#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"

typedef struct node {
    student data;
    struct node *next;
} node;

void init(node **l);

void addBegin(node *l, student s);

void addEnd(node **l, student s);

#endif
