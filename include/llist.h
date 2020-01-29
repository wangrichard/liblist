#ifndef __LLIST_H__
#define __LLIST_H__

#include <stdio.h>
#include <stdlib.h>


struct list_head
{
    int data;
    struct list_head *next;
    struct list_head *prev;
};


int list_init(struct list_head *list);
int list_add_tail(struct list_head *head, int data);
int list_del(struct list_head *entry);
int list_iterate(struct list_head *list);


#endif /* __LLIST_H__ */
