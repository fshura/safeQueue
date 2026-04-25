#include "safeQueue.h"

void adder(safeQueue<int>& sq ,int number){
	for(int i = 0; i<number; ++i){
		sq.push(i);
	} 
}
int sumDel(safeQueue<int>& sq, int number){
	int sum = 0;
	for(int i = 0; i<number; ++i){
		int current = sq.pop();
		sum += current;
	} 
	return sum;
}
