#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htmlparse.c"


int main(int argc, char const *argv[]){
	
	FILE *htmlPage,*databag;

	// char* datastore;

	// strcpy(datastore , argv[1]);

	// strcat(datastore , ".databag");

	htmlPage = fopen(argv[1],"r+");
	databag = fopen("hello.databag","w+");

	startParse( htmlPage , databag);

	fclose( htmlPage );
	fclose( databag );
	return 0;

}

