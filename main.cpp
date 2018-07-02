#include<future>
#include<vector>
#include<queue>
#include<functional>
#include<iostream>

struct task {
	task(std::shared_future<int> call, int time) :
		call(call),
		time(time) { }

	std::shared_future<int> call;
	int time;

	const bool operator<(const task& right)
	{
		return this->time < right.time;
	}
};

std::function<bool(task, task)> cmp = [](task left, task right) {
	return left.time > right.time;
};

std::priority_queue<task, std::vector<task>, std::function<bool(task, task)>> queue(cmp);

int runLater(int x)
{
	std::cout << "Currently running with x = " << x << std::endl;
	return x + 4;
}

int main()
{
	task t1(std::async(std::launch::deferred, runLater, 3), 2);
	task t2(std::async(std::launch::deferred, runLater, 5), 1);

	queue.push(t1);
	queue.push(t2);

	while (!queue.empty())
	{
		task t = queue.top();
		queue.pop();
		std::cout << "At time " << t.time << " a value of " << t.call.get() << " was returned\n";
	}
	std::getchar();
}