#include <stddef.h>
#include <stdlib.h>
#include "clist.h"

void init_list(struct intrusive_list *l) {
	l->head = malloc(sizeof(struct intrusive_node));
	l->tail = l->head;
	l->head->next = NULL;
	l->head->prev = NULL;
}

void deinit_list(struct intrusive_list *l) {
	free(l->head);
}

void add_node(struct intrusive_list *l, struct intrusive_node *v) {
	struct intrusive_node *u = l->tail;
	u->next = v;
	v->prev = u;
	v->next = NULL;
	l->tail = v;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *v) {
	if (v == l->head) return;
	if (v == l->tail) l->tail = v->prev;
	if (v->next != NULL) v->next->prev = v->prev;
    if (v->prev != NULL) v->prev->next = v->next;
}

void apply(struct intrusive_list* l, void (*op)(struct intrusive_node* node, void* data), void* data) {
	struct intrusive_node* v = l->head->next;
	struct intrusive_node* u = NULL;
	while (v != NULL) {
		u = v->next;
		op(v, data);
		v = u;
	}
}