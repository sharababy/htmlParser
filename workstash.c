#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.c"

int main(){
	
	list l1,l2;

	insertChar('a',&l1);
	insertChar('b',&l1);
	insertChar('c',&l1);
	insertChar('d',&l1);
	insertChar('e',&l1);

	insertChar('a',&l2);
	insertChar('b',&l2);
	insertChar('c',&l2);
	insertChar('d',&l2);

	bool result = listCompare(l1,l2);

	printf("%d\n", result);

	return 0;
}