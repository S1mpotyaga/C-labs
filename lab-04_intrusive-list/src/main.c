#include "clist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct point {
    int x, y;
    struct intrusive_node node;
};

void myFree(struct point* p) {
    // printf("free of point %d %d\n", p->x, p->y);
    free(p);
}

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
            if (v->next != NULL) v->next->prev = v->prev;
            if (v->prev != NULL) v->prev->next = v->next;
            myFree(p);
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
        if (v->next != NULL) v->next->prev = v->prev;
        if (v->prev != NULL) v->prev->next = v->next;
        myFree(p);
        v = u;
    }
}

int main() {
    
    const size_t MAXT = 10;
    char type[MAXT];

    char c;
    size_t szType = 0;
    int x, y;
    struct intrusive_list *l = malloc(sizeof(struct intrusive_list));
    init_list(l);

    while (1) {
        szType = 0;
        while (1) {
            c = getchar();
            if (c == ' ' || c == '\n' || szType == MAXT - 1) {
                type[szType++] = '\0';
                break;
            }
            type[szType++] = c;
        }
        if (strcmp(type, "add") == 0) {
            scanf("%d %d\n", &x, &y);
            add_point(l, x, y);
        } else if (strcmp(type, "rm") == 0) {
            scanf("%d %d\n", &x, &y);
            remove_point(l, x, y);
        } else if (strcmp(type, "print") == 0) {
            show_all_points(l);
        } else if (strcmp(type, "rma") == 0) {
            remove_all_points(l);
        } else if(strcmp(type, "len") == 0) {
            printf("%d\n", get_length(l));
        } else if (strcmp(type, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
    }
    remove_all_points(l);
    free(l->head);
    free(l);

    return 0;
}
