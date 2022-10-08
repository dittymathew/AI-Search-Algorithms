#include<iostream>
#include <stdlib.h>
class Solution
{
	public:
	int no;
	double** dist_matrix;
	Solution(int n,double** dist){
		no =n;
		dist_matrix =dist;
	}

	int* Initialize(int *);
	double Evaluate(int *);
	int* twooptswap(int *tour,int *copy);
	int* twooptswap(int *tour,int *copy,int v1,int v2);
	int* randomgen(int *tour);

	
};
class Simulated
{
   public:
	int no;
	char* filename;
	double** dist_matrix;
	Simulated(int n,double** dist,char* file_name){
		no =n;
		dist_matrix =dist;
		filename=file_name;
	}
	double cooling(int index, int flag,double initialTemp,double finalTemp,int numTemp);
	int* Anneal(int*) ;
	void Display(int*);
	void Copy(int* tour1,int* tour2);

};
class HillClimb
{
   public:
	int no;
	double** dist_matrix;
	char* filename;
	HillClimb(int n,double** dist,char* file_name){
		no =n;
		dist_matrix =dist;
		filename=file_name;
	}
	int* HillClimbing(int*) ;
	int* SortMoveGen(int *node,double e1,Solution sol);
	void Display(int*);
	void Copy(int* tour1,int* tour2);

};
class IteratedHC
{
   public:
	int no;
	char* filename;
	double** dist_matrix;
	IteratedHC(int n,double** dist,char* file_name){
		no =n;
		dist_matrix =dist;
		filename=file_name;
	}
	int* IteratedHillClimbing(int*) ;
	void Display(int*);
	void Copy(int* tour1,int* tour2);

};
class BeamSearch
{
   public:
	int no;
	double** dist_matrix;
	char* filename;
	BeamSearch(int n,double** dist,char* file_name){
		no =n;
		dist_matrix =dist;
		filename=file_name;
	}
	int* BeamSearchAlgo(int*) ;
	void Display(int*);
	void Copy(int* tour1,int* tour2);
	void storeTopW(int **open,int **w_open,int n,int w,Solution sol);
	int MoveGen(int *node,int **open,int no_open,double e1,Solution sol);

};
