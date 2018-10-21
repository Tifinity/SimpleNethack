#pragma once
#define Max_HP 20
#include<string>
#include<conio.h>
#include<iostream>
#include"Map.h"
#include"Monster.h"

using std::string;
using std::cout;
using std::endl;
class Map;
class Equip;
class Monster;
class Weapon;

class Player
{
public:
	string username;
	int pos_x;
	int pos_y;
	int HP;
	int step;
	int weapon;
	int food;
	bool helmat;
	Player(string user, Map &map);
	int Getx() { return pos_x; }
	int Gety() { return pos_y; }
	int GetStep() { return step; }
	void next_pos(const char &direct);
	void Move(Map& map, char);
	void Relax();
	void Attack(const char& direct, Map&, Monster&);
	void Attacked(int degree);
	void Pick(Map&, Weapon&, Equip&);
	void Die(bool *, Map&);
	void run(Map&, Monster&, bool*);
	friend class Map;
};
class Weapon {
	int sword;
	int wpos_x;
	int wpos_y;
public:
	Weapon();
	void appear(Map&);
	void disappear(Map&);
};
class Equip {
	int food;
	int helmat;
	int fpos_x, fpos_y;
	int hpos_x, hpos_y;
public:
	void Setfood(Map&);
	void SetHel(Map&);
	void delefood(Map&);
	void deleHel(Map&);
};