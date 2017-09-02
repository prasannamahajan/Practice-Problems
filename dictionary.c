#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define YES 1
#define NO 0
#define LEFT -1
#define EQUAL 0
#define RIGHT 1
#define INVALID -2
#define MAX_LENGTH 1000
#define DATA(n) (!n)?' ':n->data
#define GO(parent,current,direction) do { \
	parent = current; \
	current = current->direction; \
} while(0) 
struct node {
	char data;
	struct node *left;
	struct node *equal;
	struct node *right;
	int is_word;
};

struct node *root; 

struct node * create_node(char data){
	struct node *n;
	n = (struct node *)malloc(sizeof(struct node));
	n->data = data;
	n->left = n->right = n->equal = NULL;
	n->is_word = 0;
	return n;
}
void print_node(struct node *n){
	if(n){

		printf("--------------------\n");
		printf("%c = %c | %c | %c [%d]\n",n->data,DATA(n->left),DATA(n->equal),DATA(n->right),n->is_word);
		return;
	}
}

void print_all(struct node *n){
	if(n){
		print_node(n);
		print_all(n->left);
		print_all(n->equal);
		print_all(n->right);
	}	
}

static inline int find_relation(struct node *n, char alpha){
	if(n->data == alpha)
		return EQUAL;
	else if(n->data < alpha)
		return RIGHT;
	else
		return LEFT;
}

static inline void save_node(struct node *parent,struct node *child,int relation){
	if(!parent){
		root = child;
		return;
	}
	switch (relation) {
		case LEFT: 
			parent->left = child;
			break;
		case EQUAL: 
			parent->equal = child;
			break;
		case RIGHT: 
			parent->right = child;
			break;
	}
}


int insert(struct node *root,char *data){
	int index=0,length,relation = INVALID;
	struct node *current,*parent=NULL;
	current = root;
	length = strlen(data);
	while(index < length){
		if(!current){
			current = create_node(data[index]);
			save_node(parent,current,relation);
			GO(parent,current,equal);
			relation = EQUAL;
			index++;
			continue;
		}
		relation = find_relation(current,data[index]);
		switch (relation) {
			case LEFT:
				GO(parent,current,left);
				break;
			case EQUAL:
				GO(parent,current,equal);
				save_node(parent,current,relation);
				index++;
				break;
			case RIGHT:
				GO(parent,current,right);
				break;
		}
	}
	parent->is_word=YES;
}

static inline void add_to_string(char *prefix, char new, int current_length){
	prefix[current_length]=new;
	prefix[current_length+1]='\0';
}

void print_all_word(struct node *ptr,char *prefix, int len){
	if(!ptr)
		return;
	prefix[len]=0;
	if(ptr->is_word){
		printf("word : %s%c\n",prefix,ptr->data);
	}
	print_all_word(ptr->left,prefix,len);
	print_all_word(ptr->right,prefix,len);

	add_to_string(prefix,ptr->data,len);
	print_all_word(ptr->equal,prefix,++len);
}

struct node * find_node(struct node *ptr,char *prefix,int index){
	int relation;
	int i_am_last;
	if(!ptr)
		return NULL;
	relation = find_relation(ptr,prefix[index]);
	switch (relation) {
		case EQUAL: 
			i_am_last = (prefix[index+1] == 0) ?  YES : NO ;
			if(i_am_last)
				return ptr;
			return find_node(ptr->equal,prefix,++index);
		case LEFT: 
			return find_node(ptr->left,prefix,index);
		case RIGHT: 
			return find_node(ptr->right,prefix,index);
	}
}

void search(struct node *root,char *prefix){
	struct node *match = NULL;
	match = find_node(root,prefix,0);
	if(match) {
		if(match->is_word)
			printf("word : %s\n",prefix);
		print_all_word(match->equal,prefix,strlen(prefix));
	} else {
		printf("no result found");
	}
}

void free_all(struct node *n){
	if(!n)
		return;
	free_all(n->left);
	free_all(n->equal);
	free_all(n->right);
	free(n);
}

int main(){
	int input;
	char str[MAX_LENGTH];
	char prefix[MAX_LENGTH];
	scanf("%d",&input);
	root = NULL;
	while(input--){
		scanf("%s",str);
		insert(root,str);
	}
	scanf("%s",prefix);	
	printf("Search Result for %s: \n",prefix);
	search(root,prefix);
	free_all(root);
	return 0;
}
