#ifndef CLIST_H_
#define CLIST_H_

struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
};

struct intrusive_list {
  struct intrusive_node *head;
  struct intrusive_node *tail;
};

void init_list(struct intrusive_list *list);
void add_node(struct intrusive_list *list, struct intrusive_node *node);
void remove_node(struct intrusive_list *list, struct intrusive_node *node);
void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data);

#endif