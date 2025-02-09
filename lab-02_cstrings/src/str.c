#include "str.h"

char *strcpy(char *dest, char *src){
	char *result = dest;
	for (; src != nullptr; src++){
		*dest = *src;
		dest++;
	}
	*dest = *src;
	return result;
}

char *strcat(char *dest, char *src){
}

int strcmp(char *lhs, char *rhs){

}

size_t strlen(char *str){

}