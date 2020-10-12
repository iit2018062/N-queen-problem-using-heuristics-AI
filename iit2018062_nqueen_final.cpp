#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int min_value(vector<vector<int> >&domain,vector<bool>&visited)
{  
    int  m =INT_MAX;
   int n = domain.size();
   int c=0;
   int col;
   for(int i=0;i<n;i++)
   { c=0;
   	for(int j=0;j<n;j++)
   	{
   		if(domain[j][i]!=-1)c++;
	   }
	   if(c<m && visited[i]!=true)
	   {
	   	m=c;
	   	col=i;
	   }
	   
   }
   return col;
}
int helper(int row,int col,vector<vector<int> >&domain,int n)
{  //cout<<"inside helper\n";
   //remove the row 
   int c=0;
   for(int i=0;i<n;i++)
   {
   	if(i!=col)
   domain[row][i]=-1;  }
   
    for(int i=0;i<n;i++)
    {
    	if(i!=row)
    	domain[i][col]=-1;
	}
	   //remove theh diagonal rows;
	   //lower diagonal
	   for(int i=row+1,j=col+1;j<n &&i<n;j++,i++)
	   domain[i][j]=-1;
	   
	   for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++)
	   domain[i][j]=-1;
	   for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--)
	   domain[i][j]=-1;
	   for(int i=row+1,j=col-1;i<n&&j>=0;i++,j--)
	   domain[i][j]=-1;
   
}
bool over(vector<vector<int> >&g,int n)
{  //cout<<"lll\n";
	int c=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(g[i][j]==1)c++;
		}
		
	}
	if(c==n)return true;
	return false;
}
bool revised(vector<vector<int> >&domain,int col,int row,int n)
{     int c=0;

	c=helper(row,col,domain,n);

	for(int i=0;i<n;i++)
	{   c=0;
		for(int j=0;j<n;j++)
		{    
			if(domain[i][j]!=-1)c++;
		}
		
		if(c==0)
		{  
			domain[row][col]=-1;
			return false;
		}
	
	}
	return true;
	
}
bool fun(vector<vector<int> >&g,vector<vector<int> >&d,int n,vector<bool>&visited)
{ 
	
	vector<vector<int> >s = d;
     queue<vector<vector<int> > >q;
      q.push(d);
      while(!q.empty())
      {
      	
      	vector<vector<int> >tempo=q.front();
      	q.pop();
      	if(over(tempo,n))return true;
      	int col = min_value(tempo,visited);
     	visited[col]=true;
       for(int i=0;i<n;i++)
	   {   
	vector<vector<int> >tmp = tempo;

	if(g[i][col]==0 && tempo[i][col]!=-1 && revised(tempo,col,i,n) )
	{
		g[i][col]=1;
	
		bool flag = fun(g,tempo,n,visited);
		if(flag)return true;
		q.push(tmp);
		tempo= tmp;

		g[i][col]=0;
		
		
      	}
      	else tempo = tmp;
		
	   }

	  }

	
	return false;
}

int main()
{
	int n;
	cin>>n;
    vector<vector<int> >domain(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<n;j++)
    	domain[i][j]=i;
	}

    vector<vector<int> >chess(n,vector<int>(n,0));
    
    vector<bool>visited(n,false);
    bool f=fun(chess,domain,n,visited);
    cout<<"0 means no queen in place while 1 means a queen in the cell, -1 means no solution\n";
    if(f)
    {
    	for(int i=0;i<n;i++)
    	{
    		for(int j=0;j<n;j++)
    		cout<<chess[i][j]<<" ";
    		cout<<endl<<endl;
		}
		
		
	}
	else if(!f)cout<<-1<<endl;
}
