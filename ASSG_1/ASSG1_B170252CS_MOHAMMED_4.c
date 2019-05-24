#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    int data;
    struct node *left,*right,*parent;
}Node;

Node *pre, *suc;
FILE *fin, *fout;
Node* newnode(int x){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp -> data = x;
    temp -> left = temp -> right = temp -> parent = NULL;
    return temp; 
}

Node *insert(Node* Tree,int x){
    if(Tree==NULL)
        return newnode(x);
    if(Tree->data==x)
        fprintf(fout,"Already Present\n");
    else if(Tree->data>x){
        Node* temp = insert(Tree->left,x);
        Tree->left = temp;
        temp->parent = Tree;
    }
    else{
        Node* temp = insert(Tree->right,x);
        Tree->right = temp;
        temp->parent = Tree;
    }
    return Tree;
}

Node* search(Node* Tree,int x){
    if(Tree==NULL) return NULL;
    if(Tree->data==x)
        return Tree;
    else if(Tree->data>x)
        return search(Tree->left,x);
    else return search(Tree->right,x);
}

Node* findmin(Node* Tree){
    if(Tree==NULL)  return NULL;
    Node *curr = Tree;
    while(curr->left!=NULL)
        curr=curr->left;
    return curr;
}

Node* findmax(Node* Tree){
    if(Tree == NULL)  return NULL;
    Node *curr = Tree;
    while(curr->right!=NULL)
        curr = curr->right;
    return curr;
}

Node* predecessor(Node* Tree){
    if(Tree->left)
        return findmin(Tree);
    Node* temp = Tree->parent;
    while(temp != NULL && Tree == temp->left){
        Tree = temp;
        temp = temp->parent;
    }
    return temp;
}

Node* Successor(Node* Tree){
    if(Tree->right)
        return findmax(Tree);
    Node* temp = Tree->parent;
    while(temp != NULL && Tree == temp->right){
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
	else{
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
		fprintf(fout,"%d ", Tree->data);
		Inorder(Tree->right);
	}
}

void Preorder(Node *Tree) {
	if (Tree != NULL) {
		fprintf(fout,"%d ", Tree->data);
		Preorder(Tree->left);
		Preorder(Tree->right);
	}
}

void Postorder(Node *Tree) {
	if (Tree != NULL) {
		Postorder(Tree->left);
		Postorder(Tree->right);
		fprintf(fout,"%d ", Tree->data);
	}
}

int main(){
	if ((fin = fopen("input.txt", "r")) == NULL) {
		printf("Unbale to open input file\n");
		return 0;
	}
	if ((fout = fopen("output.txt", "w")) == NULL) {
		printf("Unbale to open output file\n");
		fclose(fin);
		return 0;
	}
    int x;
    Node* Tree = NULL;
    char input[100],stop[]="stop",insr[]="insr",srch[]="srch",minm[]="minm",maxm[]="maxm",pred[]="pred",succ[]="succ",delt[]="delt",inor[]="inor",prer[]="prer",post[]="post";
    do{
        fscanf(fin,"%s",input);
//		printf("%s\n", input);
        if(strcmp(input,insr)==0){
            fscanf(fin," %d",&x);
	//		printf("%d\n", x);
            Tree = insert(Tree,x);
        }
        else if(strcmp(input,srch)==0){
            fscanf(fin," %d",&x);
		//	printf("%d\n", x);
			if(search(Tree,x)==NULL)
                fprintf(fout,"NOT FOUND\n");
            else fprintf(fout,"FOUND\n");
        }
        else if(strcmp(input,minm)==0){
            if(findmin(Tree)!=NULL)
                fprintf(fout,"%d\n",findmin(Tree)->data);
            else fprintf(fout,"NIL\n");
        }
        else if(strcmp(input,maxm)==0){
            if(findmax(Tree)!=NULL)
                fprintf(fout,"%d\n",findmax(Tree)->data);
            else fprintf(fout,"NIL\n");
        }
        else if(strcmp(input,pred)==0){
            fscanf(fin," %d",&x);
			//printf("%d\n", x);
			Node *temp = search(Tree,x);
            if(temp!=NULL){
                temp = predecessor(temp);
                if(temp!=NULL)
                    fprintf(fout,"%d\n",temp->data);
                else fprintf(fout,"NIL\n");
            }
            else fprintf(fout,"NOT FOUND\n");
        }
        else if(strcmp(input,succ)==0){
            fscanf(fin," %d",&x);
		//	printf("%d\n", x);
			Node *temp = search(Tree,x);
            if(temp!=NULL){
                temp = Successor(temp);
                if(temp!=NULL)
                    fprintf(fout,"%d\n",temp->data);
                else fprintf(fout,"NIL\n");
            }
            else fprintf(fout,"NOT FOUND\n");            
        }
        else if(strcmp(input,delt)==0){
			fscanf(fin," %d", &x);
//			printf("%d\n", x);
			Node *temp = search(Tree, x);
			if (temp != NULL)
				Tree = Delete(Tree,temp);
			else fprintf(fout,"NOT FOUND\n");
        }
        else if(strcmp(input,inor)==0){
			Inorder(Tree);
			fprintf(fout,"\n");
        }
        else if(strcmp(input,prer)==0){
			Preorder(Tree);
			fprintf(fout,"\n");
        }
        else if(strcmp(input,post)==0){
			Postorder(Tree);
			fprintf(fout,"\n");
        }
        else if(strcmp(input, stop) != 0){
            fprintf(fout,"Invalid Input\n");
        }
	} while (strcmp(input, stop) != 0);
	fclose(fin);
	fclose(fout);
    return 0;
}
