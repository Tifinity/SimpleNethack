
#include "Map.h"
#include"Player.h"
#include<iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;
/*Map::Map() {

}*/

void Map::showMap(Player &play) {
	int i = 0;
	for (; i < 12; ++i) {
		cout << map[i] << endl;
	}
	cout << endl;
	cout << play;
}

void Map::setting(int x, int y, char c) {
	map[y][x] = c;
}

char Map::getpos(int x, int y) {
	return map[y][x];
}
ostream & operator<<(ostream& os, Player &play) {
	os << "Player: " << play.username << "   ";
	os << "HP:" << play.HP << "\n";
	os << "Step: " << play.step << "   ";
	os << "Weapon: " << play.weapon << "\n";
	os << "Food: " << play.food << "\n";
	os << "Helmat" << play.helmat ? "Wearing\n" : "None\n";
	return os;
}