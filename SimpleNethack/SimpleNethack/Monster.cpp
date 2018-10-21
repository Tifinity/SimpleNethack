
#include "Monster.h"
#include"Player.h"
#include"Map.h"
#include <cstdlib>
#include <ctime>
Monster::Monster(Map &map) {
	HP = max_mHP;
	Set(map);
}

void Monster::next_pos(char dir) {
	switch (dir) {
	case 8: mpos_y--; break;
	case 4: mpos_x--; break;
	case 2: mpos_y++; break;
	case 6: mpos_x++; break;
	case 7: {mpos_x--; mpos_y--; break; }
	case 9: {mpos_x++; mpos_y--; break; }
	case 1: {mpos_x--; mpos_y++; break; }
	case 3: {mpos_x++; mpos_y++; break; }
	default: break;
	}
}

void Monster::Move(Player& p, Map &map, int instance) {
	int ori_x = mpos_x;
	int ori_y = mpos_y;
	for (int i = 1; i <= 9; i++) {
		next_pos(i);
		if ((map.getpos(mpos_x, mpos_y) == '.') && (GetInstance(p) < instance)) {
			map.setting(ori_x, ori_y, '.');
			map.setting(mpos_x, mpos_y, 'M');
			break;
		}
		else {
			mpos_x = ori_x;
			mpos_y = ori_y;
		}
	}
}

void Monster::Set(Map& map) {
	mpos_x = rand() % 20 + 1;
	mpos_y = rand() % 10 + 1;
	while (map.getpos(mpos_x, mpos_y) != '.') {
		mpos_x = rand() % 20 + 1;
		mpos_y = rand() % 10 + 1;
	}
	map.setting(mpos_x, mpos_y, 'M');
}

void Monster::Attack(Player& player, Map &map) {
	player.Attacked(1);
}

void Monster::Attacked(Map &map) {
	HP -= 5;
	if (HP <= 0) {
	Die(map);
	}
}
void Monster::Die(Map& map) {
	//Set(map);/*Ç°¸°ºó¼Ì*/
	map.setting(mpos_x, mpos_y, '.');
	HP = max_mHP;
	Set(map);
}

int Monster::GetInstance(Player &p) {
	return abs(mpos_x - p.Getx()) + abs(mpos_y - p.Gety());
}

void Monster::Act(Map &map, Player &p) {
	int ins = GetInstance(p);
	//cout << HP;
	if (HP <= 0) Die(map);
	if (ins == 1) Attack(p, map);
	if (ins > 1) Move(p, map, ins);
}