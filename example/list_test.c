#include <stdio.h>
#include <stdlib.h>
#include "llist.h"


int main()
{
    int i;

    struct list_head list;
    struct list_head *ptr_cur;

    list_init(&list);

    for (i=0; i<10; i++)
    {
        list_add_tail(&list, i);
    }
    ptr_cur = list.next;
    while (ptr_cur != &list)
    {
        printf("Node data: %d\n", ptr_cur->data);
        ptr_cur = ptr_cur->next;
    }


    ptr_cur = list.next;
    while (ptr_cur != &list)
    {
        list_del(ptr_cur);
        ptr_cur = ptr_cur->next;
    }

    ptr_cur = list.next;
    while (ptr_cur != &list)
    {
        printf("Node data: %d\n", ptr_cur->data);
        ptr_cur = ptr_cur->next;
    }

    return 0;
}

