#include "../include/clist.h"

#include <stdlib.h>


void init_list(struct intrusive_list *list){
    list->head = (struct intrusive_node*) malloc(sizeof(struct intrusive_node));
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = list->head;
}


void add_node(struct intrusive_list *list, struct intrusive_node *node){
    struct intrusive_node *last_element = list->tail;
    last_element->next = node;
    list->tail = node;
    node->prev = last_element;
    node->next = NULL;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node){
    if (node == list->head){
        return;
    }

    struct intrusive_node *node_next = node->next;
    struct intrusive_node *node_prev = node->prev;
    if (node_next != NULL){
        node_next->prev = node_prev;
    }
    if (node_prev != NULL){
        node_prev->next = node_next;
    }
}

void apply(struct intrusive_list *list, void(*op)(struct intrusive_node *node, void *data), void *data){
    struct intrusive_node *it_node = list->head->next;
    while (it_node != NULL){
        op(it_node, data);
        it_node = it_node->next;
    }
}