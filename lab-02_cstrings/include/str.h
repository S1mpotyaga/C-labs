#pragma once

#include <stddef.h>

char* my_strcpy (char* restrict s_dest, const char* restrict s_from);

char* my_strcat(char* restrict s_dest, const char* restrict s_from);

int my_strcmp(const char* s, const char* t);

size_t my_strlen(const char* s);