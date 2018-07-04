#include<future>
#include<vector>
#include<queue>
#include<functional>
#include<iostream>
#include<cstdlib>
#include "Player.h"
#include "scheduling.h"
extern scheduler sched;

int runLater(int x)
{
	std::cout << "Currently running with x = " << x << std::endl;
	return x + 4;
}
// Test suite
void testQueue()
{
	task t1 = { std::async(std::launch::deferred, runLater, 3), 2 };
	task t2 = { std::async(std::launch::deferred, runLater, 5), 1 };

	sched.queue.push(t1);
	sched.queue.push(t2);

	while (!sched.queue.empty())
	{
		task t = sched.queue.top();
		sched.queue.pop();
		std::cout << "At time " << t.time << " a value of " << t.call.get() << " was returned\n";
	}
}

void testPlayer()
{
	int R[NUM_RESIST] = { 0, 0, 0, 0, 0 };
	Player p1("Player 1", 25, 10, 3, 1, 21, 12, 8, 20, R);
	Player p2("Player 2", 30, 5, 7, 1, 5, 25, 30, 17, R);

	p1.attack(p2);
	p2.attack(p1);

	sched.run();
}

int main()
{
	srand(time(0));
	testQueue();
	testPlayer();
	std::getchar();
}