#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

typedef struct Stack
{
	unsigned long long int* arr;
	unsigned long long int size;	
	unsigned long long int top;		
}stacK;

stacK* make(unsigned long long int size)
{
	stacK* s = (stacK*)malloc(sizeof(stacK)); //creating pointer to object of the user-def type "stack"
	s->size = size ;
	s->top = -1 ;
	s->arr = (unsigned long long int*) malloc(s->size * sizeof(unsigned long long int)) ;
	return s;	
}

unsigned long long int full(stacK* s)
{
	return (s->top == s->size -1 ? 1 : 0)  ; 
}

unsigned long long int empty(stacK* s)
{
	return (s->top == -1 ? 1 : 0)  ;
}	

void push(stacK* s , unsigned long long int element)
{
	if(full(s))
	{
		printf("Error : Stack is full! \n") ; 
		return;
	}
	
	s->top += 1;	
	s->arr[s->top] = element;		
}

unsigned long long int pop(stacK* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return INT_MIN ;
	}
	
	unsigned long long int popped = s->arr[s->top];
	s->top -= 1 ;
	return popped;	
}

unsigned long long int top(stacK* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return INT_MIN ;
	}
	return s->arr[s->top] ;	
}





unsigned long long int catalan(unsigned long long int n)
{
	unsigned long long int ans = 1;
	unsigned long long int i=0 ;
	/*for(i=1; i<=n-1 ; i++ )
	{
		ans = ans*(n+1+i) ;		evaluating (n+2)(n+3)(n+4)(n+5).. / 1.2.3.4.5 ....		
	}
	
	for(i=1; i<=n-1 ; i++ )
	{
		ans = ans/(i+1) ;
	} This piece of code will cause intger overflow better calculate in rev order ie 2n*(2n-1)*(2n-2)*(2n-3)*(2n-4) / 1.2.3.4 ...
	  ie multiply and divide simultaneously by denominator terms as their multipple would have already occured before their appearance in numerator */
	//cout<< "ans= "<< ans <<endl ;
	
	for(i=0; i <= n-2 ; i++ )   //giving catalan no of upto n=100
	{
		ans = ans*(2*n-i) ;		
		ans /= (i+1) ;	
	}
	ans = ans/n ;
	
	return ans;
	
}

void kthPermuationUtil(int n , int & open , int & close , unsigned long long int *c,unsigned long long int k)
{
	static stack<int> st;
	static vector <int> output(n , 0);
	 //open and close denotes pushing and poping an element into/outof stack respectively in analogy to open and close
				//bracket 
	
	if(open==n && close == n)
	{   
			*c = *c - 1 ;
		
		if(*c == k-1)
	    {
			for(int i=0 ; i<n ; i++)
			{
			cout << output[i] << " " ;
			
			}
			
		cout<<"\n" ;
		
		}
	}
	
	else
	{
		if(open < n )
		{			
			st.push(open + 1) ;
			open ++ ;
			kthPermuationUtil(n , open , close , c, k) ;
			st.pop() ;
			open -- ;			
		}
		
		if(open > close)
		{			
			int tmp = st.top();
			output[close] = tmp;
			st.pop() ;
			close ++;
			kthPermuationUtil(n, open , close , c, k);
			st.push(tmp) ;
			close -- ;					
		}		
	}	
}

void kthPermuation(int n,unsigned long long int *c , unsigned long long int k)
{
	 int open = 0;
	 int close= 0;
	kthPermuationUtil(n, open , close , c, k) ;	
}


int main()
{
	int t;
	scanf("%d",&t) ;
	while(t--)
	{
		unsigned long long int n,k ;		
		scanf("%d %d",&n ,&k) ;
		unsigned long long int *c ;		
		unsigned long long int d;
		 d = catalan(n) ;
		c = &d;
		cout<< d<<" " ;
				
		kthPermuation(n,c,k);
	
	}
	
	return 0;
}
