#ifndef CLIST_H
#define CLIST_H

typedef struct CListElmt_
{
    void *data;
    CListElmt_ *next;
}CListElmt;

typedef struct CList_
{
    int   size;
    int   (*match)(const void* key1, const void *key2);
    void  (*destory)(void* data);
    CListElmt *head;
}CList;

/* interface */
void clist_init(CList *clist, void (*destroy)(void *data));
void clist_destory(CList *clist);
int  clist_ins_next(CList *clist, CListElmt *element, const void *data);
int  clist_rem_next(CList *clist, CListElmt *element, void **data);

#define clist_size(clist) ((clist)->size)
#define clist_head(clist) ((clist)->head)
#define clist_is_head(clist, element) ((element) == (clist)->head ? 1:0)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif