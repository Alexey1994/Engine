#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef char Data;

struct Node
{
  Data data;
  struct Node *next;
};

typedef struct
{
    int size;
    struct Node *begin;
}List;

void delete_list(List *list, int pos);
void insert_list(List *list, Data data, int pos);
void clear_list(List *list);
Data get_list(List *list);
void get_array(List *list, Data *arr);

#endif
