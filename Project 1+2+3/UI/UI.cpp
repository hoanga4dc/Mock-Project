#pragma once
#include<string>
#include<iostream>
#include<memory>
using namespace std;
class UI {
public:
	UI() {}
	string Input_NamePlayer1() {
		cout << "Nhap ten nguoi choi 1:";
		string s;
		getline(cin, s);
		return s;
	}
	string Input_NamePlayer2() {
		cout << "Nhap ten nguoi choi 2:";
		string s;
		getline(cin, s);
		return s;
	}
	string Input_TimeMatch() {
		cout << "Insert time match:";
		string s;
		getline(cin, s);
		return s;
	}
	void Notification_Win(string A) {
		cout << A << " Win!\n";
	}
	void Notification_Draw() {
		cout << "Draw!\n";
	}
	int Input_X() {
		int x = 0;
		cin >> x;
		return x;
	}
	int Input_Y() {
		int x = 0;
		cin >> x;
		return x;
	}
	//Display Map
	void Display_Map(int a[10][10]) {
		for (int i = 0; i < 10; i++) {
			cout << "\n-----------------------------------------\n";
			for (int j = 0; j < 10; j++) {
				if (a[i][j] == 1) { cout << "| X "; }
				else if (a[i][j] == 2) { cout << "| O "; }
				else { cout << "|   "; }
				if (j == 9) { cout << "|"; }
			}

		}
		cout << "\n-----------------------------------------\n";
	}
	//Insert X
	void Input_Xxy(int a[10][10], int& c, int& d, string A) {
		cout << A << " turn:";
		int x = UI::Input_X();
		int y = UI::Input_Y();
		if ((a[x - 1][y - 1] == 1) || (a[x - 1][y - 1] == 2) || (x < 1) || (x > 10) || (y > 10) || (y < 1)) {
			cout << "Pointer was existed!\n";
			cout << "Nhap lai toa do:\n";
			UI::Input_Xxy(a, c, d, A);
		}
		else { a[x - 1][y - 1] = 1; c = x; d = y; }
	}
	//Insert O
	void Input_Oxy(int a[10][10], int& c, int& d, string A) {
		cout << A << " turn:";
		int x = UI::Input_X();
		int y = UI::Input_Y();
		if ((a[x - 1][y - 1] == 1) || (a[x - 1][y - 1] == 2) || (x < 1) || (x > 10) || (y > 10) || (y < 1)) {
			cout << "Pointer was existed!\n";
			cout << "Nhap lai toa do:\n";
			UI::Input_Oxy(a, c, d, A);
		}
		else {
			a[x - 1][y - 1] = 2; c = x; d = y;
		}
	}

};