#include <stdio.h>
#include <stdlib.h>
#include "llist.h"


int list_init(struct list_head *list)
{
    if (list == NULL)
    {
        printf("Input parameter null.\n");
        return -1;
    }

    list->next = list;
    list->prev = list;
    list->data = 0;

    return 0;
}


int list_add_tail(struct list_head *head, int data)
{
    struct list_head *ptr_new = (struct list_head *)malloc(sizeof(struct list_head));

    if (ptr_new == NULL)
    {
        perror("malloc");
        return -1;
    }
    ptr_new->data = data;

    if (head == NULL)
    {
        printf("Input parameter null.\n");
        return -1;
    }

    struct list_head *prev = head->prev;

    ptr_new->next = head;
    head->prev = ptr_new;
    prev->next = ptr_new;
    ptr_new->prev = prev;

    return 0;
}


int list_del(struct list_head *entry)
{
    if (entry == NULL)
    {
        printf("Input parameter null.\n");
        return -1;
    }

    struct list_head *prev = entry->prev;
    struct list_head *next = entry->next;

    prev->next = next;
    next->prev = prev;
    free(entry);

    return 0;
}


int list_empty(struct list_head *head)
{
    if (head == NULL)
    {
        printf("Input parameter null.\n");
        return -1;
    }

    return (head->next == head);
}
