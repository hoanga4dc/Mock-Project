#pragma once
#include"Controller.cpp"
class Menu {
public:
	void Run() {
		shared_ptr<Controller> C(new Controller);
		int d2 = 0;
		while (d2 == 0) {
			cout << "1. Register new Acount\n";
			cout << "2. Play Game\n";
			cout << "3. Display information of players\n";
			cout << "4. View Replays\n";
			int k = 0;
			cin >> k;
			cin.ignore();
			switch (k) {
			case 1: {system("cls"); C->Register(); break; }
			case 2: {system("cls"); C->RunMatch(); break; }
			case 3: {system("cls"); C->DisplayPlayers(); break; }
			case 4: {system("cls"); C->Display_Relays(); break; }
			}
		}
	}
};