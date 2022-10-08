#include<iostream>
#include "gnuplot.h"
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<sstream>
#include <fstream>
#include <math.h>
#include"tsp.h"
#include"cur_time.h"
#include<float.h>
using namespace std;
int noOfCities;
double **dist_matrix = NULL;
double **cordinate = NULL;
/**
 * Purpose :To compute euclidean distance between cities
 * Input Arguments: Coordinates of two cities-x1,y1 and x2,y2
 * Return : Distance computed
**/
double distance(double x1,double y1, double x2,double y2)
{
	double dist;
	dist = sqrt((((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
//	dist = abs(x2-x1)+abs(y2-y1);
	return dist;
}

/**
 * Purpose :To generate random sequence
 * 
 * **/

void generateRandom()
{
	bool euclidean;
	int i,j,len,pos1,pos2;
	string line,subline;		
	char euc[100];	
	int max,min;
	dist_matrix =new double *[noOfCities];
	for(i=0;i<noOfCities;i++){
		dist_matrix[i] =new double [noOfCities];
	}
	cordinate =new double *[noOfCities];
	for(i=0;i<noOfCities;i++){
		cordinate[i] =new double [2];
	}
	max=20000;
	min=0;
	for(i=0;i<noOfCities;i++){
		cordinate[i][0] = (double)((double)(rand() % (max - min + 1)/100) - 100.00);
		cordinate[i][1] = (double)((double)(rand() % (max - min + 1)/100) + 100.00);
	}
	i=0;
        while(i<noOfCities)
        {
		for(j=0;j<noOfCities;++j)
		{
			dist_matrix[i][j]=distance(cordinate[i][0],cordinate[i][1],cordinate[j][0],cordinate[j][1]);
	
		}
		i++;
	}
	
}
void DisplayCities()
{
	int i;
	ofstream out("cities.txt");
	for(i=0;i<noOfCities;i++)
	{
		out<<cordinate[i][0]<<" "<<cordinate[i][1]<<"\n";
		cout<<i+1<<" ("<<cordinate[i][0]<<" , "<<cordinate[i][1]<<")\n";
	}
}
void writetoFile(int* path, char* filename)
{
	int i;
	ofstream out(filename);
	for(i=0;i<noOfCities;i++)
	{
		out<<cordinate[path[i]][0]<<" "<<cordinate[path[i]][1]<<"\n";
	}
}
void Display(int* tour)
{
	int i;
	ofstream out1("tour.txt");
	for(i=0;i<noOfCities;i++)
	{
		out1<<cordinate[tour[i]][0]<<" "<<cordinate[tour[i]][1]<<"\n";
	}
}


int main(int argc, char **argv)
{
	cur_time=0;
	double e1,e2;
	int i,ch,n_itr;
	cout<<"Enter the no of cities: ";
	cin>>noOfCities;
	generateRandom();///to calculate distance matrix
	DisplayCities();
	char pause;
	Gnuplot plot;
	plot("plot \"cities.txt\"") ;
	cout << "Press any Enter to Continue...";
	cin.get();
	Solution sol(noOfCities,dist_matrix);
//	int *ipath =(int*) malloc(noOfCities);
	int *ipath=new int[noOfCities];///tour obtained by perturbing
	sol.randomgen(ipath);///Generate initial solution
	cout<<"Enter Choice:\n";
	cout<<" 1. Hill Climbing\n 2. Iterated Hill Climbing\n 3. Beam Search\n 4. Simulated Anealing\n 5. Exit\n  ";
	cin>>ch;
	ofstream out11("hill_cost.txt");
	ofstream out12("iteratedhc_cost.txt");
	ofstream out13("beamsearch_cost.txt");
	ofstream out14("simulate_cost.txt");
	HillClimb hc(noOfCities,dist_matrix,"hill_cost.txt");
	IteratedHC ihc(noOfCities,dist_matrix,"iteratedhc_cost.txt");
	BeamSearch bs(noOfCities,dist_matrix,"beamsearch_cost.txt");
	Simulated sim(noOfCities,dist_matrix,"simulate_cost.txt");
	while(ch!=5)
	{
	switch(ch)
	{
		case 1:
			cout<<"Initial Tour\n";
			hc.Display(ipath);///displays best path found
			ipath=hc.HillClimbing(ipath);///calling HillClimbing()
			cout<<"Final Tour\n";
			hc.Display(ipath);///displays best path found
			Display(ipath);///displays best path found
			break;
		case 2:
			cout<<"Initial Tour\n";
			hc.Display(ipath);///displays best path found
			ipath=ihc.IteratedHillClimbing(ipath);///calling Iterated HillClimbing()
			cout<<"Final Tour\n";
			hc.Display(ipath);///displays best path found
			Display(ipath);///displays best path found 
			break;
		case 3:
			cout<<"Initial Tour\n";
			hc.Display(ipath);///displays best path found
			ipath=bs.BeamSearchAlgo(ipath);///calling BeamSearchAlgo()
			cout<<"Final Tour\n";
			hc.Display(ipath);///displays best path found
			Display(ipath);///displays best path found
			break;
		case 4:
			cout<<"Initial Tour\n";
			hc.Display(ipath);///displays best path found
			ipath=sim.Anneal(ipath);///calling simulated annealing
			cout<<"Final Tour\n";
			hc.Display(ipath);///displays best path found
			Display(ipath);///displays best path found
			break;
		default:
			cout<<"Enter correct choice\n";
			break;
	}
	plot("plot \"tour.txt\" using 1:2 with linesp title \"Tour\"") ;
	cout<<"Enter Choice :\n";
	cout<<" 1. Hill Climbing\n 2. Iterated Hill Climbing\n 3. Beam Search\n 4. Simulated Anealing\n 5. Exit\n  ";
	cin>>ch;
	}


}
