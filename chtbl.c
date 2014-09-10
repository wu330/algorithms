/* chtbl.c */

#include <string.h>
#include "chtbl.h"

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), 
               int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    int nbktidx;
    
    if( NULL == (htbl->table = (List*)malloc(buckets*sizeof(List))) ) return -1;
    
    htbl->buckets = buckets;
    htbl->h       = h;
    htbl->match   = match;
    htbl->destroy = destroy;
    htbl->size    = 0;
    
    for( nbktidx=0; nbktidx<buckets; nbktidx++ )
        list_init(&htbl->table[i], destroy);
        
    return 0;
}
               
void chtbl_destory(CHTbl *htbl)
{
    int nbktidx;
    
    for( nbktidx=0; nbktidx<htbl->buckets; nbktidx++)
        list_destory(&htbl->table[i]);
    
    free(htbl->table);
    
    memset(htbl, 0, sizeof(CHTbl));
    
    return;
}


int  chtbl_insert(CHTbl *htbl, const void *data)
{
    void *temp;
    int  bucket, retval;
    
    temp = (void*)data;
    
    if( 0 == chtbl_loopup(htbl, &temp) )
        return 0;
    
    bucket = htbl->h(data)%buckets;
    
    if( (retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;
    
    return retval;
}


int  chtbl_remove(CHTbl *htbl, void **data)
{
    ListElmt *element,
             *prev;
    int      bucket;
    
    /* Hash */
    bucket = htbl->h(data)%buckets;
    
    /* search from bucket */
    prev   = NULL;
    for(element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element))
    {
        if( htbl->match(*data, list_data(element)) )
           break;
        
        prev = element;
    }
    
    /* remove from bucket */
    if( (element == NULL) 
        &&0 != list_rem_next(&htbl->table[bucket], prev, data)) return -1;
    
    htbl->size--;
    return 0;
}


int  chtbl_loopup(const CHTbl *htbl, void **data)
{
    ListElmt *element;
    int      bucket;
    
    /* Hash */
    bucket = htbl->h(data)%buckets;
    
    /* search from bucket */
    for(element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element))
    {
        if( htbl->match(*data, list_data(element)) )
           break;
    }
    
    /* remove from bucket */
    if(element == NULL) return -1;
    
    return 0;
}

