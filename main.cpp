#include<future>
#include<vector>
#include<queue>
#include<functional>
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include "Player.h"
#include "scheduling.h"
#include "Map.h"
#include "Graphics.h"
#include "Game.h"

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

	sched.schedule(t1);
	sched.schedule(t2);

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
	// Player p1("Player 1", 25, 10, 3, 3, 21, 12, 8, 20, R);
	// Player p2("Player 2", 30, 5, 7, 2, 5, 25, 30, 17, R);

	// p1.attack(p2);
	// p2.attack(p1);

	sched.run();
}

void testGraphics()
{
	Map m(32, 32);
	m.makeBlank();
	int R[NUM_RESIST] = { 0, 0, 0, 0, 0 };
	// Player p1("Player 1", 25, 10, 3, 3, 21, 12, 8, 20, R);
	// Player p2("Player 2", 30, 5, 7, 2, 5, 25, 30, 17, R);

	// p1.location = Point(3, 5);
	// p2.location = Point(6, 9);
	// system("cls");
	// Graphics g(m, { &p1, &p2 });
	// g.showMap();
	
}

void testLog()
{
	Map m(32, 32);
	m.makeBlank();
	int R[NUM_RESIST] = { 0, 0, 0, 0, 0 };
	Player p1("Player 1", 25, 10, 3, 3, 21, 12, 8, 20, VAMP, R);
	Player p2("Player 2", 30, 5, 7, 2, 5, 25, 30, 17, VAMP, R);

	Graphics g(m, { &p1, &p2 });
	g.log("Hello, world!");
	g.log("Goodbye, world!");
}

void testGame()
{
	Map m(32, 32);
	m.makeBlank();

	int R[NUM_RESIST] = { 0, 0, 0, 0, 0 };
	Player p1("Manav", 299, 10, 1, 15, 25, 20, 75, 27, VENOM, R);
	Player p2("Raghav", 242, 20, 1, 15, 30, 12, 57, 20, FLAME, R);
	p1.location = { 5, 10 };
	p1.ai.type = CTRL_WASD;
	p2.location = { 20, 20 };
	p2.ai.type = CTRL_ARROW;
	
	Game game(m, { &p1, &p2 });
	sched.schedule({ std::async(std::launch::deferred, &Game::getPlayerTurn, game, &p1), 0 });
	sched.schedule({ std::async(std::launch::deferred, &Game::getPlayerTurn, game, &p2), 0 });
	p1.scheduleHeal();
	p2.scheduleHeal();
	sched.run();

}

int main()
{
	/*srand(time(0));
	testQueue();
	testPlayer();
	testGraphics();
	std::getchar();*/

	testGame();
	std::getchar();
}