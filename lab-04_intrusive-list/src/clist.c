#include "clist.h"

#include <stdlib.h>
// #include <stdio.h>


void init_list(struct intrusive_list *list){
    list->head = (struct intrusive_node*) malloc(sizeof(struct intrusive_node));
    list->head->prev = NULL;
    list->head->next = NULL;
}


void add_node(struct intrusive_list *list, struct intrusive_node *node){
    struct intrusive_node *list_head = list->head;
    struct intrusive_node *first_element = list_head->next;
    list_head->next = node;
    if (first_element != NULL){
        first_element->prev = node;
    }
    // printf("%p\n", (void*)node);
    // fflush(stdout);
    node->prev = list_head;
    node->next = first_element;
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

int get_length(struct intrusive_list *list){
    int result = 0;
    struct intrusive_node *current_node = list->head->next;
    while (current_node != NULL){
        // printf("%d\n", result);
        // fflush(stdout);
        current_node = current_node->next;
        result++;
    }
    return result;
}