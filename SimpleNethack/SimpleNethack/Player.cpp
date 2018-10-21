
#include "Player.h"



Player::Player(std::string user, Map & map)
{
	username = user;
	pos_x = 1;
	pos_y = 1;
	HP = Max_HP;
	step = 0;
	weapon = 2;
	helmat = false;
	food = 0;
	map.setting(pos_x, pos_y, '@');
}

void Player::next_pos(const char &direct) {
	switch (direct) {
	case'U':pos_y = pos_y - 1;
		break;
	case'H':pos_x = pos_x - 1;
		break;
	case'N':pos_y = pos_y + 1;
		break;
	case'K':pos_x = pos_x + 1;
		break;
	case'M':pos_x = pos_x + 1;
		pos_y = pos_y + 1;
		break;
	case'I':pos_x = pos_x + 1;
		pos_y = pos_y - 1;
		break;
	case'B':pos_x = pos_x - 1;
		pos_y = pos_y + 1;
		break;
	case'Y':pos_x = pos_x - 1;
		pos_y = pos_y - 1;
		break;
	default: break;
	}
}

void Player::Move(Map &map, char ch) {
	int origin_x = pos_x;
	int origin_y = pos_y;
	next_pos(ch);
	if (map.getpos(pos_x, pos_y) == 'W') {
		map.setting(origin_x, origin_y, '.');
		map.setting(pos_x, pos_y, '@');
		++weapon;
		++step;
	}
	if (map.getpos(pos_x, pos_y) == 'H') {
		map.setting(origin_x, origin_y, '.');
		map.setting(pos_x, pos_y, '@');
		helmat = true;
		++step;
	}
	if (map.getpos(pos_x, pos_y) == 'F') {
		map.setting(origin_x, origin_y, '.');
		map.setting(pos_x, pos_y, '@');
		++food;
		++step;
	}
	if (map.getpos(pos_x, pos_y) == '.') {
		map.setting(origin_x, origin_y, '.');
		map.setting(pos_x, pos_y, '@');
		++step;
	}
	if (map.getpos(pos_x, pos_y) == '*' || map.getpos(pos_x, pos_y) == ' ' || map.getpos(pos_x, pos_y) == 'M') {
		pos_x = origin_x;
		pos_y = origin_y;
	}
}

void Player::Relax() {
	cout << "Relaxing...\n";
	step++;
}

void Player::Attack(const char& direct, Map &map, Monster& mon) {
	if (weapon == 0) {
		cout << "You don't have any weapon now\n";
		return;
	}
	int origin_x = pos_x;
	int origin_y = pos_y;
	next_pos(direct);
	char a = map.getpos(pos_x, pos_y);
	if (a == 'M') {
		--weapon;
		mon.Attacked(map);
		cout << "You hit the monster!\n";
	}
	else {
		--weapon;
	}
	pos_x = origin_x;
	pos_y = origin_y;
    ++step;
}

void Player::Attacked(int degree) {
	if(degree == 1) HP -= 2;
	if (helmat) HP += 1;//头盔的作用在此
}

void Player::Pick(Map &map, Weapon& wea, Equip &equ) {
	if (map.getpos(pos_x, pos_y) == 'W') {
		weapon++;
		wea.disappear(map);
       cout << "You have got a sword, and now you have " << weapon << " swords.\n";
	}
	if (map.getpos(pos_x, pos_y) == 'F') {
		cout << "You have got a food.\n";
		equ.delefood(map);
	}
	if (map.getpos(pos_x, pos_y) == 'H') {
		cout << "You have got a helmat.\n";
		equ.deleHel(map);
	}
}

void Player::Die(bool * alive, Map & map) {
	cout << "GoodBye! " << username << endl;
	map.setting(pos_x, pos_y, '.');
	*(alive) = false;
}

void Player::run(Map &map, Monster& mon, bool * alive) {
	if (HP <= 0) Die(alive, map);
	char ch = _getch();
	if (ch == 'H' || ch == 'M' || ch == 'K' || ch == 'I' || ch == 'Y' || ch == 'U' || ch == 'B' || ch == 'N') {
		Move(map, ch);
	}
	if (ch == 'T') {
		cout << "Please choose a direction to attack\n";
		char dir = _getch();
		Attack(dir, map, mon);
	}
	if (ch == 'R') {
		Relax();
	}
	if (ch == 'E') {
		cout << "Do you want to eat?(Y/N)" << endl;
		char an = _getch();
		if (an == 'Y') {
			HP += 5;
		}
	}
}
Weapon::Weapon() {
	sword = 0;
	wpos_x = 0;
	wpos_y = 0;
}
void Weapon::appear(Map &map){
	int orin_x = wpos_x;
	int orin_y = wpos_y;
	wpos_x = rand() % 20 + 1;
	wpos_y = rand() % 10 + 1;
	if (map.getpos(wpos_x, wpos_y) == '.') {
		map.setting(wpos_x, wpos_y, 'W');
	}
	else {
		wpos_x = orin_x;
		wpos_y = orin_y;
	}
}
void Weapon::disappear(Map &map) {
	map.setting(wpos_x, wpos_y, '.');
}
void Equip::Setfood(Map&map) {
	int orin_x = fpos_x;
	int orin_y = fpos_y;
	fpos_x = rand() % 20 + 1;
	fpos_y = rand() % 10 + 1;
	if (map.getpos(fpos_x, fpos_y) == '.') {
		map.setting(fpos_x, fpos_y, 'F');
	}
	else {
		fpos_x = orin_x;
		fpos_y = orin_y;
	}
}
void Equip::SetHel(Map&map) {
	int orin_x = hpos_x;
	int orin_y = hpos_y;
	hpos_x = rand() % 20 + 1;
	hpos_y = rand() % 10 + 1;
	if (map.getpos(hpos_x, hpos_y) == '.') {
		map.setting(hpos_x, hpos_y, 'H');
	}
	else {
		hpos_x = orin_x;
		hpos_y = orin_y;
	}
}
void Equip::delefood(Map & map) {
	map.setting(fpos_x, fpos_y, '.');
}
void Equip::deleHel(Map & map) {
	map.setting(hpos_x, hpos_y, '.');
}