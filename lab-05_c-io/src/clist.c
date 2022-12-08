#include <stddef.h>
#include <stdlib.h>
#include "clist.h"

void init_list(struct intrusive_list *l) {
	l->head = malloc(sizeof(struct intrusive_node));
	l->head->next = NULL;
	l->head->prev = NULL;
}

void deinit_list(struct intrusive_list *l) {
	free(l->head);
    free(l);
}

void add_node(struct intrusive_list *l, struct intrusive_node *v) {
	struct intrusive_node *u = l->head->next;
	if (u != NULL) u->prev = v;
	v->next = u;
	v->prev = l->head;
	l->head->next = v;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *v) {
	if (v == l->head) return;
	if (v->next != NULL) v->next->prev = v->prev;
    if (v->prev != NULL) v->prev->next = v->next;
}

int get_length(struct intrusive_list *l) {
	int ans = 0;
	struct intrusive_node *v = l->head->next;
	while (v != NULL) {
		ans++;
		v = v->next;
	}
	return ans;
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