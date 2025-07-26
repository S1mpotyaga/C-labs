#include "clist.h"

#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

struct point{
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y);

void remove_all_points(struct intrusive_list *list);

void deinit_list(struct intrusive_list *list);