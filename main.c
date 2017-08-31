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

void print_node(struct node *n){
	if(n){
		printf("node %c : %u\n",n->data,n);
		printf("%c|%d\n",n->data,n->is_word);
		printf("%u|%u|%u\n",n->left,n->equal,n->right);
	}
}

void mark_as_word(struct node *n){
	n->is_word=1;
	print_node(n);
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

int main(){
	struct node *root; 
	int input;
	char str[10];
	scanf("%d",&input);
	root = create_node('m');
	while(input--){
		scanf("%s",str);
		insert(root,str,0,strlen(str));
	}
	printf("in printall \n\n");
	print_all(root);
	return 0;
}
