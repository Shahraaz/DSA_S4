#include<stdio.h>
#include<stdlib.h>
FILE *fin,*fout;
char* RemoveSpace(char* str){
    char* result = (char*)malloc(sizeof(char)*1000);
    char* ptr = result;
    for(char* curr=str;(*curr)!='\0';++curr){
        if((*curr)==' ') continue;
        *ptr = *curr;
        ptr++;
    }
    *ptr = '\0';
    free(str); 
    return result;
}
char Stack[1000];
int size = 0;
int isoperator(char c){
    return ((c == '+') || (c == '-') || (c =='*') || (c == '/') || (c == '^'));
}
void push(char c){
    Stack[size++] = c;
}
int isempty(){
    return size==0;
}
int top(){
    if(size>0)
        return Stack[size-1];
	return 0;
}
void pop(){
    if(!isempty())
        size--;
}
int Precedence(char c){
    switch(c){
        case '+' : return 0;
        case '-' : return 0;
        case '*' : return 1;
        case '/' : return 1;
        case '^' : return 1;
        default : return 0; 
    }
}
char* infixtoPostfix(char* str){
	char *res = (char*)malloc(sizeof(char)*1000);
	int cnt = 0;
    for(char* curr = str;(*curr)!='\0';++curr){
        if((*curr)=='(') push(*curr);
        else if(*curr==')'){
			while((size>0)&&(top()!='(')){
				res[cnt++] = top();
				res[cnt++] = ' ';
				pop();
			}
			if(top()=='(') pop();
		}
		else if(isoperator(*curr)){
			while((size>0)&&(top()!='(')&&(Precedence(*curr)>Precedence(top()))){
				res[cnt++] = top();
				res[cnt++] = ' ';
				pop();
			}
			push(*curr);
		}
		else{
			res[cnt++]=*curr;
			res[cnt++] = ' ';
		}
	}
	while(size>0){
		res[cnt++] = top();
		res[cnt++] = ' ';
		pop();
	}
	res[cnt++] = '\0';
    return res;
}
void Print(char* str){
	fprintf(fout,"%s\n",str);
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
    char ch,*instr = (char*)malloc(sizeof(char)*1000);
    while(!feof(fin)){
        fscanf(fin,"%[^\n]s",instr);
        instr = RemoveSpace(instr);
        // Print(instr);
		instr = infixtoPostfix(instr);
		Print(instr);
        while(((ch=fgetc(fin))!='\n') && (!feof(fin))) ;
    }
}