#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include <string.h>
#include <ctype.h>
//#include "types.c"

typedef struct Page{

	list taglist;


} page;


void getTags(FILE* fp);
size_t angularFind(FILE* fp);
list readTag(FILE* fp);
void printTag(char*,list,char*);
list readAttr(FILE* fp);
void skipTill(char,FILE* fp);
void skipQuotes(FILE* fp);
int listcmp(char*,list,int);
void analysis(list,FILE*);
void getQuotes(list*,FILE* );
char* listToArray(list);

int main(int argc, char const *argv[]){
	
	FILE* fp;

	fp = fopen(argv[1],"r+");

	getTags(fp);

	fclose(fp);	
	return 0;

}

void getTags(FILE* fp){
		while(angularFind(fp)){
			readTag(fp);

			// to print all tag names uncomment here
			//printTag( " ;",readTag(fp)," <--Tag\n\n ;" );
			
		}
}


size_t angularFind(FILE* fp){
	char brack,oneplus;
	size_t n;
	while(1){
		n= fread(&brack,sizeof(char),1,fp);
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

	return n;
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
		if(brack == ' '){
			// to print all attributes names uncomment here 
			//printTag("\t;",readAttr(fp)," <--attr\n ;" );
			

			readAttr(fp);
			break;	
		}
		insertChar(brack,&tag);
	}
	return tag;
}


list readAttr(FILE* fp){

	char atChar;
	list attr;
	attr.last = attr.head = NULL;
	while(1){
		size_t n= fread(&atChar,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(atChar == '>'){
			break;	
		}
		else if(atChar == '='){
			analysis(attr,fp);
			// skipQuotes(fp);
			break;	
		}
		else if(atChar == '\"'){
			skipTill('\"',fp);
		}
		else if(isalpha(atChar)){
		insertChar(atChar,&attr);
		}	
		else if(atChar == ' '){

			analysis(attr,fp);
			// to print all attributes names uncomment here
			//printTag("\t;",readAttr(fp)," <--attr\n ;" );
			
			readAttr(fp);
			break;	
		}
		
	}
	return attr;
}

void printTag(char* p,list tag,char* s){
	int i=0;
	while(p[i]!=';'){
		printf("%c",p[i] );
		i++;
	}
	i=0;
	node *n = tag.head;
	for(i=0;i<tag.length;i++){
		printf("%c",n->d);
		n = n->next;
	}
	i=0;
	while(s[i]!=';'){
		printf("%c",s[i] );
		i++;
	}
}

void skipTill(char till , FILE* fp){

	char skip;

	while(1){
		size_t n= fread(&skip,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(skip!=till){
			continue;
		}
		else{

			break;
		}

	}


}


void skipQuotes(FILE* fp){

	char skip;

	while(1){
		size_t n= fread(&skip,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(skip!='\"'){
			continue;
		}
		else{

			break;
		}
	}
}

void getQuotes(list *temp,FILE* fp){

	char skip;
	while(1){
		size_t n= fread(&skip,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(skip!='\"'){
			insertChar(skip,temp);
		}
		else{
			break;
		}
	}
}


// char* listToArray(list l){

// 	int i=0;
// 	node* n = l.head;
// 	char arr[l.length];
// 	for(i=0;i<l.length;i++){
// 		arr[i] = n->d;
// 		n = n->next;
// 	}

// 	return arr;
// }


void analysis(list l,FILE* fp){

	list link;

	if(listcmp("href",l,4)==0){
		skipTill('\"',fp);
		getQuotes(&link,fp);

		printTag("\n-->;",link,"\n;");
	}

}



int listcmp(char l1[],list l2,int len){

	int i=0,flag=0;

	node* n = l2.head;

	while(n != NULL && i<len){
		if(l1[i]!=n->d){
			flag=1;
		}
		i++;
		n = n->next;
	}
	return flag;
}