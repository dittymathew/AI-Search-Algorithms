//Simulated Annealing
#include"tsp.h"
#include<math.h>
#include<fstream>
#include<ctime>
using namespace std;

/* *
 *Purpose:To display the tour
 *Input Argument: Tour to be displayed
 
 * */
void Simulated::Display(int* tour)
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

void Simulated::Copy(int* tour1,int* tour2)
{
	int i;
	for(i=0;i<no;i++)
	{
		tour2[i]=tour1[i];
	}
}

/* *
 *Purpose:Simulated annealing to find best tour
 *Return: Best tour found so far
 
 * */

int* Simulated::Anneal(int *node)
{
	int dist;
	double sec;
    time_t begin = time(0);
	int *curr_best_path = new int[no];///stores the best path found so far
	int *prev=new int[no];///tour being processed
	int *next=new int[no];///tour obtained by perturbing
	int *cp=new int[no];///tour obtained by perturbing
	int i,j;
	double temp,temp_cst;
	double init_temp=100.0;///starting temperature
	double cool_fact =0.99992;///temperature reduction factor
	double prob=0.0;
	int num_it=100;///number of iterations in one temperature
	int num_temp= 100000000;///max number of temperature values considered
	double e1,e2,delta,cur_fit,greedy;
	Solution sol(no,dist_matrix);
	Copy(node,curr_best_path);
	cout<<"Enter Temperature: ";
	cin>>init_temp;
	cout<<"Enter no of epocs: ";
	cin>>num_temp;
	Copy(curr_best_path,prev);
	e1=sol.Evaluate(curr_best_path);///cost of current tour returned by Evaluate function
	ofstream out(filename, ios::out | ios::app);
	cout<<"Current best cost: "<<e1<<"\n";
	//Display(curr_best_path);///display the current best tour
	greedy =e1;
	cur_fit=e1;
	temp=init_temp;
	for(i=0;i<num_temp;i++)
   	{
	        time_t cur = time(0);/// to check 5 minutes time limit
		sec =difftime(cur,begin);///difference between cuurent time and beginning time
	///if time elapsed greater than 4 minutes exit displaying best tour found 
		if(sec>=260){
			break;
		}
		temp_cst=0.00;
		for(j=0;j<num_it;j++)
		{
		       Copy(prev,next);///copy prev tour(which is being processed to another array before perturbing)
		       Copy(next,cp);///copy prev tour(which is being processed to another array before perturbing)
		       sol.twooptswap(next,cp);///generate neighbour of the tour using 2 opt 
		       e2=sol.Evaluate(next);///evaluate new tour
		       if(temp_cst==0.00)
				temp_cst=e2;
		       if(e2<temp_cst)		
				temp_cst=e2;
		       delta=e2-e1;///diference between costs of previous and next tour
		      // if(e2<e1)///if next tour is better than prev tour 	
			//	prob=1.0;
		       //else
		       prob= 1/(1+exp(delta/temp));///calculate probability of movinf from prev to next tour
		
		       if((rand()/(double)RAND_MAX)<prob)///generate random number between 0 and 1, compare with probability
		       {
				if(cur_fit > e2)///if next tour better than current best then set current best as next tour
				{
					Copy(next,curr_best_path);
					cur_fit=e2;
					cout<<"Current best cost: "<<e2<<"\n";
					//Display(curr_best_path);

				}
				e1=e2;
				Copy(next,prev);

			}
		}
		temp=temp*cool_fact;///reducing temperature
	}
	return curr_best_path;


}
