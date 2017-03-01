#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htmldatatypes.c"
#include <stdbool.h>

int debug;
tagList mainList;
tagType* workingTag;

size_t angularFind(FILE* fp);
tagType* readTag(FILE* fp);
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
void printTagToFile(tagType tag,FILE* data);

int checkList(tagType newTag ,tagList mainList);
void insertoList(tagType *newTag ,tagList *mainList);
bool checkAndCloseTag(tagType *newTag,tagList *mainList);

tagType* getParentTag(tagList* mainList);
void setChildTag(tagType* thisChild , tagType* forThisParent);
bool checkBackSlash(tagType* newTag);

void printHtmlTree(tagList mainList,FILE* data);
int heightOfTag(tagType* tag);
void correctTagList(tagList *mainList);

void closeThis(int lastOpen);
int checkLastOpen(tagType newTag ,tagList mainList);

void checkIfSingleTag(tagType* newTag);


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





tagType* readTag(FILE* fp){

	char brack;
	tagType *newTag = (tagType*)malloc(sizeof(tagType));
	
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
	

	if(checkBackSlash(newTag) == false){
		insertoList(newTag , &mainList);
	}
	
	return newTag;
}


void correctTagList(tagList *mainList){

	tagType *currentTag = mainList->lastTag;
	tagType *tempParent,*tempChild;
	
	while(currentTag!=NULL){
		tempParent = currentTag->parentTag;
		if (tempParent!=NULL)
		{
			if (tempParent->closed == true && currentTag->closed == false)
			{
				currentTag->closed = true;
				tempChild = currentTag->childTag;
				while(tempChild!=NULL){
					if( tempChild->parentTag == currentTag )
					{
						tempChild->parentTag = tempParent;
					}
					else{
						break;
					}
					tempChild = tempChild->nextTag;
				}
			}
		}
		currentTag = currentTag->previousTag;
	}
}
//new ->
// bool checkBackSlash(tagType* newTag){
// 	bool closed=false;
// 	if(newTag->name.head)
// 		if (newTag->name.head->d == '/')
// 		{
// 			closed = true;
// 		}
// 	return closed;
// }

//old->
bool checkBackSlash(tagType* newTag){
	bool closed=false;
	int lastOpen;
	if(newTag->name.head)
		if (newTag->name.head->d == '/')
		{
			newTag->name.head = newTag->name.head->next;
			newTag->name.length--;
			closed=true;
			//closed = checkAndCloseTag(newTag,&mainList);
			lastOpen = checkLastOpen(*newTag,mainList);
			closeThis(lastOpen);
		}
	return closed;
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



int listcmp(char l1[],list l2,int len){

	int i=0,flag=0;

	node* n = l2.head;

	if (len == l2.length)
	{

		while(n != NULL && i<len){
			if(l1[i]!=n->d){
				flag=1;
			}
			i++;
			n = n->next;
		}
	}
	else{
		flag = 1;
	}
	return flag;
}


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
void closeThis(int lastOpen){

	tagType* currentTag;

	currentTag = mainList.headTag;

	while(currentTag!=NULL){

		if( currentTag->id == lastOpen){
			currentTag->closed = true;
			break;
		}
		currentTag = currentTag->nextTag;

	}

}

int checkLastOpen(tagType newTag ,tagList mainList){

	// returns true if tag exists and is open
	int exists = 0;

	tagType* currentTag;

	currentTag = mainList.lastTag;

	while(currentTag!=NULL){

		if( listCompare(currentTag->name , newTag.name) == true && currentTag->closed==false){
			exists = currentTag->id;
			break;
		}
		currentTag = currentTag->previousTag;

	}

	return exists;
}

int checkList(tagType newTag ,tagList mainList){

	// returns true if tag exists

	int exists = 0;

	tagType* currentTag;

	currentTag = mainList.lastTag;

	while(currentTag!=NULL){

		if( listCompare(currentTag->name , newTag.name) == true){
			exists = currentTag->id;
			break;
		}
		currentTag = currentTag->previousTag;

	}

	return exists;
}



bool checkAndCloseTag(tagType *newTag,tagList *mainList){

	bool closed = false;
	tagType* currentTag;

	currentTag = mainList->lastTag;

	while(currentTag!=NULL){

		if( listCompare(currentTag->name,newTag->name)==true){
			currentTag->closed = true;
			closed = true;
			//workingTag = currentTag->parentTag;
			break;
		}
		currentTag = currentTag->previousTag;

	}
	//printf("%s\n",currentTag->closed ? "true" : "false" );
	return closed;

}

// for now we will manually check name of tag and close it if it a single line tag
void checkIfSingleTag(tagType* newTag){

	if (listcmp("img",newTag->name,3)==0 || listcmp("link",newTag->name,4)==0
	|| listcmp("br",newTag->name,2)==0 || listcmp("br/",newTag->name,3)==0 )
	{
		newTag->closed = true;
	}

}

void insertoList(tagType *newTag ,tagList *mainList){

	newTag->id = mainList->length+1;
	newTag->closed =false;

	checkIfSingleTag(newTag);

	if(mainList->lastTag != NULL){

		newTag->parentTag = getParentTag(mainList);		
		//newTag->parentTag = workingTag;
		mainList->lastTag->nextTag = newTag;
		(newTag->previousTag) = (mainList->lastTag);
		mainList->lastTag = newTag;
		if (newTag->parentTag != NULL)
		{
			setChildTag(newTag , newTag->parentTag);
		}
		//workingTag = newTag;
	}
	else{
		newTag->previousTag = NULL;
		newTag->parentTag = NULL;
		mainList->lastTag = mainList->headTag = newTag;
		//workingTag = newTag;
	}

	mainList->length++;

}


tagType* getParentTag(tagList* mainList){

	tagType *currentTag;

	currentTag = mainList->lastTag;
	
	while(currentTag!= NULL){

			if (currentTag->closed==false)
			{
				break;
			}
			
			currentTag = currentTag->previousTag;
		}
	
	return (currentTag);

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


void printTagToFile(tagType tag,FILE* data){
	

	int i=0;
	

	node *n = tag.name.head;
	for(i=0;i<tag.name.length;i++){
		fprintf(data,"%c",n->d);
		n = n->next;

	}
	// fprintf(data," %d",tag.id);
	

	// fprintf(data, " ");
	// if (tag.parentTag!=NULL)
	// 	{
	// 		n = tag.parentTag->name.head;
	// 		for(i=0;i<tag.parentTag->name.length;i++){
	// 			fprintf(data,"%c",n->d);
	// 			n = n->next;
	// 		}		
	// 	}	
	// 	fprintf(data, " ");
	// 	if (tag.childTag!=NULL)
	// 	{
	// 		n = tag.childTag->name.head;
	// 		for(i=0;i<tag.childTag->name.length;i++){
	// 			fprintf(data,"%c",n->d);
	// 			n = n->next;
	// 		}		
	// 	}	
	
	fprintf(data, "\n");
	//fprintf(data, ",%s\n",tag.closed ? "true" : "false" );
	

}



void startParse(FILE* fp ,FILE* data){

		debug = 0;
		mainList.length = 0;

		tagType *buffer = (tagType*)malloc(sizeof(tagType));
		buffer->closed = false;
		int i=0;

		while(angularFind(fp)){


			buffer = readTag(fp); 
			//printTagToFile(*buffer,data);	

			// to print all tag names uncomment here
			//printTag( " ;",buffer->name," <--Tag\n\n ;" );

		}
		correctTagList(&mainList);

		printHtmlTree(mainList,data);
}


int heightOfTag(tagType* tag){


	tagType *currentTag = tag;

	int height=0;

	while(currentTag->parentTag!=NULL){
		height++;
		currentTag = currentTag->parentTag;

	}


	return height;

					

}


void printHtmlTree(tagList mainList , FILE* data){

	tagType *currentTag = mainList.headTag;

	int distance,count;

	while(currentTag!=NULL){

		distance = heightOfTag(currentTag);

		for (int count = 0; count < distance; ++count)
		{
			fprintf(data,"\t");
		}
		printTagToFile(*currentTag , data);
		// printTag(";",currentTag->name,";");
		// if(currentTag->parentTag != NULL){
		// 	printTag("-->;",currentTag->parentTag->name,"\n;");
		// }

		currentTag = currentTag->nextTag;
	}
}



// if same names are given it is unable to from a proper printHtmlTree