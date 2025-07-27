#include "../include/point_list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int convert(int x){
    if( x & 0x00800000 )
        return x | 0xff000000;
    return x;
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
    unsigned char bytes[3];
    int x,y;
    while (!feof(infile)){
        if (fread(bytes, 1, 3, infile) == 0){
            break;
        }
        x = (bytes[0] << 16) | (bytes[1] << 8) | bytes[2];
        if (fread(bytes, 1, 3, infile) == 0){
            break;
        }
        y = (bytes[0] << 16) | (bytes[1] << 8) | bytes[2];
        // fread(&x, kBIN_BYTE, 1, infile);
        // fread(&y, kBIN_BYTE, 1, infile);
        x = convert(x);
        y = convert(y);
        printf("%d %d\n", x, y);
        fflush(stdout);
        add_point(list, x, y);
    }
    fclose(infile);
}

void savetext_node(struct intrusive_node *it_node, FILE *outfile){
    struct point *point = container_of(it_node, struct point, node);
    fprintf(outfile, "%d %d\n", point->x, point->y);
}

void write_3byte_int(FILE *file, int num) {
    unsigned char bytes[3];
    bytes[0] = (num >> 16) & 0xFF;
    bytes[1] = (num >> 8)  & 0xFF;
    bytes[2] = num & 0xFF;
    fwrite(bytes, 1, 3, file);
}

void savebin_node(struct intrusive_node *it_node, FILE *outfile){
	struct point* point = container_of(it_node, struct point, node);

    write_3byte_int(outfile, point->x);
    write_3byte_int(outfile, point->y);
    // fwrite(&(point->x), kBIN_BYTE, 1, outfile);
	// fwrite(&(point->y), kBIN_BYTE, 1, outfile);
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
        savetext_node(it_node, outfile);
        it_node = it_node->next;
    }
    fclose(outfile);
}

void savebin(struct intrusive_list *list, char *name_file){
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
    }
    fclose(outfile);
}

int main(int argc, char *argv[]){
    if (argc < 4){
        printf("Invalida input data.");
        fflush(stdout);
        return 0;
    }
    struct intrusive_list *list = (struct intrusive_list*) malloc(sizeof(struct intrusive_list));
    init_list(list);
    if (strcmp(argv[1], "loadtext") == 0){
        loadtext(list, argv[2]);
    } else if (strcmp(argv[1], "loadbin") == 0){
        loadbin(list, argv[2]);
    } else {
        printf("Invalid parametr.\n");
        fflush(stdout);
        return 0;
    }

    if (strcmp(argv[3], "savetext") == 0){
        savetext(list, argv[4]);
    } else if (strcmp(argv[3], "savebin") == 0){
        savebin(list, argv[4]);
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