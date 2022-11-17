#pragma once
#include<string>
#include<iostream>
#include<memory>
#include"DataProcess.cpp"
using namespace std;
class UI {
	DataProcess Data;
public:
	UI() {}
	string Register_Acount() {
		cout << "Nhap tai khoan nguoi choi moi:";
		string acount, pass;
		getline(cin, acount);
		if (Data.Check_ExistAcount(acount)) {
			cout << "Tai khoan da ton tai!, xin nhap lai:\n";
			return Register_Acount();
		}
		cout << "Nhap mat khau:";
		getline(cin , pass);
		string s = acount + '%' + pass;
		return s;
	}
	string Input_NamePlayer1() {
		cout << "Insert Acount 1:";
		string s,s1,s2;
		getline(cin, s1);
		cout << "Insert Password:";
		getline(cin, s2);
		s = s1 + "%" + s2;
		if (!Data.Check_ExistAcount(s)) { 
			cout << "Acount khong ton tai!, nhap lai:\n";
			return Input_NamePlayer1(); }
		return s;
	}
	string Input_NamePlayer2() {
		cout << "Insert Acount 2:";
		string s, s1, s2;
		getline(cin, s1);
		cout << "Insert Password:";
		getline(cin, s2);
		s = s1 + "%" + s2;
		if (!Data.Check_ExistAcount(s)) { 
		cout << "Acount khong ton tai!, nhap lai:\n"; 
		return Input_NamePlayer2(); }
		return s1;
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