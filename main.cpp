#include<future>
#include<vector>
#include<queue>
#include<functional>
#include<iostream>

struct task {
	std::shared_future<int> call;
	int time;
};

using comparator = std::function<bool(task, task)>;
using scheduler = std::priority_queue<task, std::vector<task>, comparator>;

comparator cmp = [](task left, task right) {
	return left.time > right.time;
};
scheduler queue(cmp);

int runLater(int x)
{
	std::cout << "Currently running with x = " << x << std::endl;
	return x + 4;
}

int main()
{
	task t1 = { std::async(std::launch::deferred, runLater, 3), 2 };
	task t2 = { std::async(std::launch::deferred, runLater, 5), 1 };

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