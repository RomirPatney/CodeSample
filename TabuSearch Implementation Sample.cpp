/*C++*/

#include <iostream>
#include <stdlib.h>
#include <map>

#define OPTIMUM_SCORE 1285
#define TABU_SEARCH_ITERATIONS 10000

#define BULLET_1 	0
#define BULLET_2 	0
#define BULLET_3 	1
#define BULLET_4_a 	0
#define BULLET_4_b 	0
#define BULLET_5 	0
#define BULLET_6 	0

using namespace std;

class QAP {
	private:
		unsigned flow[20][20] = {
			{	0,	0,	5,	0,	5,	2,	10,	3,	1,	5,	5,	5,	0,	0,	5,	4,	4,	0,	0,	1},
			{	0,	0,	3,	10,	5,	1,	5,	1,	2,	4,	2,	5,	0,	10,	10,	3,	0,	5,	10,	5},
			{	5,	3,	0,	2,	0,	5,	2,	4,	4,	5,	0,	0,	0,	5,	1,	0,	0,	5,	0,	0},
			{	0,	10,	2,	0,	1,	0,	5,	2,	1,	0,	10,	2,	2,	0,	2,	1,	5,	2,	5,	5},
			{	5,	5,	0,	1,	0,	5,	6,	5,	2,	5,	2,	0,	5,	1,	1,	1,	5,	2,	5,	1},
			{	2,	1,	5,	0,	5,	0,	5,	2,	1,	6,	0,	0,	10,	0,	2,	0,	1,	0,	1,	5},
			{	10,	5,	2,	5,	6,	5,	0,	0,	0,	0,	5,	10,	2,	2,	5,	1,	2,	1,	0,	10},
			{	3,	1,	4,	2,	5,	2,	0,	0,	1,	1,	10,	10,	2,	0,	10,	2,	5,	2,	2,	10},
			{	1,	2,	4,	1,	2,	1,	0,	1,	0,	2,	0,	3,	5,	5,	0,	5,	0,	0,	0,	2},
			{	5,	4,	5,	0,	5,	6,	0,	1,	2,	0,	5,	5,	0,	5,	1,	0,	0,	5,	5,	2},
			{	5,	2,	0,	10,	2,	0,	5,	10,	0,	5,	0,	5,	2,	5,	1,	10,	0,	2,	2,	5},
			{	5,	5,	0,	2,	0,	0,	10,	10,	3,	5,	5,	0,	2,	10,	5,	0,	1,	1,	2,	5},
			{	0,	0,	0,	2,	5,	10,	2,	2,	5,	0,	2,	2,	0,	2,	2,	1,	0,	0,	0,	5},
			{	0,	10,	5,	0,	1,	0,	2,	0,	5,	5,	5,	10,	2,	0,	5,	5,	1,	5,	5,	0},
			{	5,	10,	1,	2,	1,	2,	5,	10,	0,	1,	1,	5,	2,	5,	0,	3,	0,	5,	10,	10},
			{	4,	3,	0,	1,	1,	0,	1,	2,	5,	0,	10,	0,	1,	5,	3,	0,	0,	0,	2,	0},
			{	4,	0,	0,	5,	5,	1,	2,	5,	0,	0,	0,	1,	0,	1,	0,	0,	0,	5,	2,	0},
			{	0,	5,	5,	2,	2,	0,	1,	2,	0,	5,	2,	1,	0,	5,	5,	0,	5,	0,	1,	1},
			{	0,	10,	0,	5,	5,	1,	0,	2,	0,	5,	2,	2,	0,	5,	10,	2,	2,	1,	0,	6},
			{	1,	5,	0,	5,	1,	5,	10,	10,	2,	2,	5,	5,	5,	0,	10,	0,	0,	1,	6,	0}
		};
		
		unsigned distance[20][20] = {
			{	0,	1,	2,	3,	4,	1,	2,	3,	4,	5,	2,	3,	4,	5,	6,	3,	4,	5,	6,	7},
			{	1,	0,	1,	2,	3,	2,	1,	2,	3,	4,	3,	2,	3,	4,	5,	4,	3,	4,	5,	6},
			{	2,	1,	0,	1,	2,	3,	2,	1,	2,	3,	4,	3,	2,	3,	4,	5,	4,	3,	4,	5},
			{	3,	2,	1,	0,	1,	4,	3,	2,	1,	2,	5,	4,	3,	2,	3,	6,	5,	4,	3,	4},
			{	4,	3,	2,	1,	0,	5,	4,	3,	2,	1,	6,	5,	4,	3,	2,	7,	6,	5,	4,	3},
			{	1,	2,	3,	4,	5,	0,	1,	2,	3,	4,	1,	2,	3,	4,	5,	2,	3,	4,	5,	6},
			{	2,	1,	2,	3,	4,	1,	0,	1,	2,	3,	2,	1,	2,	3,	4,	3,	2,	3,	4,	5},
			{	3,	2,	1,	2,	3,	2,	1,	0,	1,	2,	3,	2,	1,	2,	3,	4,	3,	2,	3,	4},
			{	4,	3,	2,	1,	2,	3,	2,	1,	0,	1,	4,	3,	2,	1,	2,	5,	4,	3,	2,	3},
			{	5,	4,	3,	2,	1,	4,	3,	2,	1,	0,	5,	4,	3,	2,	1,	6,	5,	4,	3,	2},
			{	2,	3,	4,	5,	6,	1,	2,	3,	4,	5,	0,	1,	2,	3,	4,	1,	2,	3,	4,	5},
			{	3,	2,	3,	4,	5,	2,	1,	2,	3,	4,	1,	0,	1,	2,	3,	2,	1,	2,	3,	4},
			{	4,	3,	2,	3,	4,	3,	2,	1,	2,	3,	2,	1,	0,	1,	2,	3,	2,	1,	2,	3},
			{	5,	4,	3,	2,	3,	4,	3,	2,	1,	2,	3,	2,	1,	0,	1,	4,	3,	2,	1,	2},
			{	6,	5,	4,	3,	2,	5,	4,	3,	2,	1,	4,	3,	2,	1,	0,	5,	4,	3,	2,	1},
			{	3,	4,	5,	6,	7,	2,	3,	4,	5,	6,	1,	2,	3,	4,	5,	0,	1,	2,	3,	4},
			{	4,	3,	4,	5,	6,	3,	2,	3,	4,	5,	2,	1,	2,	3,	4,	1,	0,	1,	2,	3},
			{	5,	4,	3,	4,	5,	4,	3,	2,	3,	4,	3,	2,	1,	2,	3,	2,	1,	0,	1,	2},
			{	6,	5,	4,	3,	4,	5,	4,	3,	2,	3,	4,	3,	2,	1,	2,	3,	2,	1,	0,	1},
			{	7,	6,	5,	4,	3,	6,	5,	4,	3,	2,	5,	4,	3,	2,	1,	4,	3,	2,	1,	0}
		};
		
		unsigned cost[20][20];
		unsigned netCost;
		
	public:
		void calculateCost();
		unsigned int returnNetCost();
		void swapDistances(int a, int b);
		
};

void QAP::calculateCost(){
	netCost = 0;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(i >= j)
				continue;
			netCost += flow[i][j]*distance[i][j];
		}
	}
}

unsigned int QAP::returnNetCost(){
	calculateCost();
	return netCost;
}

void QAP::swapDistances(int a, int b){
	
	unsigned int temp[20];
	
	for(int i = 0; i < 20; i++)
	{
		temp[i] = distance[a][i];
		distance[a][i] = distance[b][i];
		distance[b][i] = temp[i];
	}
	
	for(int i = 0; i < 20; i++)
	{
		temp[i] = distance[i][a];
		distance[i][a] = distance[i][b];
		distance[i][b] = temp[i];
	}
}

typedef struct Permutation{
	int a;
	int b;
} Permutation;


class tabuSearch {
	private:
		QAP qap;
		unsigned int tabuMatrix [20][20];
		unsigned int tabuListSize = 5;
		
		unsigned int currentPermuation[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
		unsigned int currentScore = 0xffffffff;
		
		unsigned int bestScore = 0xffffffff;
		unsigned int bestPermuation[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
		
		std::multimap<int, Permutation> candidates;
		
		void swapCurrentPerm(int a, int b){
			unsigned int temp = currentPermuation[a];
			currentPermuation[a] = currentPermuation[b];
			currentPermuation[b] = temp;
		}
		
		void currentPermIsBestPerm(){
			for(int i = 0; i < 20; i++){
				bestPermuation[i] = currentPermuation[i];
			}
		}
		
	public:
		tabuSearch(){}
		tabuSearch(unsigned int size) : tabuListSize(size){}
		
		
		void q1randomizeStart(int seed){
			srand(seed);
			
			for(int itr = 0; itr < 100; itr++){
				for(int i = 0; i < 20; i++){
			        for(int j = 0; j < 20; j++){
			            
			            if( i >= j )
							continue;
			            
						if(rand()%5 == 0){
			                qap.swapDistances(i,j);
							swapCurrentPerm(i, j);
			            }
			        }
			    }
			}
		}
		
		void TabuSearch(){
			
			bestScore = 0xffffffff;
			for(int i = 0; i < 20; i++){
				for(int j = 0; j < 20; j++){
					tabuMatrix[i][j] = 0;		
				}
			}
			cout<<"Current Starting Permutation:";
			for(int i = 0; i < 20; i++){
				cout<<currentPermuation[i]<<" ";
			}
			cout<<"\n";
			
			for(int itr = 0; itr < TABU_SEARCH_ITERATIONS; itr++){
				
				// Generate candidates
				for(int i = 0; i < 20; i++){
					for(int j = 0; j < 20; j++){
						
						if( i >= j )
							continue;
						
						// skip half of the candidates randomly
						if(BULLET_5){
							if(rand()%2 == 0){
								continue;
							}
						}
						
						// swap
						qap.swapDistances(i,j);
						
						// note score
						unsigned int score = qap.returnNetCost();
						// note candiate permutation
						Permutation permutation = {i , j};
						
						// Add to candidate list
						candidates.insert(std::make_pair(score, permutation));
						
						// reverse swap
						qap.swapDistances(i,j);
					}
				}
				
				int xSwap = 0, ySwap = 0;
				unsigned int score;
				
				// Select candidate
				for(std::multimap<int, Permutation>::iterator it = candidates.begin(); it != candidates.end(); it++){
					xSwap = it->second.a;
					ySwap = it->second.b;
					score = it->first;
					// Iterate through candidates till you find a non-taboo move
					if(BULLET_4_a){
						if( tabuMatrix[xSwap][ySwap] == 0 || score < bestScore){
							break;
						}	
					}
					
					if(BULLET_4_b){
						if( tabuMatrix[xSwap][ySwap] == 0 || score < currentScore){
							break;
						}
					}
					
					if( tabuMatrix[xSwap][ySwap] == 0 ){
						break;
					}
				}
				
				qap.swapDistances(xSwap,ySwap);
				swapCurrentPerm(xSwap, ySwap);
				
				currentScore = score;
				
				if(currentScore < bestScore){
					bestScore = score;
					currentPermIsBestPerm();
				}
				
				if(bestScore == OPTIMUM_SCORE || itr == (TABU_SEARCH_ITERATIONS - 1) ){
					cout<<"Best Score: "<<bestScore<<" Permutation: ";
					for(int i = 0; i < 20; i++){
						cout<<bestPermuation[i]<<" ";
					}
					cout<<"\n";
					cout<<"Optimum reached in: "<<itr + 1<<" iterations \n";
					break;
				}
				
				// Wipe candidate list
				candidates.clear();
				
				for(int x = 0; x < 20; x++){
					for(int y = 0; y < 20; y++){
						if(x >= y)
							continue;
						if(tabuMatrix[x][y] > 0){
							tabuMatrix[x][y] = tabuMatrix[x][y] - 1;
						}
					}	
				}
				
				if(BULLET_3){
					tabuListSize = rand()%19;
				}
				
				tabuMatrix[xSwap][ySwap] += tabuListSize;
			}
		}
	
};

int main(){
	
	if(BULLET_1){
		for(int i = 0; i < 10; i++){
			tabuSearch t(8);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_2){
		for(int i = 0; i < 10; i++){
			tabuSearch t(13);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
		
		for(int i = 0; i < 10; i++){
			tabuSearch t(5);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_3){
		for(int i = 0; i < 10; i++){
			tabuSearch t;
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_4_a && BULLET_4_b){
		cout<<"Both bullet 4a and 4b can't run together";
		return 0;
	}
	
	if(BULLET_4_a){
		for(int i = 0; i < 10; i++){
			tabuSearch t(8);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_4_b){
		for(int i = 0; i < 10; i++){
			tabuSearch t(8);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_5){
		for(int i = 0; i < 10; i++){
			tabuSearch t(8);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
	if(BULLET_6){
		for(int i = 0; i < 10; i++){
			tabuSearch t(8);
			t.q1randomizeStart(i);
			t.TabuSearch();
		}
	}
	
}
