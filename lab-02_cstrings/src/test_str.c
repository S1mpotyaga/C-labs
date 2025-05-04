#include "test_str.h"
#include "str.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

void test_strcpy(){
	char a[] = "Hello";
	char b[] = "aba";
	char c[] = "";
	char a_cpy[10] = "";
	char b_cpy[10] = "acd";
	char c_cpy[10] = "a";
	assert(strcmp(my_strcpy(a_cpy, a), a) == 0);
	assert(strcmp(my_strcpy(b_cpy, b), b) == 0);
	assert(strcmp(my_strcpy(c_cpy, c), c) == 0);
}

void test_strcat(){
	char a[] = "Hello";
	char b[] = "";
	char c[] = "me";
	char d[] = "";
	char a_tmp[] = "!";
	char b_tmp[] = "Hello!";
	char c_tmp[] = ":)";
	char d_tmp[] = "";
	char check1[] = "Hello!";
	char check2[] = "me:)";
	char check3[] = "";
	assert(strcmp(my_strcat(a, a_tmp), check1) == 0);
	assert(strcmp(my_strcat(b, b_tmp), check1) == 0);
	assert(strcmp(my_strcat(c, c_tmp), check2) == 0);
	assert(strcmp(my_strcat(d, d_tmp), check3) == 0);
}


void test_strcmp(){
	char a[] = "aba";
	char b[] = "ajfgkerngjea";
	char c[] = "";
	assert(my_strcmp(a, b) == strcmp(a, b));
	assert(my_strcmp(a, c) == strcmp(a, c));
	assert(my_strcmp(b, c) == strcmp(b, c));
}

void test_strlen(){
	char a[] = "ajbsdfjkne";
	char b[] = "";
	char c[] = "\n";
	assert(my_strlen(a) == strlen(a));
	assert(my_strlen(b) == strlen(b));
	assert(my_strlen(c) == strlen(c));
}