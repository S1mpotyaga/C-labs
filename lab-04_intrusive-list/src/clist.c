#include <stddef.h>
#include <stdlib.h>
#include "clist.h"

void init_list(struct intrusive_list *l) {
	l->head = malloc(sizeof(struct intrusive_node));
	l->head->next = NULL;
	l->head->prev = NULL;
}

void add_node(struct intrusive_list *l, struct intrusive_node *v) {
	struct intrusive_node *u = l->head->next;
	if (u != NULL) u->prev = v;
	v->next = u;
	v->prev = l->head;
	l->head->next = v;
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