#include "clist.h"
#include "point_list.h"
#include "stdio.h"
#include <stdlib.h>
#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

void add_point(struct intrusive_list *l, int x, int y) {
    struct point *p = malloc(sizeof(struct point));
    p->x = x;
    p->y = y;
    add_node(l, &p->node);
}

void remove_point(struct intrusive_list *l, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node *v = l->head->next;
    struct intrusive_node *u = NULL;
    while (v != NULL) {
        struct point *p = container_of(v, struct point, node);
        u = v->next;
        if (p->x == x && p->y == y) {
            remove_node(l, v);
            free(p);
        }
        v = u;
    }
}

void show_all_points(struct intrusive_list *l) {
    struct intrusive_node *v = l->head->next;
    struct point *p = NULL;
    while (v != NULL) {
        p = container_of(v, struct point, node);
        printf("(%d %d)", p->x, p->y);
        if (v->next != NULL) printf(" ");
        v = v->next;
    }
    printf("\n");
}

void remove_all_points(struct intrusive_list *l) {
    struct intrusive_node *v = l->head->next;
    struct intrusive_node *u = NULL;
    while (v != NULL) {
        struct point *p = container_of(v, struct point, node);
        u = v->next;
        remove_node(l, v);
        free(p);
        v = u;
    }
}
