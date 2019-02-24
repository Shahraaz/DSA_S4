#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* RemoveSpace(char* str) {
	char* result = (char*)malloc(sizeof(char) * 1000);
	char* ptr = result;
	for (char* curr = str; (*curr) != '\0'; ++curr) {
		if ((*curr) == ' ') continue;
		*ptr = *curr;
		ptr++;
	}
	*ptr = '\0';
	free(str);
	return result;
}

typedef struct node {
	int data;
	struct node *left, *right, *parent;
}Node;

FILE *fin, *fout;
Node* newnode(int x) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = x;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

char *str;
Node* Make(Node* Tree) {
	if (*str == '(') str++;
	if (*str == ')') return NULL;
	int result = 0;
	while ((*str != '(') && (*str!=')')) {
		result = result * 10 + (*str - '0');
		str++;
	}
	Tree = newnode(result);
	if (*str == ')') {
		str++;
		return Tree;
	}
	Tree->left = Make(Tree->left);
	if (*str == ')') str++;
	Tree->right = Make(Tree->right);
	if (*str == ')') str++;
	return Tree;
}

void Preorder(Node *Tree) {
	if (Tree != NULL) {
		fprintf(fout, "( ");
		fprintf(fout, "%d ", Tree->data);
		if (Tree->left != NULL || Tree->right != NULL) {
			if (Tree->left != NULL)
				Preorder(Tree->left);
			else fprintf(fout, " ( ) ");
			if (Tree->right != NULL)
				Preorder(Tree->right);
			else fprintf(fout, " ( ) ");
		}
		fprintf(fout, ") ");
	}
}

Node* mirror(Node* T) {
	if (T == NULL) return NULL;
	Node *t1 = mirror(T->left), *t2 = mirror(T->right);
	T->right = t1;
	T->left = t2;
	return T;
}

int main() {
	if ((fin = fopen("input.txt", "r")) == NULL) {
		printf("Unbale to open input file\n");
		return 0;
	}
	if ((fout = fopen("output.txt", "w")) == NULL) {
		printf("Unbale to open output file\n");
		fclose(fin);
		return 0;
	}
	char ch, *instr = (char*)malloc(sizeof(char) * 1000);
	Node *Tree = NULL;
	int cnt = 0;
	do {
		ch = fgetc(fin);
		printf("%c\n", ch);
		switch (ch) {
			case 'c': 	fscanf(fin, "%[^\n]s", instr);
				instr = RemoveSpace(instr);
				str = instr;
				Tree = NULL;
				Tree = Make(Tree); 
				break;
			case 'p': Preorder(Tree); 
				fprintf(fout, "\n");
				break;
			case 'm': mirror(Tree); break;
			case 's': break;
			case '\n': break;
		}
	} while (ch != 's');
	return 0;
}