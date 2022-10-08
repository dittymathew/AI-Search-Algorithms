//Hill Climbing
#include"tsp.h"
#include<string.h>
#include<math.h>
#include<fstream>
#include<ctime>
using namespace std;

/* *
 *Purpose:To display the tour
 *Input Argument: Tour to be displayed
 
 * */
void BeamSearch::Display(int* tour)
{
	int i;
	for(i=0;i<no;i++)
	{
		cout<<tour[i]+1<<" ";
	}
cout<<"\n";
}

/* *
 *Purpose:To copy the tour to another array
 *Input Argument: source, destination
 
 * */

void BeamSearch::Copy(int* tour1,int* tour2)
{
	int i;
	for(i=0;i<no;i++)
	{
		tour2[i]=tour1[i];
	}
}
void BeamSearch::storeTopW(int **open,int **w_open,int n,int w,Solution sol)
{
	int i,j;
	int *min_node;
	double min,nxt,best;
	for(j=1;j<n;j++)
	{
		min_node=open[j];
		min=sol.Evaluate(open[j]);
		i= j-1;
		nxt=sol.Evaluate(open[i]);
		while(i>0 && nxt>min)
		{
			Copy(open[i],open[i+1]);
			i--;
		}
		Copy(min_node,open[i+1]);
	}
	
	cout<<"Current best cost :";
	for(i=0;i<n;i++)
	{
		if(i<w)
		{
			Copy(open[i],w_open[i]);
			best=sol.Evaluate(open[i]);
			cout<<best<<"\t";
		}
		open[i]=NULL;
	}
	cout<<"\n";
	
}
int BeamSearch::MoveGen(int *node,int **open,int no_open,double e1,Solution sol)
{
	int i,j,child_cnt,v1,v2;
	double e2;
	int *newnode=new int[no];///tour obtained by perturbing
	int *cp=new int[no];///tour obtained by perturbing
	child_cnt =0;

	for(i=0;i<(no/4);i++)
	{
		Copy(node,cp);
		Copy(cp,newnode);
		v1=rand() % no;
		v2=rand() % no;
		sol.twooptswap(cp,newnode,v1,v2);///generate neighbour of the tour using 2 opt 
		e2=sol.Evaluate(cp);
//		Display(cp);
		if(e2 < e1)
		{
			
			open[no_open]= new int[no];
			Copy(cp,open[no_open]);
			no_open++;				
		}
	}
	return no_open;
}

/* *
 *Purpose:Beam Search  to find best tour
 *Return: Best tour found so far
 
 * */

int* BeamSearch::BeamSearchAlgo(int *node)
{
	int *best=new int[no];///best tour being processed
	double e1,e2,best_eval;
	int **open,**w_open;
	int i,j,no_open,k,w,cnt;
	no_open=0;
	open =new int *[no];
	for(i=0;i<(no);i++){
		open[i] =new int [no];
	}
	w_open =new int *[no];
	for(i=0;i<no;i++){
		w_open[i] =new int [no];
	}
	Solution sol(no,dist_matrix);
	cout<<"Enter Beam Width\n";
	cin>>w;
	e1=sol.Evaluate(node);///cost of current tour returned by Evaluate function
	cout<<"Current best cost:"<<e1<<"\n";
	Copy(node,best);
	best_eval=e1;
	no_open=MoveGen(node,open,no_open,e1,sol);
	while(no_open !=0)
	{
		storeTopW(open,w_open,no_open,w,sol);
		if(w_open[0]!=NULL)
			best=w_open[0];
		no_open=0;
		for(i=0;i<w;i++)
		{
			if(w_open[i]!=NULL){
			e1=sol.Evaluate(w_open[i]);///cost of current tour returned by Evaluate function
			cnt=no_open;
			no_open= MoveGen(w_open[i],open,no_open,e1,sol);
			}
		}
		
	}
	return best;
}


