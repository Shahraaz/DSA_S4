#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data ;
    struct node* next;
}Node;
FILE *fin,*fout;
Node* new_node(int x){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}
Node* add_node(Node* Head,int x){
    if(Head==NULL)
        return new_node(x);
    if(Head->next==NULL)
        Head->next = new_node(x);
    else
        add_node(Head->next,x);
    return Head;
}
Node* create(Node* Head){
    Head = NULL;
    int x,size;
    fscanf(fin,"%d",&size);
    while(size--){
        fscanf(fin,"%d",&x);
        Head = add_node(Head,x);
    }
    return Head;
}
void print(Node *Head){
    if(Head==NULL) return;
    fprintf(fout,"%d ",Head->data);
    print(Head->next);
}
int Count(Node* Head,int D){
    int count=0;
    Node *temp = Head;
    while(temp!=NULL){
        if(temp->data == D)
            count++;
        temp = temp->next;
    }
    return count;
}
void h_occur(Node* Head){
    if(Head==NULL){
        fprintf(fout,"List is empty\n");
        return;
    }
    int count,maxcount=-1,maxelement=0;
    Node *temp = Head;
    while(temp!=NULL){
        count = Count(Head,temp->data);
        if(count>maxcount){
            maxcount = count;
            maxelement = temp->data;
        }
        temp = temp->next;
    }
    fprintf(fout,"%d\n",maxelement); 
}
int main(){
    if((fin=fopen("input.txt","r"))==NULL){
        printf("Unbale to open input file\n");
        return 0;
    }
    if((fout=fopen("output.txt","w"))==NULL){
        printf("Unbale to open output file\n");
        fclose(fin);
        return 0;
    }
    char choice;
    Node *Head = NULL;
    do{
        fscanf(fin,"%c",&choice);
        switch(choice){
            case 'c' : Head = create(Head); break;
            case 'p' : print(Head); fprintf(fout,"\n"); break;
            case 'h' : h_occur(Head); break;;
            case 'a' : int x; fscanf(fin,"%d",&x); Head = add_node(Head,x); break;
            case 's' : break;
            default : fprintf(fout,"Invalid case\n");
        }
        getc(fin);
    }while(choice!='s');
    fclose(fin);
    fclose(fout);
    return 0;
}