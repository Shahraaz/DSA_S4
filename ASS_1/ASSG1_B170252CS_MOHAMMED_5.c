#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	int data;
	struct node *left, *right, *parent;
}Node;

Node *pre, *suc;
FILE *fin, *fout;
Node* newnode(int x) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = x;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

Node *insert(Node* Tree, int x) {
	if (Tree == NULL)
		return newnode(x);
	if (Tree->data == x)
		fprintf(fout, "Already Present\n");
	else if (Tree->data > x) {
		Node* temp = insert(Tree->left, x);
		Tree->left = temp;
		temp->parent = Tree;
	}
	else {
		Node* temp = insert(Tree->right, x);
		Tree->right = temp;
		temp->parent = Tree;
	}
	return Tree;
}

Node* search(Node* Tree, int x) {
	if (Tree == NULL) return NULL;
	if (Tree->data == x)
		return Tree;
	else if (Tree->data > x)
		return search(Tree->left, x);
	else return search(Tree->right, x);
}

Node* findmin(Node* Tree) {
	if (Tree == NULL)  return NULL;
	Node *curr = Tree;
	while (curr->left != NULL)
		curr = curr->left;
	return curr;
}

Node* findmax(Node* Tree) {
	if (Tree == NULL)  return NULL;
	Node *curr = Tree;
	while (curr->right != NULL)
		curr = curr->right;
	return curr;
}

Node* predecessor(Node* Tree) {
	if (Tree->left)
		return findmin(Tree);
	Node* temp = Tree->parent;
	while (temp != NULL && Tree == temp->left) {
		Tree = temp;
		temp = temp->parent;
	}
	return temp;
}

Node* Successor(Node* Tree) {
	if (Tree->right)
		return findmax(Tree);
	Node* temp = Tree->parent;
	while (temp != NULL && Tree == temp->right) {
		Tree = temp;
		temp = temp->parent;
	}
	return temp;
}

Node* Transplant(Node *Tree, Node *u, Node *v) {
	if (u->parent == NULL)	Tree = v;
	else if (u == (u->parent->left))
		u->parent->left = v;
	else u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
	return Tree;
}

Node* Delete(Node *Tree, Node *z) {
	if (z->left == NULL)
		Tree = Transplant(Tree, z, z->right);
	else if (z->right == NULL)
		Tree = Transplant(Tree, z, z->left);
	else {
		Node* y = findmin(z->right);
		if (y->parent != z) {
			Tree = Transplant(Tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Tree = Transplant(Tree, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	return Tree;
}

void Inorder(Node *Tree) {
	if (Tree != NULL) {
		Inorder(Tree->left);
		fprintf(fout, "%d ", Tree->data);
		Inorder(Tree->right);
	}
}

void Preorder(Node *Tree) {
	if (Tree != NULL) {
		fprintf(fout, "( ");
		fprintf(fout, "%d ", Tree->data);
		Preorder(Tree->left);
		Preorder(Tree->right);
		fprintf(fout, ") ");
	}
	else fprintf(fout, " ( ) ");
}

void Postorder(Node *Tree) {
	if (Tree != NULL) {
		Postorder(Tree->left);
		Postorder(Tree->right);
		fprintf(fout, "%d ", Tree->data);
	}
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
	int x,n;
	Node* Tree = NULL;
	fscanf(fin, " %d", &n);
	while (n--) {
		fscanf(fin, " %d", &x);
		Tree = insert(Tree, x);
	}
	Preorder(Tree);
	return 0;
}
