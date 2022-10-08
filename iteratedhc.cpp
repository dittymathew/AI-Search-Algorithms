//Iterated Hill Climbing
#include"tsp.h"
#include<math.h>
#include<fstream>
#include<ctime>
using namespace std;

/* *
 *Purpose:To display the tour
 *Input Argument: Tour to be displayed
 
 * */
void IteratedHC::Display(int* tour)
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

void IteratedHC::Copy(int* tour1,int* tour2)
{
	int i;
	for(i=0;i<no;i++)
	{
		tour2[i]=tour1[i];
	}
}

/* *
 *Purpose:Do Iterated Hill Climbing  to find best tour
 *Return: Best tour found so far
 
 * */

int* IteratedHC::IteratedHillClimbing(int *node)
{
	int n,i;
	int *bestnode=new int[no];/// best node
	int *newnode=new int[no];///new node
	int *cp=new int[no];
	double e1,e2,best_eval;
	Solution sol(no,dist_matrix);
	HillClimb hc(no,dist_matrix,"hill_cost.txt");
	cout<<"Enter no of iterations: ";
	cin>>n;
	Copy(node,bestnode);
	best_eval=sol.Evaluate(bestnode);///evaluate new tour
	cout<<"Current best cost: "<<best_eval<<"\n";
	for(i=0;i<n;i++)
	{
		sol.randomgen(node);///Generate initial solution
		e1=sol.Evaluate(node);///cost of current tour returned by Evaluate function
		newnode=hc.SortMoveGen(node,e1,sol);
		e2=sol.Evaluate(newnode);///evaluate new tour
		while(e2<e1)	
		{
			e1=e2;
			Copy(newnode,node);
			newnode=hc.SortMoveGen(node,e1,sol);
			e2=sol.Evaluate(newnode);///evaluate new tour
			if(e2 < best_eval)
			{
				best_eval=e2;
				cout<<"Current best cost: "<<best_eval<<"\n";
				Copy(newnode,bestnode);
				//Display(bestnode);
			}
		}
	}
	return bestnode;
}


