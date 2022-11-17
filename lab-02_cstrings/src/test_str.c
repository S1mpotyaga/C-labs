#include "test_str.h"
#include "str.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void test_strcpy() {
	char a[] = "abacaba", b[10];
	my_strcpy(b, a);
	assert(strcmp(b, a) == 0);

	char a1[] = "";
	char b1[] = "asdasd";
	my_strcpy(b1, a1);
	assert(strcmp(b1, a1) == 0);	
}

void test_strcat() {
	char a[100] = "abacaba", b[] = "cad";
	char a1[100] = "abacaba", b1[] = "cad";
	
	strcat(a, b);
	my_strcat(a1, b1);
	assert(strcpy(a, a1));
}

int check(int a, int b) {
	if (a == 0) return a == b;
	return a * b > 0;
}

void test_strcmp() {
	char a[] = "abacaba", b[] = "abacaba";
	char c[] = "abadaba", d[] = "aba";

	assert(check(my_strcmp(a, b), strcmp(a, b)));
	assert(check(my_strcmp(a, c), strcmp(a, c)));
	assert(check(my_strcmp(a, d), strcmp(a, d)));
	assert(check(my_strcmp(b, a), strcmp(b, a)));
	assert(check(my_strcmp(b, c), strcmp(b, c)));
	assert(check(my_strcmp(b, d), strcmp(b, d)));
	assert(check(my_strcmp(c, a), strcmp(c, a)));
	assert(check(my_strcmp(c, b), strcmp(c, b)));
	assert(check(my_strcmp(c, d), strcmp(c, d)));
	assert(check(my_strcmp(d, a), strcmp(d, a)));
	assert(check(my_strcmp(d, b), strcmp(d, b)));
	assert(check(my_strcmp(d, c), strcmp(d, c)));
}

void test_strlen() {
	char a[] = "", b[] = "abacaba", c[] = "a", d[] = "asdfghj";
	assert(my_strlen(a) == strlen(a));
	assert(my_strlen(b) == strlen(b));
	assert(my_strlen(c) == strlen(c));
	assert(my_strlen(d) == strlen(d));
}

