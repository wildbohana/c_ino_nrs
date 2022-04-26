#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct node {
    int data;
    struct node *next;
} node;

void init(node **l);

void addBegin(node *l, int s);

void addEnd(node **l, int s);

#endif
