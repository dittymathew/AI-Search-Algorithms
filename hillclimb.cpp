//Hill Climbing
#include"tsp.h"
#include<string.h>
#include<math.h>
#include<fstream>
using namespace std;

/* *
 *Purpose:To display the tour
 *Input Argument: Tour to be displayed
 
 * */
void HillClimb::Display(int* tour)
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

void HillClimb::Copy(int* tour1,int* tour2)
{
	int i;
	for(i=0;i<no;i++)
	{
		tour2[i]=tour1[i];
	}
}

int* HillClimb::SortMoveGen(int *node,double e1,Solution sol)
{
	int i,j,v1,v2;
	double e2,cur_best_val;
	int *newnode=new int[no];///tour obtained by perturbing
	int *cp=new int[no];///tour obtained by perturbing
	int *cur_best=new int[no];///tour obtained by perturbing
	cur_best_val =e1;
	Copy(node,cur_best);
	for(i=0;i<no/4;i++)
	{
//		for(j=0;j<no;j++)
//		{
//			if(i!=j)
//			{
		v1=rand() % no;
		v2=rand() % no;
			Copy(node,newnode);
			Copy(newnode,cp);
			sol.twooptswap(newnode,cp,v1,v2);///generate neighbour of the tour using 2 opt 
			//free(cp);
			e2=sol.Evaluate(newnode);
			if(cur_best_val>e2)
			{
				Copy(newnode,cur_best);
				cur_best_val=e2;
			}
//			}
//		}
	}
//	free(newnode);
//	free(cp);
	return cur_best;
}


/* *
 *Purpose:Hill Climbing  to find best tour
 *Return: Best tour found so far
 
 * */

int* HillClimb::HillClimbing(int *node)
{
	int *newnode=new int[no];///tour obtained by perturbing
	int *cp=new int[no];///tour obtained by perturbing
	double e1,e2;
	Solution sol(no,dist_matrix);
	e1=sol.Evaluate(node);///cost of current tour returned by Evaluate function

	cout<<"Current best cost:"<<e1<<"\n";
	newnode=SortMoveGen(node,e1,sol);
	e2=sol.Evaluate(newnode);///evaluate new tour
	while(e2<e1)	
	{
		cout<<"Current best cost:"<<e2<<"\n";
		e1=e2;
		Copy(newnode,node);
		newnode=SortMoveGen(node,e1,sol);
		e2=sol.Evaluate(newnode);///evaluate new tour
		
		
	}
	return newnode;
}


