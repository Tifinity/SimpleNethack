#pragma once
#define max_mHP 10
#include"Map.h"
#include"Player.h"
class Player;
class Map;
class Monster
{
	int mpos_x;
	int mpos_y;
	int HP;
public:
	Monster(Map&map);
	void Set(Map&);
	void Attack(Player&, Map&);
	void Attacked(Map&);
	void Die(Map&);
	void Act(Map&, Player&);
	void next_pos(char dir);
	void Move(Player& p, Map&map, int instance);
	int GetInstance(Player&p);
};
