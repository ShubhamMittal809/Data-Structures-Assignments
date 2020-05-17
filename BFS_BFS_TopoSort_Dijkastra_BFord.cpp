#include<bits/stdc++.h>
using namespace std;

#define SIZE 40000
int Q[SIZE];
int front=-1,rear=-1;

void enque(int x)
{
	if(front==(rear+1)%SIZE)
	{
		printf("\n queue is full,data not inserted.Try deque operation\n");
	return;
	}

	if(front==-1)
	{
		front=rear=0;
		Q[rear]=x;
	}

	else
	{
		rear=(rear+1)%SIZE;
		Q[rear]=x;
	}
}

int deque()
{
	if(front==-1)
	{
		printf("\nqueue is empty\n");		
	return -1;
	}
	
	else if(front==rear)
	{
		int y=Q[front];
		front=rear=-1;
		return y;
	}
	else
	{
		int y=Q[front];
		front=(front+1)%SIZE;
		return y;
	}
}

void display()
{
	int i;
	if(front==-1)
	printf("\nqueue is empty\n");

	else if(rear>=front)
	{
		for(i=front;i<=rear;i++)
		{
			printf("%d\n",Q[i]);
		}
	}

	else if(rear<front)
	{
		for(i=front;i<SIZE;i++)
		printf("%d\n",Q[i]);

		for(i=0;i<=rear;i++)
		printf("%d\n",Q[i]);

	}

}


void DfsUtil(int i , vector<vector<int>> Graph, int N, int& time, int& treeEdges, int& crossEdges, int& backEdges, int& forwardEdges, int color[],int start[],int finish[],int parent[], int D )
{
	//cout<<"reaching here"<<endl ; working
	color[i] = 1; 
	//*timeptr = *timeptr + 1;
	time++;
	start[i] = time ;
	if(D==1)
	{
	
	for(int j=0; j<N; j++)
	{
		if( Graph[i][j] )
		{	
			if(color[j]==0)
			{			
			treeEdges++;
			parent[j] = i ;
			DfsUtil(j, Graph, N, time, treeEdges, crossEdges, backEdges, forwardEdges, color, start, finish, parent, D ) ;
			}
			
			else
			{
				if(color[j]==1)
				{
					backEdges++;
				}
				else if(color[j]==2 && start[i]<start[j] ) 
				{
					forwardEdges++ ;
				}
				
				else if(color[j]==2 && start[i]>start[j] )
				{
					crossEdges++;
				}
				
			}
		}
	}
	}
	
	else
	{
	for(int j=i+1; j<N; j++)
	{
		if( Graph[i][j] )
		{	
			if(color[j]==0)
			{			
			treeEdges++;
			parent[j] = i ;
			DfsUtil(j, Graph, N, time, treeEdges, crossEdges, backEdges, forwardEdges, color, start, finish, parent, D ) ;
			}			
		}
	}	
	}
	
	color[i] = 2;
	//*timeptr = *timeptr + 1;
	time++;
	finish[i] = time ;	
}

void DFS(vector<vector<int>> Graph,int N, int s, int D,int Edges)
{
	int color[N],parent[N], start[N] , finish[N] ;
	int treeEdges=0,crossEdges=0,backEdges=0,forwardEdges=0;
	for(int i=0;i<N;i++)
	{
		color[i] = 0 ;
		parent[i] = -1;
	}
	int time=0 ;
	//int* timeptr = &time ;
	for(int i=0;i<N;i++)
	{
		if(color[i]==0)
		{			
			DfsUtil(i,Graph,N,time,treeEdges,crossEdges,backEdges,forwardEdges,color,start,finish,parent, D) ;
		}
	}
	if(D==1)
	cout<<finish[s]<<" "<<treeEdges<<" "<<backEdges<<" "<<forwardEdges<<" "<<crossEdges<<endl; 
	
	else if(D==0)
	cout<<finish[s]<<" "<<treeEdges<<" "<<(Edges/2)-treeEdges<<endl;
		
}

void BFS(vector<vector<int>> Graph, int N, int s, int D,int edges)
{
	int color[N],parent[N], start[N] , finish[N], distance[N] ;
	int treeEdges=0,crossEdges=0,backEdges=0,forwardEdges=0;
	for(int i=0; i<N; i++)
	{
		color[i] = 0;
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	
	distance[s] = 0;
	parent[s] = -1;
	color[s] = 1;
	queue<int> q;
	int time=0;
	q.push(s) ;
	time++;
	start[s] = 1;
	if(D==1){
	
	while(!q.empty())
	{
		int i = q.front() ;
		q.pop();
		//start[i] = time;
		for(int j=0; j<N; j++)
		{
			if( Graph[i][j] )
			{	
				if(color[j]==0)
				{			
					treeEdges++;
					parent[j] = i ;
					color[j]=1;  ;
					distance[j] = distance[i] +1 ;
					q.push(j) ;
					time++;					
					start[j]=time;
				}
			
				else
				{
					int a=i , b=j;
					while(distance[b] > distance[a])
					{
						b = parent[b];
					}
					while(distance[b] < distance[a])
					{
						a = parent[a];
					}
					if(a==b)
					{
						backEdges++ ;
					}
					
					else
					{
						crossEdges++ ;
					} 			
				}
			}
		}  
		color[i] = 2 ;
		time++ ;		
		finish[i] = time ;
	}	
	
	int count[N];
	memset(count,0,sizeof(count)) ;
	for(int i=0;i<N;i++)
	{
		count[distance[i]] ++ ;
	}
	
	for(int i=1;i<N;i++)
	{
		if(count[i]!=0)
		cout<<count[i]<<" " ; 
	}
	
	cout<<"0 "<<treeEdges<<" "<<backEdges<<" "<<"0"<<" "<<crossEdges<<endl; 
	}
	
	else if(D==0)
	{
	while(!q.empty())
	{
		int i = q.front() ;
		q.pop();
		//start[i] = time;
		for(int j=0 ; j<N ; j++)
		{
			if( Graph[i][j] && parent[i]!=j )
			{	
				if(color[j]==0)
				{			
					treeEdges++;
					parent[j] = i ;
					color[j]=1;  ;
					distance[j] = distance[i] +1 ;
					q.push(j) ;
					time++;					
					start[j]=time;
				}
			
				
			}
		}  
		color[i] = 2 ;
		time++ ;		
		finish[i] = time ;
	}
	
	int count[N];
	memset(count,0,sizeof(count)) ;
	for(int i=0;i<N;i++)
	{
		count[distance[i]] ++ ;
	}
	
	for(int i=1;i<N;i++)
	{
		if(count[i]!=0)
		cout<<count[i]<<" " ; 
	}	
	cout<<"0 "<<treeEdges<<" "<<(edges/2)-treeEdges<<endl;
	}
		
}

void lexographicTopoSort(int N, vector<vector<int>> Graph, int indegree[] ) //using kahn's algorithm
{
	priority_queue <int,vector<int>,greater<int>> q; 
	for(int i=0;i<N;i++)
	{
		
		if(indegree[i]==0)
		{
			//cout<<"i= " << i <<endl;
			q.push(i);
		}
	}
	
	int count=0;
	vector<int> smallestTopo;
	
	/*for(int i=0 ;i<N;i++)
        {
            for(int j=0 ; j<N;j++)
            {
            	cout<<Graph[i][j]<<" " ;
        	}
        	cout<<endl;
    	}*/
	
	while(!q.empty())
	{
		int temp = q.top();
		q.pop() ;
		smallestTopo.push_back(temp) ;
		
		for(int i=0 ; i<N ; i++  )
		{	
			//cout<<"testing= "<<Graph[temp][i]<<" " ;
			if(Graph[temp][i]== 1 ) //checking if there is an edge from temp to i
			{
			
				indegree[i]--;
			
				if(indegree[i]==0)
				{ 
				q.push(i) ;
				}
			}
		}
		//cout<<endl;
		count++;
		//cout<<"count= "<< count<<" " ;
	}
	
	if(count!=N)
	{
		cout<<"-1"<<endl;
	}
	
	else
	{
		for(int i=0 ; i<N; i++)
		{
			cout<< smallestTopo[i] + 1 << " " ;
		}
		cout<<endl;
	}
	
} 

void Dijkstra(list<pair<int,int>> adj[], int s, int N )
{
	priority_queue< pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>> > q;
	vector<int> distance(N,INT_MAX) ;  //to initialise distances as infinite
	q.push(make_pair(0,s)) ;
	distance[s] = 0 ;
	
	
	
	while(!q.empty())
	{
		//cout<<"reaching here1"<<endl;
		int x = q.top().second ;  //to access 2nd element of the pair ie the vertex with minimum disance present in the queue
		q.pop() ;
		/*for(auto i: adj[x])	
		{
			cout<<" adj of " << x <<"is "<< i.first <<endl;
		}*/
		
		
		
		for(auto i: adj[x])	
		{
		//	cout<<" adj of " << x <<"is "<< i.first <<endl;
			int y = i.first;
			int wt = i.second ;
			
			if(distance[y]>distance[x]+wt)
			{
				distance[y]  = distance[x] + wt ;
				q.push(make_pair(distance[y] , y) ) ;	
			}	
			
		}	
		
	}
	//cout<<"reaching here"<<endl;
	for(int i=0 ; i<N ; i++)
	{
		(distance[i]==INT_MAX) ? cout<<"999999 " : cout<<distance[i]<<" " ;	
	}	
	
	cout<<endl;
	
}

void Bellman(list<pair<int,int>> adj[], int s, int N )
{
	int distance[N] ;
	for(int i=0;i<N;i++ )
	{
		distance[i] = INT_MAX;
	}
	distance[s] = 0;
	
	int change=0;
	
	for(int count=1; count<=N-1; count++ )
	{
		
		for(int i=0; i<N; i++)
		{
			int flag=0;
			for(auto j: adj[i] )
			{
				if(distance[i]!=INT_MAX && (distance[i] + j.second < distance[j.first] ) )
				{
					flag=1;
					distance[j.first]	= distance[i] + j.second ;
					
				}	
			}
			if(flag==1)
			{
				change++ ;
			}	
		}	
		
	}
	
	for(int i=0; i<N; i++)
		{
			for(auto j: adj[i] )
			{
				if( distance[i]!= INT_MAX && distance[i] + j.second < distance[j.first] )
				{
					cout<<"-1"<<endl ;
					return;
				}	
			}	
		}	
	
	for(int i=0 ; i<N ; i++)
	{
		(distance[i]==INT_MAX) ? cout<<"999999 " : cout<<distance[i]<<" " ;	
	}	
	
	
	
	cout<< (N-1) << " " << change << endl;
	
	
	
	
}


int main()
{
	int T; cin>>T;

	while(T--)
	{
    	int Q; cin>>Q;
    	if(Q==1||Q==2||Q==4||Q==5)
    	{
        	int N,D,s; cin>>N>>D>>s;
        	       
        	if(Q==1 || Q==2 )
        	{
           		vector<vector<int>> Graph ;
        		//int indegree[N+1] ;
        		for(int i=0 ; i<=N ; i++)
				{
					vector<int> initVector ;
					Graph.push_back(initVector);
					//indegree[i] = 0 ;  
				}
        		int edges=0 ;
        		for(int i=0;i<N;i++)
        		{
            		for(int j=0;j<N;j++)
            		{
            			int weight; cin>>weight ;
            			if(weight!=0)
            			{
            				edges++;
						}
                		Graph.at(i).push_back(weight) ;
                		
            		}           
        		}
				
				if(Q==2)
				DFS(Graph,N,s-1,D,edges) ;  // remember here must passs s-1 not s as my convention of vertex label start from 0 n ot 1
             
			/*for(int i=0; i<N; i++)
        	{
            	for(int j=0; j<N; j++)
            	{
            		cout<<Graph[i][j]<<" " ;
        		}
        		cout<<endl ;
    		} */
    		else if(Q==1)
    		BFS(Graph,N,s-1,D,edges) ;
        	}  
			
			else if(Q==4)
    		{   		
    		
    			list<pair<int,int>>* adj;
    			adj = new list< pair<int,int> > [N] ;
    			int stop=0;
    			for(int i=0;i<N;i++)
        		{
            		for(int j=0;j<N;j++)
            		{
            			int weight; cin>>weight ;
            			if(weight<0)
            			{
            				stop=1;
						}
						
						else if(weight!=0 && weight!=999999)
						{
							//cout<<"i= "<<i<<"j= "<<j<<endl;
						adj[i].push_back(make_pair(j,weight)) ;
						}
						//cout<<j<<" " ;
						
					}
				}
				
				if(stop==1)
				cout<<"-1"<<endl ;
				
				else
				{
					
					Dijkstra(adj,s-1,N)  ;
				}
				
			}  
			
			else if(Q==5)
    		{
    			list<pair<int,int>>* adj;
    			adj = new list< pair<int,int> > [N] ;
    			//int stop=0;
    			for(int i=0;i<N;i++)
        		{
            		for(int j=0;j<N;j++)
            		{
            			int weight; cin>>weight ;
            			
						
						if(weight!=0 && weight!=999999)
						{
							//cout<<"i= "<<i<<"j= "<<j<<endl;
						adj[i].push_back(make_pair(j,weight)) ;
						}
						//cout<<j<<" " ;
						
					}
				}
				
    		
    			Bellman(adj,s-1,N) ;
    		
			}  
       
        }
   
    	else if(Q==3)
    	{
        	int N; cin>>N;
        	
        	vector<vector<int>> Graph ;
        	int indegree[N+1] ;
        	for(int i=0 ; i<=N ; i++)
			{
				vector<int> initVector ;
				Graph.push_back(initVector);
				indegree[i] = 0 ;  //Initialisation
			}
        	
        	for(int i=0;i<N;i++)
        	{
            	for(int j=0;j<N;j++)
            	{
            		int weight; cin>>weight ;
                	Graph.at(i).push_back(weight) ;
                	if(weight!=0)
                	indegree[j]++;
            	}           
        	} 
             
			/*for(int i=0 ;i<N;i++)
        	{
            	for(int j=0 ; j<N;j++)
            	{
            		cout<<Graph[i][j]<<" " ;
        		}
        		cout<<endl;
    		} */
             
           lexographicTopoSort(N, Graph, indegree ) ;
    	} 
    	
    	
    	
	}

return 0;

}

/*code was giving correct output for all the test cases given on hackerrank*/

	



