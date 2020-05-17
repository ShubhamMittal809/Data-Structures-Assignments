#include<stdio.h>
#include<stdlib.h>
#include <ctype.h> 
#include<string.h>
typedef struct Stack
{
	int* arr;
	int size;	
	int top;		
}stack;

stack* make(int size)
{
	stack* s = (stack*)malloc(sizeof(stack)); //creating pointer to object of the user-def type "stack"
	s->size = size ;
	s->top = -1 ;
	s->arr = (int*) malloc(s->size * sizeof(int)) ;
	return s;	
}

int full(stack* s)
{
	return (s->top == s->size -1 ? 1 : 0)  ; 
}

int empty(stack* s)
{
	return (s->top == -1 ? 1 : 0)  ;
}	

void push(stack* s , int element)
{
	if(full(s))
	{
		printf("Error : Stack is full! \n") ; 
		return;
	}
	
	s->top += 1;	
	s->arr[s->top] = element;		
}

int pop(stack* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return INT_MIN ;
	}
	
	int popped = s->arr[s->top];
	s->top -= 1 ;
	return popped;	
}

int top(stack* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return INT_MIN ;
	}
	return s->arr[s->top] ;	
}

int map(char c[2])
{       
		//printf("  c = %s \n",c) ;
		if(strcmp(c,"*")==0)
		return 1000;
		
		else if(strcmp(c,"/")==0)
		return 1001;
		
		else if(strcmp(c,"%")==0)
		return 1002;
		
		else if(strcmp(c,"+")==0)
		return 1003;
		
		else if(strcmp(c,"-")==0)
		return 1004;		
		
		else if(strcmp(c,"<<")==0)
		return 1005;
		
		else if(strcmp(c,">>")==0)
		return 1006;
		
		else if(strcmp(c,"<")==0)
		return 1007;
		
		else if(strcmp(c,"<=")==0)
		return 1008;
		
		else if(strcmp(c,">")==0)
		return 1009;
		
		else if(strcmp(c,">=")==0)
		return 1010;
		
		else if(strcmp(c,"==")==0)
		return 1011;
		
		else if(strcmp(c,"!=")==0)
		return 1012;
		
		else if(strcmp(c,"&")==0)
		return 1013;
		
		else if(strcmp(c,"^")==0)
		return 1014;
		
		else if(strcmp(c,"|")==0)
		return 1015;
}

int eval(int a,int b ,int op)
{
	switch(op)
	{
		case 1000 : return (a*b) ;
		case 1001 : return (a/b) ;
		case 1002 : return (a%b) ;
		case 1003 : return (a+b) ;	
		case 1004 : return (a-b) ;	
		case 1005 : return (a<<b) ;	
		case 1006 : return (a>>b) ;	
		case 1007 : return (a<b) ;	
		case 1008 : return (a<=b) ;	
		case 1009 : return (a>b) ;	
		case 1010 : return (a>=b) ;	
		case 1011 : return (a==b) ;	
		case 1012 : return (a!=b) ;	
		case 1013 : return (a&b) ;	
		case 1014 : return (a^b) ;	
		case 1015 : return (a|b) ;
	}	
	
}

int preced(int c)
{
	//printf("%d",c) ;
	if(c== 1015 )
	return 1;
	
	else if(c== 1014 )
	return 2;
		
	else if(c== 1013 )
	return 3;
	
	else if(c==1012 || c==1011 )
	return 4;

	else if(c==1010 || c==1009 || c==1008 || c==1007)
	return 5;
	
	else if(c==1006 || c== 1005 )
	return 6;
	
	else if(c==1004 || c==1003 )
	{
		
		return 7;
		
	}
	
	else if(c==1002||1001||1000 )
	return 8;
	
	return 0;	
}

int compute(char s[] , int n)
{
	stack* operands = make(n);
	stack* operators = make(n) ;
	int i=0;
	int k=0;
	if(s[0] =='-')
	{
		k=1;
	}
	
	for(i=k; i<=n-4 ; i++)
	{
		
		int flag=0;	
		if(s[i] == ' ')
		continue;
		
		/*else if(s[i]=="-" && isdigit(s[i+1]) )
		{
			continue;
		}*/
			
		else if(isdigit(s[i]))
		{
			int number =0;
			
			if(i>0 && s[i-1]=='-')
			{
				flag = 1;
			}
			
			while(i<n-1 && isdigit(s[i]))
			{	
				number = number*10 + s[i]-'0' ;
				i++ ; 
			}
			
			if(flag==1)
			number = -number;
			//printf(" testing ");
			push(operands,number ) ;						
		}
		
		else if(s[i] == ' ')
		continue;		
		
		else if(!isdigit(s[i]) && s[i] !=' ' && s[i] !='#') // current element is an operator
		{   char oparr[3]={0} ;
			
			oparr[0] = s[i];
			if(s[i+1] != ' ' && !isdigit(s[i+1]) )
			{			
			oparr[1] = s[i+1];
			//printf(" testing ");
			  i++;
			}
			//printf("* %s \n",oparr) ;
			
			//printf(" oparr = %s ",oparr) ;
			int hashval = map(oparr);
			
			//printf(" i= %d hashval=%d ",i, hashval) ;
			//printf(" hashval = %s ",hashval) ;
			
			while(!empty(operators) && preced(top(operators)) >= preced(hashval))
			{
				int b = top(operands) ;
				//printf(" testing ");
				pop(operands) ;
				
				int a = top(operands) ;
				pop(operands) ;
				
				int op = top(operators) ;
				pop(operators) ;	
				
				push(operands,eval(a,b,op)) ;								
			}	
			
			push(operators,hashval) ;
			
		}
		
		
		
	}
	
	while(!empty(operators))
	{
		
		int b = top(operands) ;
		pop(operands) ;
				
		int a = top(operands) ;
		pop(operands) ;
		
		int op = top(operators) ;
		pop(operators) ;				
		push(operands,eval(a,b,op)) ;
			
	}	
		return top(operands) ;
		
}


int main()
{
	int t;
	scanf("%d", &t) ;
	
	while(t--)
	{  
	
		fflush(stdin);		
		char c[200];
		//cin>>s ;
		fgets(c, 200, stdin);
		//printf("%s",c) ;	
		int n=strlen(c);
		//printf("%d",n) ;
		
		int n1=0;
		//new
		while(c[n1] != '#')
		{
			n1++;
		}
		n1= n1+2 ;
		//printf(" n1= %d\n",n1) ;
		
		printf("%d\n",compute(c, n1)) ;	
		//new ends
		
	}		

}






	

