#include <stdlib.h>
#include <string.h>

#include "clist.h"

void clist_init(CList *clist, void (*destroy)(void *data))
{
    clist->size = 0;
    clist->head = NULL;
    clist->destory = destory;
    
    return;
}


void clist_destory(CList *clist);
{
    void *data;
    while(clist_size(clist)>0)
    {
        if( (clist_rem_next(clist, NULL, (void**)&data) == 0) && (clist->destory != NULL) )
            clist->destory( (void*)data );
    }
    
    memset(clist, 0, sizeof(CList));
    
    return;
}

int  clist_ins_next(CList *clist, CListElmt *element, const void *data)
{
    CListElmt *new_elmt;
    
    if( NULL == (new_elmt = (CListElmt*)malloc(sizeof(CListElmt))))
        return -1;
        
    new_elmt->data = (void*)data;
    
    if( clist_size(clist) == 0 )
    {
        new_elmt->next = new_elmt;
        clist->head    = new_elmt;
    }
    else
    {
        new_elmt->next = element->next;
        element->next  = new_elmt; 
    }
    
    list->size++;
    
    return 0;
}


int  clist_rem_next(CList *clist, CListElmt *element, void **data)
{
    CListElmt *old_elmt;
    
    if(clist_size(clist) == 0)
        return -1;
        
    *data = element->next->data;

    if(clist_size(clist) == 1)
    {
        old_elmt    = element->next;
        clist->head = NULL;
    }
    else
    {
        old_elmt    = element->next;
        element->next = old_elmt->next;
        if( old_elmt == clist_head(clist) )
            clist->head = old_elmt->next;
    }
    
    free(old_elmt);    
    
    clist->size--;
    return 0;
}
















