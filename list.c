#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{	
	char d;
	char *arr;
	struct Node* next;
} node;


typedef struct List{
	int length;
	node* head;
	node* last;
} list;	


void insertChar(char d,list* l){
	node* new = (node*)malloc(sizeof(node));

	new->d = d;
	new->next = NULL;
	if(l->head!=NULL){
		l->last->next = new;
		l->last = new;
		l->length++;
	}
	else if(l->head==NULL){
		l->length=1;
		l->head = new;
		l->last = new;

	}

}


