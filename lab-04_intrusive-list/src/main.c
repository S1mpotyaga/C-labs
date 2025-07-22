#include "./include/clist.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

struct point{
    int x, y;
    struct intrusive_node *node;
};

void add_point(struct intrusive_list *list, int x, int y){
    struct point *point = (struct point*) malloc(sizeof(struct point));
    point->x = x;
    point->y = y;
    add_node(list, &point->node);
}

bool point_equals(const struct point* a, int x, int y){
    return a->x == x && a->y == y;
}

void remove_point(struct intrusive_list *list, int x, int y){ // removes all (x, y) pairs
    struct intrusive_node *it_node = list->head->next;
    struct intrusive_node *tmp_next = NULL;
    while (it_node != NULL){
        struct point *point = container_of(it_node, struct point, node);
        tmp_next = it_node->next;
        if (point_equals(point, x, y)){
            remove_node(list, it_node);
        }
        it_node = tmp_next;
    }
}

void show_all_points(struct intrusive_list *list){
    struct intrusive_node *it_node = list->head->next;
    while (it_node != NULL){
        struct point *point = container_of(it_node, struct point, node);
        printf("(%d %d)", point->x, point->y);
        if (it_node->next != NULL){
            printf(" ");
        }
        it_node = it_node->next;
    }
}

void remove_all_points(struct intrusive_list *list){
    struct intrusive_node *it_node = list->head->next;
    list->head->next = NULL;
    struct intrusive_node *tmp_node = NULL;
    while (it_node != NULL){
        tmp_node = it_node->next;
        remove_node(list, it_node);
        it_node = tmp_node;
    }
}

void deinit_list(struct intrusive_list *list){
    remove_all_points(list);
    free(list->head);
    free(list);
}

const int kMAX_INPUT = 10;

int main(){
    char input[kMAX_INPUT];
    int input_x;
    int input_y;
    struct intrusive_list *list = malloc(sizeof(struct intrusive_list));
    while (true){
        scanf("%10s", input);
        if (strcmp(input, "add") == 0){
            scanf("%d %d\n", &input_x, &input_y);
            add_point(list, input_x, input_y);
        } else if (strcmp(input, "rm") == 0){
            scanf("%d %d\n", &input_x, &input_y);
            remove_point(list, input_x, input_y);
        } else if (strcmp(input, "print") == 0){
            show_all_points(list);
        } else if (strcmp(input, "rma") == 0){
            remove_all_points(list);
        } else if (strcmp(input, "len") == 0){
            int len = get_length(list);
            printf("%d\n", len);
        } else if (strcmp(input, "exit") == 0){
            break;
        } else{
            printf("Unknown command\n");
        }
    }
    deinit_list(list);
    return 0;
}