#include <gtest/gtest.h>
#include "../src/safeQueue.h"

TEST(SafeQueueTest, PushPop) {
    safeQueue<int> queue;
    const int toPush = 2;
    
    queue.push(toPush);
    
    int fromPop = queue.pop();
    EXPECT_EQ(toPush,fromPop);
}
TEST(SafeQueueTest, FIFO) {
    safeQueue<int> queue;
    const int toPush1 = 3, toPush2 = 5;
    
    queue.push(toPush1);
    queue.push(toPush2);
    
    int fromPop1 = queue.pop();
    int fromPop2 = queue.pop();
    
    EXPECT_EQ(toPush1,fromPop1);
    EXPECT_EQ(toPush2,fromPop2);
}
TEST (SafeQueueTest, Empty){
	safeQueue<int> queue;
	EXPECT_TRUE(queue.empty());
	
	queue.push(1);
	EXPECT_FALSE(queue.empty());
	
	queue.pop();
	EXPECT_TRUE(queue.empty());
}
TEST (SafeQueueTest, Size){
	safeQueue<int> queue;
	EXPECT_EQ(0,queue.size());
	
	queue.push(2);
	queue.push(3);
	EXPECT_EQ(2,queue.size());
	
	queue.pop();
	EXPECT_EQ(1,queue.size());
	
	queue.pop();
	EXPECT_EQ(0,queue.size());
}
TEST (SafeQueueTest, TryPopOnEmpty){
	safeQueue<int> queue;
	int fromPop = 0;
	
	EXPECT_FALSE(queue.try_pop(fromPop));
	EXPECT_EQ(0,fromPop);
}
TEST (SafeQueueTest, TryPopOnNonEmpty){
	safeQueue<int> queue;
	const int toPop = 2;
	queue.push(toPop);
	
	int fromPop = 0;
	bool isPop = false;
	isPop = queue.try_pop(fromPop);
	
	EXPECT_TRUE(isPop);
	EXPECT_EQ(toPop,fromPop);
}
TEST (SafeQueueTest, TwoAdderThreeSumDel){
	safeQueue<int> queue;
	const int toAdd = 300, toSumDel = 200;
	
	std::thread add1(adder, std::ref(queue), toAdd);
	std::thread add2(adder, std::ref(queue), toAdd);
	std::future<int> sumDel1 = std::async(std::launch::async, sumDel, std::ref(queue), toSumDel);
	std::future<int> sumDel2 = std::async(std::launch::async, sumDel, std::ref(queue), toSumDel);
	std::future<int> sumDel3 = std::async(std::launch::async, sumDel, std::ref(queue), toSumDel);
	add1.join();
	add2.join();
	const int sum1 = sumDel1.get();
	const int sum2 = sumDel2.get();
	const int sum3 = sumDel3.get();
	const int allSum = sum1+sum2+sum3;
	
	EXPECT_TRUE(queue.empty());
	EXPECT_EQ(0,queue.size());
	EXPECT_EQ((toAdd-1)*toAdd, allSum);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
