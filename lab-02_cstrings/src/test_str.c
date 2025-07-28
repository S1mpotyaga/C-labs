#include "test_str.h"
#include "str.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

void test_strcpy(){
	char a[] = "Hello", b[] = "aba", c[] = "";
	char a_cpy[10] = "",  b_cpy[10] = "acd", c_cpy[10] = "a";
	assert(strcmp(my_strcpy(a_cpy, a), strcpy(a_cpy, a)));
	assert(strcmp(my_strcpy(b_cpy, b), strcpy(b_cpy, b)));
	assert(strcmp(my_strcpy(c_cpy, c), strcpy(c_cpy, c)));
}

void test_strcat(){
	char a[] = "Hello", b[] = "", c[] = "me";
	char a_tmp[] = "!", b_tmp[] = "Hello!", c_tmp[] = ":)";
	char check1[] = "Hello!", check2[] = "me:)";
	assert(strcmp(my_strcat(a, a_tmp), check1) == 0);
	assert(strcmp(my_strcat(b, b_tmp), check1) == 0);
	assert(strcmp(my_strcat(c, c_tmp), check2) == 0);
}

bool check(int a, int b){
	if (a == 0 && b == 0)
		return true;
	return a * b * 1ll > 0;
}

void test_strcmp(){
	char a[] = "aba", b[] = "ajfgkerngjea", c[] = "";
	assert(check(my_strcmp(a, b), strcmp(a, b)));
	assert(check(my_strcmp(a, c), strcmp(a, c)));
	assert(check(my_strcmp(b, c), strcmp(b, c)));
}

void test_strlen(){
	char a[] = "ajbsdfjkne", b[] = "", c[] = "\n";
	assert(my_strlen(a) == strlen(a));
	assert(my_strlen(b) == strlen(b));
	assert(my_strlen(c) == strlen(c));
}                         
