#include "safeQueue.h"

int main(){
	safeQueue<int> q;
	std::thread add1(adder, std::ref(q), 1000);
	std::thread add2(adder, std::ref(q), 1000);
	std::future<int> sumDel1 = std::async(std::launch::async, sumDel, std::ref(q), 1000);
	std::future<int> sumDel2 = std::async(std::launch::async, sumDel, std::ref(q), 1000);
	add1.join();
	add2.join();
	int sum1 = sumDel1.get();
	int sum2 = sumDel2.get();
	std::cout << sum1+sum2;
	return 0;
}
