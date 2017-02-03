#include <stdlib.h>
#include <stdbool.h>

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

bool listCompare(list l1 , list l2){
	bool same = false;

	if (l1.length != l2.length)
	{
		same = false;
	}
	else{
		node* n1 = l1.head;
		node* n2 = l2.head;

	 	while(n1 != NULL && n2!= NULL){
			if(n1->d != n2->d){
				same = false;
				break;
			}
			n1 = n1->next;
			n2 = n2->next;
			same = true;
		}
	}	
	return same;
}

