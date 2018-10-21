#pragma once
#define MAX_length 12
#define MAX_width 21
#include"Player.h"
#include"Monster.h"
#include<iostream>
using namespace std;
class Map {
	char map[MAX_length][MAX_width] = {
		"*************       ",
		"*...........*       ",
		"*............*      ",
		"*............**     ",
		"*..............*    ",
		" *.............***  ",
		"*****............* ",
		"     *.............*",
		"*****..............*",
		"*..................*",
		"*..................*",
		"********************"
	};
public:
	//Map();
	void showMap(Player&);
	void setting(int x, int y, const char c);
	char getpos(int x, int y);
	friend ostream& operator <<(ostream & os, Player& play);
};

