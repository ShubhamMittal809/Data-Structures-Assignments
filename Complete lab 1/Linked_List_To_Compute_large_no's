#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
	struct Node* prev;
}nodea;

typedef struct list
{
	int a;
	struct list *link;
}nodeb;

int find(nodea* head , char s[])
{	
	int n = strlen(s);	
	nodea* temp1=head;
	
	if(temp1==NULL)
		return 0;	
	
	int numOfNodes=1;
	
	while(temp1->next != NULL)
	{
		temp1 = temp1->next;
		numOfNodes++;
	}
	
	if(n > numOfNodes)
	{
		return 0;
	}
	
	else
	{	
		temp1=head;
		int count =0;
		while(temp1 != NULL)
		{  	
			//printf(" testing1 ");
			int t=n;	
			int flag=0;
			//printf("first char is %d second is %d ",s[0]-'0',temp1->data);
			if(temp1->data == s[0]-'0')
			{	
				//printf(" testing2 ");
				t--;
				
				nodea* temp2 = temp1->next ;
				int ind=1;
				while(t>0)
				{	
					//printf(" check = %d" , temp2->data ) ;				
					if(temp2==NULL)
					{
						//printf(" testingnew " ) ;
				 		flag=1;
				 		break;
					}
				
					if(temp2->data != s[ind++]-'0')
					{
						//printf(" testing2 ");
					 	flag=1;
					 	break;
					}
					temp2 = temp2->next ;
					t-- ;
					//printf(" t = %d\n ", t);
				}
			
			/*if(flag == 1)
				continue*/
		
				if(t==0)
					count++;			
			}			
			temp1 = temp1->next ;				
		}	
				
		return count;
		
	}			
}


void fact(int number,char s[])
{
	int carry;
	int i,a,b,d,e,f,h,j=0;
	nodea *head,*new,*tail,*temp;
	head=new=tail=temp=NULL;
	tail=(nodea*)malloc(sizeof(nodea));
	head=temp=tail;	
	tail->next=NULL; 
	tail->prev=NULL;
	tail->data=1; 
	
	/*
	 as number is non-negative.it can be 0 too.if so following lines included
	if(number == 0)
	{	if (strlen(s)==1 && s[0]=='0')  //IMPORTANT CORNER CASE. Taking 0^0 = 0 has 1 trailing
		printf(" 1 1 0 \n");
		
		else
		printf(" 1 0 0 \n");
		
		return ;		
	}
	*/
	
	for(i=1;i<=number;i++)  //storing ans say 720 as 7->2->0 where 7 is head and 2 is tail
	{	
		b=i; 
		for(j=1;j<=b;j++)
		{
								
			while(tail)
			{
				a=tail->data;
				carry=a*b;
				d=carry%10;  
				carry=carry/10;
				tail->data=d;
				while(carry)
				{
					if(tail->prev==NULL)
					{
						new=(nodea*)malloc(sizeof(nodea)) ;
						tail->prev=new ;
						head = new ;
						new->next = tail ;
						tail=tail->prev ;
						d = carry%10 ;
						carry=carry/10 ;
						tail->data = d ;
						tail->prev = NULL ;
					}				
					else if(tail->prev!=NULL)
					{
						tail=tail->prev;
						e = tail->data;
						f = b*e;
						carry = f+carry;
						d = carry%10; 
						carry = carry/10;
						tail->data=d;
					}
				}
				tail = tail->prev;
			}
			tail = temp;
		}
		
	}	
	
	while(tail->data == 0)
	{
		h++;
		tail = tail->prev;
	}
	printf("%d ",h);
	
	int count = find(head,s);
    printf("%d ",count) ;
    
    
	while(head)
	{
		printf("%d",head->data);
		head = head->next;
	}
	
	printf("\n");   
    
} 

int main()
{
	int t,y,z,i;
	int c=0,p=1;
	nodeb *head,*temp,*new;
	head=temp=new=NULL;
	printf("enter no of test cases\n");
	scanf("%d", &t);	
	while(t>500 || t<0)
 	{
    	printf("INVALID INPUT! no of test cases should be atleast one and less than 500 only\n");
    	scanf("%d", &t);
 	}


	while(t--)
	{
    	//new=(nodeb*)malloc(sizeof(nodeb));
    	//printf("enter a no btw 1 and 500\n");
    	
    	scanf("%d", &y);
    	
    	int anyLength = 100000;  //though if required error can be printed if length(stringToserach)>999
    	char s[100000];			//implemented for anyLength to make the code generic
		scanf("%s",&s) ;
	    
    	//scanf("%d",&new->a);
    	//y=new->a;
 
		while(y>500||y<0)     //code is working fast enough for atleast upto 500 
		{
    		printf("INVALID INPUT! enter a value between 1 to 500: \n"); 
    		//scanf(" %d", &new->a);    y=new->a; 
		}
		
		fact(y ,s);
		
		/* below code can be iused to keep track of all numbers for which factorial has been called
		if(head==NULL)
		{
			head=new;   head->link=NULL; 
			temp=head; 
			fact(y);
		} 
		else
		{
    		head->link=new;   head=head->link; 
    		head->link=NULL; 
			fact(y);
		}	
 			  
	} 
	
	head=temp;
	*/	
	}
	//return 0;
}
/*
Tested for:

3 1      
5 7
9 941
9 09
7 3    results as expected in pdf

9 22    5 2 21577941222941856209168026828800000
9 222   5 1 21577941222941856209168026828800000

1 2
0 0 1
1 1
0 1 1
3 1234
0 0 108
5 100
5 0 86400000

Declaration : Did it myself

*/



