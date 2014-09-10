/* set.c */

#include <stdlib.h>
#include <string.h>
#include "set.h"

void set_init( Set *set, int (*match)(const void *key1, const void *key2), 
               void(*destory)(void *data))
{
    list_init(set, destory);
    set->match = match;
    
    return;
}

int set_insert(Set *set, const void *data)
{
    if( set_is_member(set, data) ) return 0;
    
    return list_ins_next(set, NULL, data);
}


int set_remove(Set *set, void **data)
{
    ListElmt *prev, *member;
    
    prev = NULL;
    
    /* Find the member to remove */
    for(member = list_head(set); member != NULL; member = list_next(member))
    {
        if( set->match(*data, list_data(member)) )
            break;
        
        prev = member;
    }
    
    if(member == NULL)
        return -1;
    
    /* remove data */
    return list_rem_next(set, prev, data);  
}


int set_union(Set *setu, const Set *set1, const Set *set2)
{
    ListElmt *member;
    
    /* Initial setu */
    set_init(setu, set1->match, set1->destory);
    
    for( member = list_head(set1); member != NULL; member = list_next(member) )
    {
        if( 0 != list_ins_next(setu, list_tail(setu), list_data(member)) )
        {
            set_destory(setu);
            return -1;
        }        
    }
    
    for( member = list_head(set2); member != NULL; member = list_next(member) )
    {
        if( set_is_member(setu, list_data(member)) ) continue;
        
        if( 0 != list_ins_next(setu, list_tail(setu), list_data(member)) )
        {
            set_destory(setu);
            return -1;
        }        
    }
    
    return 0;
}


int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElmt *member;
    
    /* Initial seti */
    set_init(seti, set1->match, set1->destory);
    
    for( member = list_head(set2); member != NULL; member = list_next(member) )
    {
        if( set_is_member(set1, list_data(member)) )
        {
            if( 0 != list_ins_next(seti, list_tail(seti), list_data(member)) )
            {
                set_destory(seti);
                return -1;
            }  
        }            
    }
    
    return 0;
}


int set_difference(Set *setd, const Set *set1, const Set *set2)
{
    ListElmt *member;
    
    /* Initial setd */
    set_init(setd, set1->match, set1->destory);
    
    for( member = list_head(set1); member != NULL; member = list_next(member) )
    {
        if( 0 != list_ins_next(setd, list_tail(setd), list_data(member)) )
        {
            set_destory(setd);
            return -1;
        }        
    }
    
    for( member = list_head(set2); member != NULL; member = list_next(member) )
    {
        if( set_is_member(setd, list_data(member)) ) 
        {
            set_remove(setd, list_data(member));
        }
        else
        {
            if( 0 != list_ins_next(setd, list_tail(setd), list_data(member)) )
            {
                set_destory(setd);
                return -1;
            }  
        }      
    }
    
    return 0;
}


int set_is_member(const Set *set, const void *data)
{
    ListElmt *member;
    
    for( member = list_head(set); member != NULL; member = list_next(member) )
    {
        if( set->match(data, list_data(member)) ) return 1; 
    }
    
    return 0;
}


int set_is_subset(const Set *set1, const Set *set2)
{
    ListElmt *member;
    
    /* quick test */
    if(set_size(set1) > set_size(set2)) return 0;
    
    /* whole test */
    for( member = list_head(set1); member != NULL; member = list_next(member) )
    {
        if( set_is_member(set2, list_data(member)) ) return 0; 
    }
    
    return 1;
}


int set_is_equal(const Set *set1, const Set *set2)
{
    ListElmt *member;
    
    if(set_size(set1) != set_size(set2)) return 0;
   
    return set_is_subset(set1, set2);
}