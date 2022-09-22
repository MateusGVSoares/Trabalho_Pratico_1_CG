#ifndef __LIST__
#define __LIST__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node
{
    void *content;
    struct node *next;
} node_t;

typedef struct stack
{
    size_t size;
    node_t *head;
} list_t;

list_t *genList(size_t size);

int getSize(list_t *target);

int peek(list_t *target, int pos, void **ret);

int pop(list_t *target, void **ret);

void push(list_t *target, void *val);

int isEmpty(list_t *target);

#endif