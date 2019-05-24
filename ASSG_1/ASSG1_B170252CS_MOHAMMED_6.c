#include<stdio.h>
#include<stdlib.h>

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
	while (*str != '(') {
		result = result * 10 + (*str - '0');
		str++;
	}
	Tree = newnode(result);
	Tree->left = Make(Tree->left);
	if (*str == ')') str++;
	Tree->right = Make(Tree->right);
	if (*str == ')') str++;
	return Tree;
}

int Height(Node* Tree) {
	if (Tree == NULL) return -1;
	int t1 = Height(Tree->left), t2 = Height(Tree->right);
	if (t1 < t2)
		return t2 + 1;
	return t1 + 1;
}

int maxi(int a, int b) {
	if (a < b) return b;
	return a;
}

int height(Node* root, int* ans){
	if (root == NULL)
		return -1;
	int left_height = height(root->left, ans);
	int right_height = height(root->right, ans);
	*ans = maxi(*ans, 2 + left_height + right_height);
	return 1 + maxi(left_height, right_height);
}

int diameter(Node* root){
	if (root == NULL)
		return 0;
	int ans = INT_MIN;
	int height_of_tree = height(root, &ans);
	return ans;
}

int min, max;
void Width(Node* Tree, int x) {
	if (Tree == NULL) return;
	Width(Tree->left, x - 1);
	Width(Tree->right, x + 1);
	if (x < min) min = x;
	if (x > max) max = x;
	return;
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
	fscanf(fin, "%[^\n]s", instr);
	instr = RemoveSpace(instr);
	str = instr;
	Node* Tree = Make(Tree);
	fprintf(fout, "%d ", Height(Tree));
	fprintf(fout, "%d ", diameter(Tree));
	min = 1 << 30, max = -(1 << 30);
	Width(Tree, 0);
	fprintf(fout, "%d", max - min);
	return 0;
}