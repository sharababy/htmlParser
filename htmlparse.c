#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htmldatatypes.c"
#include "htmltagtree.c"
#include <stdbool.h>

int debug;
tagList mainList;


size_t angularFind(FILE* fp);
tagType readTag(FILE* fp);
// list readAttr(FILE* fp, FILE* data);
// void printTag(char* p,list tag,char* s);
void skipTill(char till , FILE* fp);
// void skipQuotes(FILE* fp);
// void analysis(list l,FILE* fp);
// void getQuotes(list *temp,FILE* fp);
// int listcmp(char l1[],list l2,int len);
// void reachQuotes(FILE* fp);
void startParse(FILE* fp , FILE* data);
void saveTill(char stopChar , list buffer,FILE* fp);
void printTagtoFile(tagType tag,FILE* data);

bool checkList(tagType newtag ,tagList mainList);
void insertoList(tagType *newTag ,tagList *mainList);
bool checkAndCloseTag(tagType *newTag,tagList *mainList);

tagType getParentTag(tagList mainList);
void setChildTag(tagType* thisChild , tagType* forThisParent);
void removeBackSlach(tagType* newTag);

size_t angularFind(FILE* fp){
	
	char brack;
	size_t n;
	while(1){
		n = fread(&brack,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		if(brack == '<'){
			
			break;
			
		}
	}

	return n;
}



tagType readTag(FILE* fp){

	char brack;
	tagType *newTag = (*tagType)malloc(sizeof(tagType));
	
	newTag->name.last = newTag->name.head = NULL;

	while(1){
		size_t n= fread(&brack,sizeof(char),1,fp);
		if(n<1){
			break;
		}
		else if(brack == '>'){
			break;	
		}
		else if(brack == ' ' && newTag->name.head!=NULL){
				//attributes are read here
				break;
		}
		else if(brack == ' ' && newTag->name.head==NULL){
				continue;
		}
		else{
			insertChar(brack,&newTag->name);
		}
	}

	removeBackSlach(newTag);

	bool tagExists = checkList(newTag , mainList);


	if( checkAndCloseTag(newTag,&mainList) == true ){
		
	}else{
		insertoList(newTag , &mainList);
	}

	return newTag;
}


void removeBackSlach(tagType* newTag){

	if(newTag->name.head)
		if (newTag->name.head->d == '/')
		{
			newTag->name.head = newTag->name.head->next;

		}
}

// list readAttr(FILE* fp ,FILE* data){

// 	char atChar;
// 	list attr;
// 	attr.last = attr.head = NULL;
// 	while(1){
// 		size_t n= fread(&atChar,sizeof(char),1,fp);
// 		if(n<1){
// 			break;
// 		}
// 		if(atChar == '>'){
// 			break;	
// 		}
// 		else if(atChar == '='){
// 			analysis(attr,fp);
// 			// skipQuotes(fp);
// 			break;	
// 		}
// 		// else if(atChar == '\"' ){
					

// 		// 	// reachQuotes(fp);
// 		// 	//skipTill('\"',fp);
// 		// }
// 		else if(isalpha(atChar)){
// 		insertChar(atChar,&attr);
// 		}	
// 		else if(atChar == ' '){

// 			analysis(attr,fp);
// 			// to print all attributes names uncomment here
// 			//printTag("\t;",readAttr(fp)," <--attr\n ;" );
			
// 			readAttr(fp,data);
// 			break;	
// 		}
		
// 	}
// 	return attr;
// }

// void printTag(char* p,list tag,char* s){
// 	int i=0;
// 	while(p[i]!=';'){
// 		printf("%c",p[i] );
// 		i++;
// 	}
// 	i=0;
// 	node *n = tag.head;
// 	for(i=0;i<tag.length;i++){
// 		printf("%c",n->d);
// 		n = n->next;
// 	}
// 	i=0;
// 	while(s[i]!=';'){
// 		printf("%c",s[i] );
// 		i++;
// 	}
// }

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


// void skipQuotes(FILE* fp){

// 	char skip;

// 	while(1){
// 		size_t n= fread(&skip,sizeof(char),1,fp);
// 		if(n<1){
// 			break;
// 		}
// 		if(skip!='\"'){
// 			continue;
// 		}
// 		else{

// 			break;
// 		}
// 	}
// }

// void getQuotes(list *temp,FILE* fp){

// 	char skip;
// 	while(1){
// 		size_t n= fread(&skip,sizeof(char),1,fp);
// 		if(n<1){
// 			break;
// 		}
// 		if(skip!='\"' || skip!='\''){
// 			insertChar(skip,temp);
// 		}
// 		else{
// 			break;
// 		}
// 	}
// }


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


// void analysis(list l,FILE* fp){

// 	list link;

// 	if(listcmp("href",l,4)==0){
// 		//skipTill('\"',fp);
// 		reachQuotes(fp);
// 		getQuotes(&link,fp);

// 		printTag("\n-->;",link,"\n;");
// 	}

// }



// int listcmp(char l1[],list l2,int len){

// 	int i=0,flag=0;

// 	node* n = l2.head;

// 	while(n != NULL && i<len){
// 		if(l1[i]!=n->d){
// 			flag=1;
// 		}
// 		i++;
// 		n = n->next;
// 	}
// 	return flag;
// }


// void reachQuotes(FILE* fp){

// 	char skip;

// 	while(1){
// 		size_t n= fread(&skip,sizeof(char),1,fp);
// 		if(n<1){
// 			break;
// 		}
// 		if(skip!='\"' || skip!='\''){
// 			continue;
// 		}
// 		else{

// 			break;
// 		}

// 	}


// }


bool checkList(tagType newtag ,tagList mainList){

	// returns true if tag exists

	bool exists = false;

	tagType* currentTag;

	currentTag = mainList.headTag;

	while(currentTag!=NULL){

		if( listCompare(currentTag.name , newTag.name) == true){
			exists = true;
			break;
		}
		currentTag = currentTag->nextTag;

	}

	return exists;
}
bool checkAndCloseTag(tagType *newTag,tagList *mainList){

	bool closed = false;
	tagType* currentTag;

	currentTag = mainList->headTag;

	while(currentTag!=NULL){

		if( listCompare(currentTag->name , newTag->name) == true){
			currentTag->closed = true;
			closed = true;
			break;
		}
		currentTag = currentTag->nextTag;

	}

	return closed;

}


void insertoList(tagType *newTag ,tagList *mainList){

	mainList->lastTag->nextTag = newTag;

	newTag->previousTag = mainList->lastTag;

	newTag->parentTag = getParentTag(mainList);

	setChildTag(newTag , newTag->parentTag);



}


tagType getParentTag(tagList mainList){

	tagType *currentTag;

	currentTag = mainList->headTag;

	while(currentTag->closed==true && currentTag!=NULL){

			currentTag = currentTag->nextTag;

		}

	return currentTag;

}

void setChildTag(tagType *thisChild, tagType* forThisParent){

	forThisParent->childTag = thisChild;

}

void saveTill(char stopChar , list buffer , FILE* fp){

	char input;

	while(1){
		size_t n= fread(&input,sizeof(char),1,fp);
	
		if(input == '>' || n<1 || input == stopChar){
			break;
		}
		else{
			insertChar(input , &buffer);
		}
	}
}


void printTagtoFile(tagType tag,FILE* data){
	int i=0;
	
	node *n = buffer.name.head;
			
	for(i=0;i<buffer.name.length;i++){
		fprintf(data,"%c",n->d);
		n = n->next;
	}
	fprintf(data, "\n" );
	
}



void startParse(FILE* fp ,FILE* data){

		debug = 0;

		tagType buffer;
		buffer.closed = false;
		int i=0;
		while(angularFind(fp)){

			buffer = readTag(fp); 
				
			printTagtoFile(buffer,data);	
			
			// to print all tag names uncomment here
			//printTag( " ;",readTag(fp)," <--Tag\n\n ;" );
			
		}
}


