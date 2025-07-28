#include "test_str.h"
#include "str.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

void test_strcpy(){
	char Hello[] = "Hello";
	char empty_string_1[10] = "";
	assert(strcmp(my_strcpy(empty_string_1, Hello), Hello) == 0);

	char aba[] = "aba";
	char acd[10] = "acd";
	assert(strcmp(my_strcpy(acd, aba), aba) == 0);

	char empty_string_2[] = "";
	char test_string[10] = "a";
	assert(strcmp(my_strcpy(test_string, empty_string_2), empty_string_2) == 0);

    char* dst = malloc(10);
    const char src_1[] = "abcdefg";
    const char src_2[] = "hij";
    my_strcpy(dst, src_1);
    my_strcpy(dst, src_2);
    assert(strcmp(dst, src_2) == 0);
    // for (; *dst != '\0'; ++dst){
    //     printf(dst);
    // }
    // printf("\n");
    // fflush(stdout);
}

void test_strcat(){
	char Hello_1[] = "Hello";
	char exclamation_mark[] = "!";
	char result_string_1[] = "Hello!";
	assert(strcmp(my_strcat(Hello_1, exclamation_mark), result_string_1) == 0);
	
	char empty_string_1[] = "";
	char Hello_2[] = "Hello!";
	assert(strcmp(my_strcat(empty_string_1, Hello_2), result_string_1) == 0);
	
	char me[] = "me";
	char smile[] = ":)";
	char result_string_2[] = "me:)";
	assert(strcmp(my_strcat(me, smile), result_string_2) == 0);

	char empty_string_2[] = "";
	char empty_string_3[] = "";
	char result_string_3[] = "";
	assert(strcmp(my_strcat(empty_string_2, empty_string_3), result_string_3) == 0);
}


void test_strcmp(){
	char test_string_1[] = "aba";
	char test_string_2[] = "ajfgkerngjea";
	char empty_string[] = "";
	assert(my_strcmp(test_string_1, test_string_2) == strcmp(test_string_1, test_string_2));
	assert(my_strcmp(test_string_1, empty_string) == strcmp(test_string_1, empty_string));
	assert(my_strcmp(test_string_2, empty_string) == strcmp(test_string_2, empty_string));
}

void test_strlen(){
	char test_string[] = "ajbsdfjkne";
	assert(my_strlen(test_string) == strlen(test_string));

	char empty_string[] = "";
	assert(my_strlen(empty_string) == strlen(empty_string));

	char new_line[] = "\n";
	assert(my_strlen(new_line) == strlen(new_line));
}