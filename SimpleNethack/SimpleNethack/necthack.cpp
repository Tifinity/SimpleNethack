
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<string>
#include"Player.h"
#include"Map.h"
#include"Monster.h"

using namespace std;
bool running = true;
bool* run = &running;
int main() {
	string username;
	cout << "Who are you ?";
	cin >> username;
	Map mymap;
	Monster mymon(mymap);
	Player me(username, mymap);
	Weapon mywea;
	Equip myequ;
	while (running) {
		system("cls");
		mymap.showMap(me);
		me.run(mymap, mymon, run);//人动一下
		if (me.GetStep() % 2 == 0)mymon.Act(mymap, me);//怪动半下
		if (me.GetStep() % 10 == 0) mywea.appear(mymap);
		if (me.GetStep() % 15 == 0) myequ.Setfood(mymap);
		if (me.GetStep() % 20 == 0) myequ.SetHel(mymap);
		//mymon.Attack(me, mymap);
	}
	return 0;
}
