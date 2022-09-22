#include "list.h"

// Verifica se a stack está vazia
int isEmpty(list_t *target)
{
    return !(target->head == NULL);
}

void push(list_t *target, void *val)
{
    node_t *atual = target->head;

    target->head = malloc(sizeof(node_t));
    target->head->next = atual;

    atual = target->head;
    atual->content = malloc(sizeof(target->size));

    memcpy(atual->content, val, sizeof(target->size));
}

int pop(list_t *target, void **ret)
{

    node_t *atual = target->head;

    // Verifica se a stack n estava vazia

    if (atual != NULL)
    {
        *ret = malloc(sizeof(target->size));
        memcpy(*ret, atual->content, target->size);
        target->head = atual->next;
        free(atual);
        return 0;
    }
    else
    {
        return 1;
    }
}

int peek(list_t *target, int pos, void **ret)
{
    node_t *atual = target->head;
    int i = 0;
    for (; i < pos && atual != NULL; i++)
    {
        atual = atual->next;
    }

    if (i == pos && atual != NULL)
    {
        *ret = malloc(target->size);
        memcpy(*ret, atual->content, target->size);
        return 0;
    }
    else
        return 1;
}

int getSize(list_t *target)
{
    int i = 0;
    node_t *atual = target->head;
    for (; atual != NULL; i++)
        atual = atual->next;
    return i;
}

list_t *genList(size_t size)
{
    list_t *ret = malloc(sizeof(list_t));
    ret->head = NULL;
    ret->size = size;
    return ret;
}