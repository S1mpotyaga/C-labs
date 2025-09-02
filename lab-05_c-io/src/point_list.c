#include "../include/point_list.h"

#include <stddef.h>
#include <stdlib.h>

void add_point(struct intrusive_list *list, int x, int y){
    struct point *point = (struct point*) malloc(sizeof(struct point));
    point->x = x;
    point->y = y;
    add_node(list, &point->node);
}

void remove_all_points(struct intrusive_list *list){
    struct intrusive_node *it_node = list->head->next;
    list->head->next = NULL;
    struct intrusive_node *tmp_node = NULL;
    while (it_node != NULL){
        struct point *p = container_of(it_node, struct point, node);
        tmp_node = it_node->next;
        remove_node(list, it_node);
        it_node = tmp_node;
        free(p);
    }
}

void deinit_list(struct intrusive_list *list){
    remove_all_points(list);
    free(list->head);
    free(list);
}