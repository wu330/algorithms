#ifndef DLIST_H
#define DLIST_H

#include<stdlib.h>
typedef struct DListElmt_
{
    void   *data;
    struct DListElmt_ *prev;
    struct DListElmt_ *next;
}DListElmt;

typedef struct DList_
{
    int    size;
    int    (*match)(const void *key1, const void *key2);
    void   (*destory)(void *data);
    DListElmt *head;
    DListElmt *tail;
}DList;

/* interface */
void dlist_int(DList *dlist, void (*destory)(void *data));
void dlist_destory(DList *dlist);
int  dlist_ins_next(DList *dlist, DListElmt *element, const void *data);
int  dlist_ins_prev(DList *dlist, DListElmt *element, const void *data);
int  dlist_remove(DList *dlist, DListElmt *element, void **data);

#define dlist_size(dlist)  ((dlist)->size)
#define dlist_head(dlist)  ((dlist)->head)
#define dlist_tail(dlist)  ((dlist)->tail)
#define dlist_is_head(element)  (((element)->prev == NULL)?1:0)
#define dlist_is_tail(element)  (((element)->tail == NULL)?1:0)
#define dlist_data(element)  ((element)->data)
#define dlist_prev(element)  ((element)->prev)
#define dlist_next(element)  ((element)->next)

#endif