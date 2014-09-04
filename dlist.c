#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_int(DList *dlist, void (*destory)(void *data))
{
    dlist->head = NULL;
    dlist->tail = NULL;
    dlist->destory = destory;
    dlist->size = 0;
    
    return;
}

void dlist_destory(DList *dlist)
{
    while(dlist_size(dlist) > 0)
    {
        void *data;
        if( (0 == dlist_remove(dlist, NULL, (void**)&data)) && (dlist->destory != NULL) )
            dlist->destory(data);
    }
    
    memset(dlist, 0, sizeof(DList));
    return;
}

int  dlist_ins_next(DList *dlist, DListElmt *element, const void *data)
{
    DListElmt *new_elmt;
    
    /* Do not allow inset a NULL element unless the list is empty */
    if(NULL == element && dlist_size(dlist) != 0)
        return -1;
    
    if( NULL == (new_elmt = (DListElmt*)malloc(sizeof(DListElmt))))
        return -1;
        
    new_elmt->data = (void*)data;
    
    if( dlist_size(dlist) == 0)
    {
        new_elmt->prev = NULL;
        new_elmt->next = NULL;
        dlist->head = new_elmt;
        dlist->tail = new_elmt;
    }
    else
    {
        new_elmt->next = element->next;
        new_elmt->prev = element;
        
        if(NULL == element->next)
            dlist->tail = new_elmt;
        else 
            element->next->prev = new_elmt;
        
        element->next = new_elmt;
    }
    
    dlist->size++;
    
    return 0;
}


int  dlist_ins_prev(DList *dlist, DListElmt *element, const void *data)
{  
    DListElmt *new_elmt;
    
    /* Do not allow inset a NULL element unless the list is empty */
    if(NULL == element && dlist_size(dlist) != 0)
        return -1;
    
    if( NULL == (new_elmt = (DListElmt*)malloc(sizeof(DListElmt))))
        return -1;
        
    new_elmt->data = (void*)data;
    
    if( dlist_size(dlist) == 0)
    {
        new_elmt->prev = NULL;
        new_elmt->next = NULL;
        dlist->head = new_elmt;
        dlist->tail = new_elmt;
    }
    else
    {
        new_elmt->next = element;
        new_elmt->prev = element->prev;
        
        if(NULL == element->prev)
            dlist->head = new_elmt;
        else 
            element->prev->next = new_elmt;
        
        element->prev = new_elmt;
    }
    
    dlist->size++;
    
    return 0;
}


int  dlist_remove(DList *dlist, DListElmt *element, void **data)
{
    if(NULL == element || dlist_size(dlist) != 0)
        return -1;
    
    *data = element->data;
    
    if( dlist_is_head(element) )
    {
        dlist->head = element->next;
        
        if(dlist->head == NULL)
            dlist->tail = NULL;
        else
            element->next->prev = NULL;
    }
    else
    {
        element->prev->next = element->next;
        if(element->next == NULL)
            dlist->tail = NULL;
        else     
            element->next->prev = element->prev;
    }
    
    free(element);
    
    dlist->size--;
    
    return 0;
}





























