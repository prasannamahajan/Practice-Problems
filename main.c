#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define true 1
#define false 0
struct node {
	char data;
	struct node *left;
	struct node *equal;
	struct node *right;
	int is_word;
};

struct node * create_node(char data){
	struct node *n;
	n = (struct node *)malloc(sizeof(struct node));
	n->data = data;
	n->left = n->right = n->equal = NULL;
	n->is_word = 0;
	printf("creating data with %c and adress %u\n",data,n);
	return n;
}
struct node *root; 
#define DATA(n) (!n)?' ':n->data
void print_node(struct node *n){
	if(n){

		printf("--------------------\n");
		printf("%c = %c | %c | %c [%d]\n",n->data,DATA(n->left),DATA(n->equal),DATA(n->right),n->is_word);
		return;
		printf("node %c : %u\n",n->data,n);
		printf("%c|%d\n",n->data,n->is_word);
		printf("%u[%c] |%u[%c] | %u[%c]\n",n->left,DATA(n->left),n->equal,DATA(n->equal),n->right,DATA(n->right));
	}
}

void mark_as_word(struct node *n){
	n->is_word=1;
}

void print_all(struct node *n){
	if(n){
		print_node(n);
		print_all(n->left);
		print_all(n->equal);
		print_all(n->right);
	}	
}
#define LEFT -1
#define EQUAL 0
#define RIGHT 1
#define INVALID -2

int find_relation(struct node *n, char alpha){
	if(n->data == alpha)
		return EQUAL;
	else if(n->data < alpha)
		return RIGHT;
	else
		return LEFT;
}

struct node * nextNode(struct node *n,int relation){
	switch (relation) {
		case LEFT: 
			return n->left;
		case EQUAL: 
			return n->equal;
		case RIGHT: 
			return n->right;
	}
}

void save_node(struct node *parent,struct node *child,int relation){
	if(!parent){
		root = child;
		return;
	}
	//printf("relation %c  to %c is %d\n",parent->data,child->data,relation);
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

int proceed(struct node *root,char *data){
	int index=0;
	int length;
	struct node *current,*parent=NULL;
	int relation = INVALID;
	current = root;
	length = strlen(data);
	while(index < length){
		if(!current){
			current = create_node(data[index]);
			save_node(parent,current,relation);
			parent = current;
			current = current->equal;
			relation = EQUAL;
			index++;
			continue;
		}
		relation = find_relation(current,data[index]);
		if(relation == EQUAL){
			parent = current;
			current = current->equal;
			save_node(parent,current,relation);
			index++;
			continue;
		}
		if(relation == LEFT){
			parent = current;
			current = current->left;
			continue;
		}
		if(relation == RIGHT){
			parent = current;
			current = current->right;
			continue;
		}
	}
	mark_as_word(parent);
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

	prefix[len]=ptr->data;
	prefix[len+1]=0;
	print_all_word(ptr->equal,prefix,len+1);
}

struct node * find_node(struct node *ptr,char *prefix,int index){
	int relation;
	int iamlast;
	if(!ptr)
		return NULL;
	relation = find_relation(ptr,prefix[index]);
	switch (relation) {
		case EQUAL: 
			iamlast = (prefix[index+1] == 0) ?  1 : 0 ;
			if(iamlast)
				return ptr;
			return find_node(ptr->equal,prefix,++index);
			break;
		case LEFT: 
			return find_node(ptr->left,prefix,index);
			break;
		case RIGHT: 
			return find_node(ptr->right,prefix,index);
			break;
	}
}
void search(struct node *root,char *prefix){
	struct node *match = NULL;
	printf("IN SEARCH RESULT \n");
	match = find_node(root,prefix,0);
	if(match) {
		if(match->is_word)
			printf("word : %s\n",prefix);
		print_all_word(match->equal,prefix,strlen(prefix));
	} else {
		printf("no result found");
	}
}

int main(){
	int input;
	char str[10];
	char prefix[10];
	scanf("%d",&input);
	root = NULL;
	while(input--){
		scanf("%s",str);
		proceed(root,str);
	}
	printf("in printall \n\n");
	print_all(root);
	scanf("%s",prefix);	
	search(root,prefix);
	//printf("in print all word\n");
	//print_all_word(root,prefix,0);
	return 0;
}
