#include "list.c"
#include <stdbool.h>
typedef list dystring;

struct Attr;
struct TagType;
struct TagList;
struct Page;



typedef struct Attr{
	dystring name;
	dystring value;
	
	struct Attr *previous;
	struct Attr *next;

	struct TagType *parent;
} attr;

typedef struct TagType{
	dystring name;	
	dystring content;
	attr *attribute;

	struct TagType *nextTag;
	struct TagType *parentTag;
	struct TagType *childTag;
	struct TagType *previousTag;	

	bool closed;
} tagType;



typedef struct TagList{
	int length;

	struct TagType* headTag;
	struct TagType* lastTag;


} tagList;


typedef struct Page
{	
	tagType *firstTag;
	


} page;