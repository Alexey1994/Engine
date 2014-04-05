#include "List.h"
#include <stdlib.h>

Data get_list(List *list)
{
    struct Node *cur=list->begin;
    int i;

    for(i=0; i<list->size; i++)
        cur=cur->next;

    return cur->data;
}

void clear_list(List *list)
{
    int i;
    struct Node *t=list->begin;

    for(i=0; i<list->size; i++)
    {
        t=t->next;
        free(list->begin);
        list->begin=t;
    }
    free(list->begin);
    list->size=0;
}

void insert_list(List *list, Data data, int pos)
{
    int i;
    struct Node *cur=list->begin, *ins;

    ins=malloc(sizeof(struct Node));
    ins->data=data;

    if(list->begin==0)
    {
        list->begin=ins;
        list->size++;

        return;
    }

    if(pos==0)
    {
        ins->next=list->begin;
        list->begin=ins;
        list->size++;

        return;
    }

    for(i=0; i<pos-1; i++)
        cur=cur->next;

    ins->next=cur->next;
    cur->next=ins;

    list->size++;

    return;
}

void delete_list(List *list, int pos)
{
    struct Node *del=list->begin, *cur;
    int i;

    if(pos==0)
    {
        cur=list->begin->next;
        free(list->begin);
        list->begin=cur;
        list->size--;

        return;
    }

    cur=list->begin;
    for(i=0; i<pos-1; i++)
        cur=cur->next;

    del=cur->next;
    cur->next=del->next;
    free(del);

    list->size--;

    return;
}

void get_array(List *list, Data *arr)
{
    struct Node *cur=list->begin;
    int i;

    for(i=0; i<list->size; i++)
    {
        arr[i]=cur->data;
        cur=cur->next;
    }
}
