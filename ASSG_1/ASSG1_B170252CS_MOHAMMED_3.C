#include<stdio.h>
#include<stdlib.h>
FILE *fin,*fout;
int Stack[1000];
int size = 0;
int isoperator(char c){
    return ((c == '+') || (c == '-') || (c =='*') || (c == '/') || (c == '^'));
}
void push(int c){
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
int Calculator(int a,int b,char op){
	switch(op){
		case '+' : return a+b; break;
		case '-' : return a-b; break;
		case '*' : return a*b; break;
		case '/' : return a/b; break;
		case '^' : return a^b; break;
	}
	return 0;
}
int evaluatePostfix(char *str){
	for(char *curr=str;(*curr)!='\0';){
		char ch = *curr;
		curr++;
		if((ch<='9')&&(ch>='0')){
			int integer = ch - '0';
			for(;((*curr)!=' ')&&((*curr)!='\0');curr++)
				integer = integer*10 + (*curr-'0');
			push(integer);
			printf("%d ",integer);
			if(*curr!='\0') curr++;
		}
		else{
			int a = top(); pop();
			int b = top(); pop();
			printf("%c ",ch);
			if(*curr!='\0') curr++;
			push(Calculator(b,a,ch));
		}
	}
	printf("\n");
	return top();
}
void Print(int output){
	fprintf(fout,"%d\n",output);
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
    char instr[1000],ch;
    while(!feof(fin)){
        fscanf(fin,"%[^\n]s",instr);
        int output = evaluatePostfix(instr);
		Print(output);
		while(((ch=fgetc(fin))!='\n') && (!feof(fin))) ;
    }
}