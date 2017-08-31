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

void insert(struct node *n,char *word,int index,int length){
	printf("index = %d, current node = %c , alpha %c\n",index,n->data,word[index]);
	int last=0;	
	char calpha = word[index];
	struct node * ptr;
	last = (index == length - 1) ? true : false;
	if(n->data == calpha){
		printf("in equal\n");
		if(last){
			mark_as_word(n);
		} else if(n->equal){
			insert(n->equal,word,++index,length);
		} else{
			n->equal = create_node(word[index+1]);
			insert(n->equal,word,++index,length);
		}
	} else if(calpha < n->data){
		printf("in left\n");
		if(n->left){
			insert(n->left,word,index,length);
		} else{
			n->left = create_node(word[index]);
			if(last){
				mark_as_word(n->left);
			} else {
				insert(n->left,word,++index,length);
			}
		}
	} else if(calpha > n->data){
		printf("in right\n");
		if(n->right){
			insert(n->right,word,index,length);
		} else{
			n->right = create_node(word[index]);
			if(last){
				mark_as_word(n->right);
			} else {
				insert(n->right,word,++index,length);
			}
		}
	}
	print_node(n);
	return;
}

struct node * find_start_node(struct node *n,char data){
	if(n){
		if(n->data == data){
			return n;
		}else if(n->data > data) {
			return find_start_node(n->left,data);
		}else {
			return find_start_node(n->right,data);
		}
	}
	return NULL;
}

void print_suggestion(struct node *n){
	char pref[10]="";
	int i=0;
	while(n){
		pref[i]=n->data;
		if(n->is_word){
			return;	
			// todo
		}
	}
}

int main(){
	struct node *root; 
	int input;
	char str[10];
	scanf("%d",&input);
	root = create_node('c');
	while(input--){
		scanf("%s",str);
		insert(root,str,0,strlen(str));
	}
	printf("in printall \n\n");
	print_all(root);
	return 0;
}
