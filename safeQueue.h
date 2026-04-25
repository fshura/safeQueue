#ifindef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>
#include <future>

template <typename T>
class safeQueue {
	std::queue<T> queue;
	std::mutex mtx;
	std::condition_variable cv;
public:
	void push(const T& value){
		std::unique_lock<std::mutex> lock(mtx);
		queue.push(value);
		cv.notify_one();
	}
	void push(T&& value){
		std::unique_lock<std::mutex> lock(mtx);
		queue.push(value);
		cv.notify_one();
	}
	T pop(){
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this]{return !queue.empty();});
		T temp = queue.front();
		queue.pop();
		return temp;
	}
	bool try_pop(T& value) {
		std::unique_lock<std::mutex> lock(mtx);
		if(!queue.empty()){
			value = queue.front();
			queue.pop();
			return true;
		} else {
			return false;
		}
	}
	bool empty() const {
		std::unique_lock<std::mutex> lock(mtx);
		return queue.empty();
	}
	size_t size() const {
		std::unique_lock<std::mutex> lock(mtx);
		return queue.size();
	}
};

void adder(safeQueue<int>& sq ,int number);
int sumDel(safeQueue<int>& sq, int number);

#endif
