/*
Declaration : Since I was preparing for internship interviews in which tree is a major topic most of the functions of tree to be implemented were
already known to me.All the below functions have been written on the basis of that preparation which may by-chance resemble from some online sources
from which I prepared.Though still I could not get them correct in first go,so the debugging statements I used have been included in comments which
shows the  Genuity of the code.Also I have tried to use appropriate names for most variables and functions in camelCase. 

*/
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;	
	int ht;
}node;


typedef struct Stack
{
	node** tree;

	int* arr;
	int size;	
	int top; //idex of current element of the arrays tree/arr
			
}stack;

stack* make(int size)
{
	stack* s = (stack*)malloc(sizeof(stack)); //creating pointer to object of the user-def type "stack"
	s->size = size ;
	s->top = -1 ;
	s->arr = (int*) malloc(s->size * sizeof(int)) ;
	return s;	
}

stack* makeNodeStack(int size)
{
	stack* s = (stack*)malloc(sizeof(stack)); //creating pointer to object of the user-def type "stack"
	s->size = size ;
	s->top = -1 ;
	s->tree = (node**) malloc(s->size * sizeof(node)) ;
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

int max(int a,int b)
{
	return (a > b) ? a : b ;
}


void Nodepush(stack* s , node* element)
{
	if(full(s))
	{
		printf("Error : Stack is full! \n") ; 
		return;
	}
	
	s->top += 1;	
	s->tree[s->top] = element;		
}

node* Nodepop(stack* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return NULL ;
	}
	
	node* popped = s->tree[s->top];
	s->top -= 1 ;
	return popped;	
}

node* Nodetop(stack* s)
{
	if(empty(s))
	{
		printf("Error : Stack is empty! \n") ;
		return NULL ;
	}
	return s->tree[s->top] ;	
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


node* newNode(int data)
{
	node* root = (node*)malloc(sizeof(node)) ;
	root->data = data ;
	root->left=NULL;
	root->right= NULL ;
	root->ht = 1 ;
	return root;
}

node* insertBST(node* root,int data)
{
	if(root==NULL)
	{
		return newNode(data);
		
	}
	
	else if(data==root->data)
	 	root->left = insertBST(root->left,data);
	 	
	else if(data < root->data)
	{
		root->left = insertBST(root->left,data);
	}
	
	else if(data > root->data)
	{
		root->right = insertBST(root->right , data) ;
	}
		
	return root;
}

int ht(node* root)
{
	if(root==NULL)
	return 0;
	
	else
	return root->ht ;
	
}

node* rRotation(node* root)
{
	node* leftchild = root->left;
	node* lchildRsubtree = leftchild->right ;
	
	leftchild->right = root;
	root->left = lchildRsubtree;
	
	root->ht = 1 + max(ht(root->left) , ht(root->right) ) ; //this must be updated first then leftchilds ht as root has become child of its leftchild
	leftchild->ht = 1 + max(ht(leftchild->left) , ht(leftchild->right) ) ;
	
	return leftchild ;	
}

node* lRotation(node* root)  //just replace all left by right here and vice versa to rRotation
{
	node* rightchild = root->right ;
	node* rchildLsubtree = rightchild->left ;
	
	rightchild->left = root;
	root->right = rchildLsubtree;
	
	root->ht = 1 + max(ht(root->left) , ht(root->right) ) ; //this must be updated first then leftchilds ht as root has become child of its leftchild
	rightchild->ht = 1 + max(ht(rightchild->left) , ht(rightchild->right) ) ;
	
	return rightchild ;	
}




int getBFactor(node* root)
{
	if(root==NULL)
	 return 0;
	
	else
	return ht(root->left) - ht(root->right) ; 
	
}

node* insertAVL(node* root,int data)
{
	if(root==NULL)
	{
		return newNode(data);
		
	}
	
	else if(data==root->data)
	 	root->left = insertAVL(root->left,data);
	 	
	else if(data < root->data)
	{
		root->left = insertAVL(root->left,data);
	}
	
	else if(data > root->data)
	{
		root->right = insertAVL(root->right , data) ;
	}
	
	int a = ht(root->left) ;
	int b = ht(root->right)  ;
	root->ht = 1 + max(a,b) ;  //to update ht variable of this ancestor
	
	int BFactor = getBFactor(root) ;
	
	if(BFactor < -1 && data > root->right->data)
	{
		return lRotation(root) ; //right right case
	}
	
	if(BFactor>1 && data < root->left->data)  //bfactor>1 LR or LL case
	{
		return rRotation(root);  //left left case
	}
	
	if(BFactor > 1 && data > root->left->data )
	{
		root->left = lRotation(root->left) ;  //left right case.first make left rotaion at root->left then right rotation
		return rRotation(root); 
	}
	
	if(BFactor < -1 && data < root->right->data)
	{
		root->right = rRotation(root->right) ;
		return lRotation(root) ; //right left case.first make right rotaion at root->right then left rotation
	}
	
	return root;
}


node* delBST(node* root, int data)   //I am replacing node with two children by its inorder predecessor.though inorder succesor could also be used
{
	if(root==NULL)
	{
		printf("tree is empty!\n") ;	
		return root;
	}
	
	if(data<root->data) 
	{
		root->left = delBST(root->left,data) ;
	}
	
	else if(data>root->data) 
	{
		root->right = delBST(root->right,data) ;
	}
	
	
	else 
	{
		if(!root->left && !root->right)
		{
			free(root) ;
			return NULL;
		}
		
	    else if(root->left && !root->right)
	    {
	    	node* temp = root->left;	    	
	    	free(root) ;
	    	return temp;
		}
		
		else if(root->right && !root->left)
		{
			node* temp = root->right;	    	
	    	free(root) ;
	    	return temp;
		}
		
		else		
		{
			node* temp = root->left;
			while(temp && temp->right!=NULL)
			{
				temp =temp->right;
			}
			
			root->data = temp->data ;
			//free(temp)  This is wrong;
			root->left  = delBST(root->left,temp->data) ; //Alert in this line
		}
				
	}	
	return root;		
}


node* delAVL(node* root, int data)   //I am replacing node with two children by its inorder predecessor.though inorder succesor could also be used
{
	if(root==NULL)
	{
		printf("tree is empty!\n") ;	
		return root;
	}
	
	if(data<root->data) 
	{
		root->left = delBST(root->left,data) ;
	}
	
	else if(data>root->data) 
	{
		root->right = delBST(root->right,data) ;
	}
	
	
	else 
	{
		if(!root->left && !root->right)
		{
			free(root) ;
			return NULL;
		}
		
	    else if(root->left && !root->right)
	    {
	    	node* temp = root->left;	    	
	    	free(root) ;
	    	return temp;
		}
		
		else if(root->right&& !root->left)
		{
			node* temp = root->right;	    	
	    	free(root) ;
	    	return temp;
		}
		
		else		
		{
			node* temp = root->left;
			while(temp && temp->right!=NULL)
			{
				temp =temp->right;
			}
			
			root->data = temp->data ;
			//free(temp)  This is wrong;
			root->left  = delBST(root->left,temp->data) ; //Alert in this line
		}
				
	}
	
	int a = ht(root->left) ;
	int b = ht(root->right) ;
	root->ht = 1 + max(a,b) ;
	
	
	int BFactor = getBFactor(root) ; //to check whther this node has become unbalanced
	
	if(BFactor < -1 && getBFactor(root->right) <1 ) //RR case
	{
		return lRotation(root) ;
	}
	
	if(BFactor < -1 && getBFactor(root->right) > 0 ) //RL case
	{
		root->right = rRotation(root->right) ;
		return lRotation(root) ;
	}
	
	
	if(BFactor > 1 && getBFactor(root->left) > -1 )  //LL case
		return rRotation(root) ;
	
	if(BFactor > 1 && getBFactor(root->left) < 0 )  //LR case
	{	
		root->left = lRotation(root->left)	;
		return rRotation(root) ;
	}
			
	return root;		
}


int search(node* root, int x)
{
	if(root == NULL)
	return 0;
	
	if(root->data == x)
	{
		return 1;
	}
	
	else if(x < root->data)
	{
		return search(root->left , x) ;
	}
	
	//else if(x > root->data)
	//{
		return search(root->right , x) ;
	//}	
}

int NumOfLeaf(node* root)
{
	if(root==NULL)
	 return 0;
	 
	else if(!root->left && !root->right)
	{
	 	return 1;
	}
	
	//else
	//{
		return NumOfLeaf(root->left)+NumOfLeaf(root->right) ;
	//}	
}

int NumOfNodes(node* root)
{
	if(root==NULL)
	 return 0;
	 
	else if(!root->left && !root->right)
	{
	 	return 1;
	}
	
	//else
	//{
		return (NumOfNodes(root->left) + NumOfNodes(root->right) + 1); //only difference from NumOfleaf is the "+1"
	//}	
}

void IterativePreOrder(node *root)
{
	
	stack* st = makeNodeStack(10000) ; //here stack of nodes needed
	Nodepush(st, root);
	
	while(!empty(st))
	{
		node* cur= Nodetop(st) ;
		printf("%d ", cur->data) ;
		Nodepop(st) ;
		
		if(cur->right)
		{
			Nodepush(st, cur->right) ;
		}
		if(cur->left)  //not carefully here it will not be 'else if' but a separate 'if'
		{
			Nodepush(st, cur->left) ;
		}	
		
	}	
}


void InOrder(node* root)
{
	//printf("reaching here\n") ;
	if(root==NULL)
		return ;
	
	InOrder(root->left);
	printf("%d ",root->data);
	InOrder(root->right) ;			
}

void PostOrder(node* root)
{
	//printf("reaching here\n") ;
	if(root==NULL)
		return ;
	
	PostOrder(root->left);	
	PostOrder(root->right) ;
	printf("%d ",root->data);			
}

void PrintLevel(node* root, int i)
{
	if(root==NULL)
	{
		return ;
	}
	
	if(i==0)
	return ;
	
	if(i==1)
	{
		printf("%d " ,root->data ) ;
		return;
	}

	else if(i>1)  //wrting else will not work as level may become negative too
	{
		PrintLevel(root->left,i-1);
		PrintLevel(root->right,i-1);
	}
	
}

int Height(node* root)
{
	if(root==NULL)
		return 0;
	
	else
	{
		int lh = Height(root->left) ;
		int rh = Height(root->right)  ;
		return ( 1 + max( lh,rh ) );  //max(Height(root->left),Height(root->left)) + 1 was giving error
		
	}
}

void LevelOrder(node* root)
{	
	/*queue<node*> q;    // O(n) level order *****Missing C++ :\ *****	
	q.push(root) ;	
	while(!q.empty())
	{
		node* cur = q.top();
		q.pop() ;
		
		printf("%d",cur->data) ;
		
		if(cur->left)
		{
			q.push(cur->left) ;
		}
		
		if(cur->right)
		{
			q.push(cur->right) ;
		}		
	}*/
	
	
	//O(n^2)
	int h = Height(root) ;
	int i;
	for( i=1;i<=h; i++)
	{
		PrintLevel(root,i);		
		
	}
	
}

int getWid(node* root , int i)
{
	//printf(" in getWidth function \n")  ;
	if(root == NULL)
	return 0 ;
	
	if(i==1)
	{
		//printf("%d " ,root->data ) ;
		return 1;
	}

	else if(i>1)  //wrting else will not work as level may become negative too
	{	
		//int temp1 = getWid(root->left , i-1) ;
		//int temp2 = getWid(root->right , i-1) ;
		//return (  temp1 + temp2 );
		return (getWid(root->left , i-1) + getWid(root->right , i-1) ) ;
	}
	
}

int Width(node* root)
{
	//printf(" in Width function \n") ;
	int MaxWidth=0;
	//int wid;
	int h = Height(root) ;
	//printf("h= %d \n", h) ;
	int i;
	for( i=1 ; i<=h ;i++)
	{		
		/*wid = getWid(root,i) ;
		if(wid > MaxWidth)
		{
			MaxWidth = wid ;
		} */
		if(getWid(root,i) > MaxWidth )
		{
			MaxWidth = getWid(root,i) ;
		}
				
	}
	
	return MaxWidth ;
	
}

node* PointerToGivenNode(node* root , int s) //this function is being used when we already know s exist from Route function.so case of non existence not handled
{
	node* temp = root;
	if(root->data == s)
	{
		temp = root;
		return temp;
	}
	
	else if(s<root->data)
	{
		temp = PointerToGivenNode(root->left,s) ;
	}
	
	else if(s>root->data)
	{
		temp = PointerToGivenNode(root->right,s) ;
	}
	return temp ;
	
}

int RouteUtil(node* root , stack** st, int d)
{
	if(!root)
	return 0;
	
	push(*st, root->data) ;
	
	if(root->data == d)
	return 1;
	
	if(RouteUtil(root->left, st, d)|| RouteUtil(root->right , st, d) )
	return 1 ;
	
	pop(*st) ;
	return 0;
	
}


void Route(node* root, int s ,int d)
{
	if(root==NULL)
	{
		printf("Unreachable ") ;
		return ;
	}
	
	if(!search(root,s)){
		printf("Source does not exist ");
		return ;
	}
	else if(!search(root,d)){
		printf("Destination doen't exists ");
		return ;
	}
	
	else if(s==d)
	{
		printf("%d Reached %d ",s,d) ;
	}
	
	else
	{
		node *source = PointerToGivenNode(root,s) ;
		stack* st = make(10000);
		
		if(RouteUtil(source, &st, d))
		{
			int A[10000], l=0 ;
			while(!empty(st))
			{
				A[l++] = top(st) ;
				pop(st) ; 					
			}
			
			printf("%d ", A[l-1]) ;
			int j;
			for( j=l-2;j>=0;j--)
			{	
				if(A[j]<A[j+1])
				{
					printf("Left ");
				}
				else
				{
					printf("Right ");
				}
				printf("%d ",A[j]) ;
			}
			printf("Reached %d",d) ;
		}
		
		else					
		{
			printf("Unreachable ") ;
		}
		
	} 
	
}

node* LCA(node* root, int first , int second)
{
	if(root==NULL)
	return NULL;	
		
			
	else if(root->data < first && root->data < second )
	{
		return LCA(root->right, first ,second) ;
	}
	
	else if(root->data > first && root->data > second )
	{
		return LCA(root->left, first ,second) ;
	}
	
	//else if(root->data>first && root->data<second)   **understood
	//{
		return root ;
	//}	
}


int diameter(node* root, int* ht)
{
	if(root==NULL)
	{
		*ht = 0;
		return 0;
	}
	
	int lh=0, rh =0 ;
	//int lDia=0, rDia=0 ;  //this decleration will aslo work
	
	
	int lDia = diameter(root->left ,&lh) ;  //this also just to be sure
	int rDia = diameter(root->right , &rh) ;
	*ht = max(lh , rh) + 1 ; 
	return max(lh+rh+1 , max(lDia,rDia)) ;
	
}

void rightboundary(node* rightRoot, int* sum)
{
	if(rightRoot == NULL)
		return;	
	
	if(rightRoot->right)
	{
		*sum = *sum + rightRoot->data ;
		//printf("%d", root->data) ;
		rightboundary(rightRoot->right, sum) ;
	}
	
	else if(rightRoot->left)
	{
			*sum = *sum + rightRoot->data ;
			//printf("%d ", rightRoot->data) ;
			rightboundary(rightRoot->left,sum) ;	
	}
	
}

void leftboundary(node* leftRoot, int* sum)
{
	if(leftRoot==NULL)
		return;
		
	if(leftRoot->left)
	{
		leftboundary(leftRoot->left , sum) ;
		//printf("%d", root->data) ;
		*sum = *sum + leftRoot->data ;
	}
	
	else if(leftRoot->right)
	{
		leftboundary(leftRoot->right,sum) ;
		//printf("%d", leftRoot->data) ;
		*sum = *sum + leftRoot->data ;
	}	
		
}


void leaves( node* root , int *sum)
{
	if(root==NULL)
		return;
	
	leaves(root->right, sum) ;  //to print leaves from right to left
	
	if(!(root->right) && !(root->left))
	{
		//printf("%d ",root->data) ;
		*sum = *sum + root->data ;
	}
	
	leaves(root->left, sum) ;
	
}


int Perimeter(node* root)
{		           //clockwise
	int sum = 0 ;
	if(root==NULL)
	return 0;
	
	//printf("%d " ,root->data) ; //printing root separately
	sum = sum + root->data ;
	
	rightboundary(root->right, &sum) ;// to get right boundary in top down way
	leaves(root->right, &sum) ; // to get leaves of right subtree
	leaves(root->left,&sum) ;  // to get leaves of left subtree
	leftboundary(root->left,&sum) ; //to get leaves in bottom-up way
	return sum;
}




int main()
{
	int q;
	//printf("Enter no of queries:\n") ;
	scanf("%d", &q) ;
	char *s;
	
	node* root=NULL;
	node* BSTroot= NULL ;
	node* AVLroot=NULL;
	int flag=0;
	while(q--)
	{		
		/* since input can also be taken by fgets and then traverse the obtained string and extract the numbers
		using no = no*10 + i where i is variable of iteation until s[i]=" ". After which again start no from no=0.If encounter "-" do i= i+1 extra.and then same
		 */
	
		fflush(stdin) ; //without this below scanf will treat next line as input!
		char s0;
		scanf("%c", &s0) ;
			
		
		if(s0 == 'T' )
		{	
			flag=0;
			int i=0,size,A[10000];
			char temp; 
			do{
	  			scanf("%d%c", &A[i++], &temp); 
	  		 
	  		} while(temp!= '\n');
		
			size=i; 
			//printf("size=%d \n", size) ;
			
			/*for(i=0;i<size;i++){ 
			printf("A[%d]= %d ",i, A[i]) ;
			}*/
			node* tempRoot = BSTroot;
			BSTroot=NULL;
			free(tempRoot) ;
			BSTroot = insertBST(BSTroot,A[0]) ;
			
			
 			for(i=1;i<size;i++){ 
  				if(A[i]>0 )
				  { 
				    BSTroot = insertBST(BSTroot,A[i]) ; 
				  }
				  
				else 
				{			
					BSTroot=delBST(BSTroot,abs(A[i])) ;  	
				}
  			} 			
  			
		}
		
		else if(s0 == 'H')
		{
			node* tempRoot = AVLroot;
			AVLroot=NULL;
			free(tempRoot) ;
			flag=1 ;			
			int i=0,size,A[10000];
			char temp; 
			do{
	  			scanf("%d%c", &A[i++], &temp); 
	  		 
	  		} while(temp!= '\n');
		
			size=i; 
			//printf("size=%d \n", size) ;
			
 			for(i=0;i<size;i++){ 
  				if(A[i]>0 )
				  {
				    AVLroot=insertAVL(AVLroot,A[i]) ;
				  }
				  
				else 
				{			
					AVLroot=delAVL(AVLroot,abs(A[i])) ;  	
				}
  			} 			
  			
			
		}
		
		
		else if(s0 == 'A')
		{
			int i=0,size,A[10000];
			char temp; 
			do{
	  			scanf("%d%c", &A[i++], &temp); 
	  		 
	  		} while(temp!= '\n');
		
			size=i; 
			//printf("size=%d \n", size) ;
			
			if(flag==0)
			{			
 				for(i=0;i<size;i++){ 
  				if(A[i]>0 ){				  	
				    BSTroot=insertBST(BSTroot,A[i]) ;
				}
				  
				  else{
				 	; //do nothing
				}	
				  			
  				}
  			}
  			
  			else if(flag==1){
  				for(i=0;i<size;i++){ 
  					if(A[i]>0 ){				  	
				   		 AVLroot=insertAVL(AVLroot,A[i]) ;
					}	
									  
					else{
				 		; //do nothing
					}	
				  			
  				}  				
  				
			}		
		
		}
		
		else if(s0=='U'){
			int i=0,size,A[10000];
			char temp; 
			do{
	  			scanf("%d%c", &A[i++], &temp); 
	  		 
	  		} while(temp!= '\n');
		
			size=i; 
			//printf("size=%d \n", size) ;
			
			if(flag==0)
			{			
 				for(i=0;i<size;i++){ 
  				if(A[i]>0 ){				  	
				    BSTroot=delBST(BSTroot,A[i]) ;
				}
				  
				  else{
				 	; //do nothing
				}	
				  			
  				}
  			}
  			
  			else if(flag==1){
  				for(i=0;i<size;i++){ 
  					if(A[i]>0 ){				  	
				   		AVLroot = delAVL(AVLroot,A[i]) ;
					}	
									  
					else{
				 		; //do nothing
					}	
				  			
  				}  				
  				
			}		
			
		}
		
		else if(s0=='F')
		{
			int x;
			scanf("%d",&x);
			
			if(x<0)
			{
				printf("No\n") ;
			}
			
			else
			{
				if(flag==0)
				{
					search(BSTroot,x) ? printf("Yes\n") : printf("No\n") ;
				}
				
				else if(flag==1)
				{
					search(AVLroot,x) ? printf("Yes\n") : printf("No\n") ;
				}			
				
			}
			
			continue;			
		}
		
		else if(s0=='N')
		{
			if(flag==0)
	   		printf("%d\n", NumOfNodes(BSTroot)) ;
	   		
	   		else if(flag==1)
	   		printf("%d\n", NumOfNodes(AVLroot)) ;
	   		
	   		continue;
		}
		
		else if(s0=='Q')
		{
			if(flag==0)
	   		printf("%d\n", NumOfLeaf(BSTroot)) ;
	   		
	   		else if(flag==1)
	   		printf("%d\n", NumOfLeaf(AVLroot)) ;
	   		
	   		continue;
		}
		
		
		else if(s0 == 'P')
		{   
			if(flag==0){
			IterativePreOrder(BSTroot);
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			IterativePreOrder(AVLroot);
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'I')
		{   
			if(flag==0){
			InOrder(BSTroot);
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			InOrder(AVLroot);
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'S')
		{   
			if(flag==0){
			PostOrder(BSTroot);
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			PostOrder(AVLroot);
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'L')
		{   
			if(flag==0){
			LevelOrder(BSTroot);  
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			LevelOrder(AVLroot);
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'D')
		{   
			if(flag==0){
			printf("%d ", Height(BSTroot) );  
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			printf("%d ", Height(AVLroot) );
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'W')
		{   
			if(flag==0){
			printf("%d ", Width(BSTroot) ); 
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			printf("%d ", Width(AVLroot) ); 
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'C')   
		{   
			int first,second;
			scanf("%d %d",&first, &second) ; 
			if(flag==0){
				if(!search(BSTroot,first) || !search(BSTroot,second) )
				{
					printf("-1 ")	;
				}	
				
				else if(first== second)
				{
					printf("%d ",first) ;
				}
				
				else{
				
					printf("%d ", LCA(BSTroot,first,second)->data) ;  
				}
				printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			
			if(!search(AVLroot,first) || !search(AVLroot,second) )
				{
					printf("-1 ")	;
				}	
				
				else if(first==second)
				{
					printf("%d ",first) ;
				}
				
				else{
				
					printf("%d ", LCA(AVLroot,first,second)->data) ;  
				}
				printf("\n") ;	
			continue ;
			}	
		}
		
		else if(s0 == 'R')   
		{   int i,j ; scanf("%d %d",&i, &j);
			if(flag==0){
			Route(BSTroot,i,j);  
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			Route(AVLroot,i,j);
			printf("\n") ;	
			continue ;	
			}			
		}
		
		else if(s0 == 'X')   // see note for edge cases
		{   
			if(flag==0){
			int ht =0;	
			printf("%d",diameter(BSTroot, &ht));  
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			int ht = 0;	
			printf("%d",diameter(AVLroot, &ht));
			printf("\n") ;	
			continue ;	
			}			
		}
		
		
		else if(s0 == 'Y')   //as per the instructor we just eed to print sum of all nodes in the perimeter
		{   
			if(flag==0){
			printf("%d ", Perimeter(BSTroot) ) ;  
			printf("\n") ;	
			continue ;
			}
			
			else if(flag==1){
			printf("%d ", Perimeter(AVLroot) ) ;
			printf("\n") ;	
			continue ;	
			}			
		}	
		
		
	}		
		
}


/*  TESTED FOR THE FOLLOWING BST AND AVL. ALL FUNCTIONS WORKED AS DESIRED

20

below BST

  			8	
           /  \ 
          3   10 
        /  \     \ 
       1    6     14 
          /  \    /
        4    7   13



T 8 3 1 6 4 7 10 14 13
Q
4
N
9
L
8 3 10 1 6 14 4 7 13
D
4
R 8 7
8 Left 3 Right 6 Right 7 Reached 7
X
7
Y
60
T 8 3 10
I
3 8 10
L
8 3 10


below AVL tree

			 9 
           /  \ 
          3   10 
        /  \     \ 
       2    5     11 
      /    /  \ 
     1   4    6 



H 9 5 10 2 6 11 1 3 4                         
L
9 3 10 2 5 11 1 4 6
F 5
Yes
F 87
No
Q
4
N
9
P
9 3 2 1 5 4 6 10 11
I
1 2 3 4 5 6 9 10 11
X
6
Y
46
R 10 1
Unreachable
R 3 1
3 Left 2 Left 1 Reached 1


*/
		
	
	


