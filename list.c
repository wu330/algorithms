#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size    = 0;
    list->destroy = destroy;
    list->head    = NULL;
    list->tail    = NULL;
	
    return;
}

void list_destory(List *list)
{
    void *data;
	
    while(list_size(list) > 0)
    {
        if( (list_rem_next(list, NULL, void **(&data)) == 0) && (list->destroy != NULL) )
	{
            list->destory(data);
	}
    }
	
    memset(list, 0, sizeof(List));
    return;
}

int  list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt* new_elmt;
	
	if( (new_elmt = malloc(sizeof(ListElmt))) == NULL )
	    return -1;
		
	new_elmt->data = (void*)data;
	
	/* Insert new element into the list */
	if(NULL == element) /* insert at head */
	{
	    if( 0 == list_size(list) )
		    list->tail = new_elmt;
			
		new_elmt->next = list->head;
		list->head     = new_elmt;
	}
	else /* Insert other than at the head */
	{
	    if(NULL == element->next)
		    list->tail = new_elmt;
		
		new_elmt->next = element->next;
		element->next = new_elmt;
	}
	
	list->size++;
	
	return 0;	
}

int  list_rem_next(List* list, ListElmt *element, void **data)
{
    ListElmt* old_elmt;
    
    if( 0 == list_size(list) ) return -1;    
    
    if(NULL == element) /* head */
	{
	    *data = list->head->data;
        old_elmt = list->head;
        list->head = list->head->next;
        
        if( 1 == list_size(list) )
            list->tail = NULL;
	}
	else /* other than the head */
	{
	    if(NULL == element->next) return -1;
        
        *data    = element->next->data;
        old_elmt = element->next;
        element->next = element->next->next;
        
        if( NULL == element->next )
            list->tail = element;
	}
    
    free(old_elmt);
    
    list->size--;
    
	return 0;
}
