#include "scheduling.h"

void scheduler::run()
{
	while (!this->queue.empty())
	{
		task t = this->queue.top();
		this->queue.pop();
		this->cur_time = t.time;
		t.call.get();
	}
}

void scheduler::schedule(task t)
{
	this->queue.push(t);
}

comparator cmp = [](task t1, task t2) {
	return t1.time > t2.time;
};

q_scheduler queue(cmp);
scheduler sched = { queue, 0 };