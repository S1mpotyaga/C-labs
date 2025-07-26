#include "../include/point_list.h"

#include <stdio.h>
#include <string.h>

const int kBIN_BYTE = 3;
const int kTEXT_BYTE = 10;

void print_element(struct intrusive_node *it_node, void *data){
    if (it_node == NULL){
        return;
    }
    struct point *point = container_of(it_node, struct point, node);
    char *format = (char*) data;
    printf(format, point->x, point->y);
    fflush(stdout);
}

void count(struct intrusive_node *it_node, void *data){
    if (it_node == NULL){
        return;
    }
    int *it_count = (int*) data;
    int count = *it_count;
    count++;
}

void loadtext(struct intrusive_list *list, char *path){
    FILE *infile = fopen(path, "r");
    if (infile == NULL){
        printf("Failed to open file.\n");
        fflush(stdout);
        return;
    }
    int x, y;
    while (fscanf(infile,"%d %d", &x, &y) != EOF){
        add_point(list, x, y);
    }
    fclose(infile);
}

void loadbin(struct intrusive_list *list, char *path){
    FILE *infile = fopen(path, "rb");
    if (infile == NULL){
        printf("Failed to open file.\n");
        fflush(stdout);
        return;
    }
    int x,y;
    while (!feof(infile)){
        fread(&x, kBIN_BYTE, 1, infile);
        fread(&y, kBIN_BYTE, 1, infile);
        add_point(list, x, y);
    }
}

void savetext_node(struct intrusive_node *it_node, FILE *outfile){
    struct point *point = container_of(it_node, struct point, node);
    fprintf(outfile, "%d %d", point->x, point->y);
}

void savebin_node(struct intrusive_node *it_node, FILE *outfile){
	struct point* point = container_of(v, struct point, node);
	fwrite(&(point->x), kBIN_BYTE, 1, outfile);
	fwrite(&(point->y), kBIN_BYTE, 1, outfile);
}

void savetext(struct intrusive_list *list, char *name_file){
    FILE *outfile = fopen(name_file, "w");
    if (outfile == NULL){
        printf("Failed to open file.");
        fflush(stdout);
        return;
    }
    struct intrusive_node *it_node = list->head->next;
    while (it_node != NULL){
        savetext_node(it_node);
        it_node = it_node->next;
    }
    fclose(outfile);
}

void savebin(char *name_file){
    FILE *outfile = fopen(name_file, "wb");
    if (outfile == NULL){
        printf("Failed to open file.");
        fflush(stdout);
        return;
    }
    struct intrusive_node *it_node = list->head->next;
    while (it_node != NULL){
        savebin_node(it_node, outfile);
        it_node = it_node->next;
        free(point);
    }
    fclose(outfile);
}

int main(int argc, char *argv[]){
    struct intrusive_list *list = malloc(sizeof(intrusive_node));
    init_list(list);
    if (strcmp(argv[1], "loadtext") == 0){
        loadtext(list, argv[2]);
    } else if (strcmp(argv[1], "loadbin" == 0)){
        loadbin(list, argv[2]);
    } else {
        printf("Invalid parametr.\n");
        fflush(stdout);
        return 0;
    }

    if (strcmp(argv[3], "savetext") == 0){
        savetext(argv[4]);
    } else if (strcmp(argv[3], "savebin") == 0){
        savebin(argv[4]);
    } else if (strcmp(argv[3], "print") == 0){
        apply(list, print_element, argv[4]);
    } else if (strcmp(argv[3], "count") == 0){
        int len = 0;
        apply(list, count, &len);
        printf("%d\n", len);
        fflush(stdout);
    }
    deinit_list(list);
    return 0;
}