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
#define LEFT 1
#define EQUAL 0
#define RIGHT 2
#define INVALID -1

int find_relation(struct node *n, char alpha){
	if(n->data == alpha)
		return EQUAL;
	else if(n->data < alpha)
		return LEFT;
	else
		return RIGHT;
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

int main(){
	int input;
	char str[10];
	scanf("%d",&input);
	root = NULL;
	while(input--){
		scanf("%s",str);
		proceed(root,str);
	}
	printf("in printall \n\n");
	print_all(root);
	return 0;
}
