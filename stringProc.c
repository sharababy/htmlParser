#include <stdio.h>
#include <stdlib.h>
#include "list.c"
//#include "types.c"




void getTags(FILE* fp);
void angularFind(FILE* fp);
list readTag(FILE* fp);
void printTag(list);

int main(){
	
	FILE* fp;

	fp = fopen("index.html","r+");

	getTags(fp);

	fclose(fp);	
	return 0;

}

void getTags(FILE* fp){
		while(!feof(fp)){
		angularFind(fp);
		printTag( readTag(fp) );
		}
}


void angularFind(FILE* fp){
	char brack,oneplus;
	while(1){
		size_t n= fread(&brack,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(brack == '<'){

			fread(&oneplus,sizeof(char),1,fp);
			if(oneplus=='/'){

				continue;
			}	
			else{
				fseek(fp,-sizeof(char),SEEK_CUR);
				break;
			}
			
		}
	}
}



list readTag(FILE* fp){

	char brack;
	list tag;
	tag.last = tag.head = NULL;
	while(1){
		size_t n= fread(&brack,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(brack == '>'){
			break;	
		}
		insertChar(brack,&tag);
	}
	return tag;
}


void printTag(list tag){
	int i=0;	
	node *n = tag.head;
	for(i=0;i<tag.length;i++){
		printf("%c",n->d);
		n = n->next;
	}
	printf("\n");
}

