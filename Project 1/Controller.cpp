#pragma once
#include"UI.cpp"
#include"CheckWin.cpp"
#include<memory>
class Controller {
private:
	string player1;
	string player2;
	int x=0;
	int y=0;
	int a[10][10];
	shared_ptr<UI> u;
	CheckWin Check;
public:
	void Input_NamePlayer() {
		player1 = u->Input_NamePlayer1();
		player2 = u->Input_NamePlayer2();
	}
	void Input_X() {
		u->Input_Xxy(a,x,y,player1);
		
	}
	void Input_O() {
		u->Input_Oxy(a,x,y,player2);
	}
	void Display_Map() {
		u->Display_Map(a);
	}
	void Run() {
		Input_NamePlayer();
		Display_Map();
		while (true) {
			Input_X(); 
			system("cls"); 
			Display_Map();
			if (Check.Check_Win(a, x-1, y-1)) {
				u->Notification_Win(player1);
				exit(0);
			}
			Input_O();
			system("cls");
			Display_Map();
			if (Check.Check_Win(a, x-1, y-1)) {
				u->Notification_Win(player2);
				exit(0);
			}
		}
	}

};