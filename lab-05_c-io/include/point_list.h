#pragma once
#include "clist.h"

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *l, int x, int y);
void remove_all_points(struct intrusive_list *l);