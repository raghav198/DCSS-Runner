#pragma once

#include<future>
#include<vector>
#include<queue>
#include<functional>

struct task {
	std::shared_future<int> call;
	int time;
};

using comparator = std::function<bool(task, task)>;
using q_scheduler = std::priority_queue<task, std::vector<task>, comparator>;

struct scheduler {
	q_scheduler queue;
	int cur_time;

	void run();
	void schedule(task);
};