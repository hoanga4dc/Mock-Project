#pragma once
#include<iostream>
#include<string>
using namespace std;
class Player {
private:
	string name;
	int NumberWin = 0;
	int NumberLose = 0;
	int NumberDraw = 0;
	double WinRate = 0;
public:
	Player() {}
	void set_Name(string s) {
		this->name = s;
	}
	void set_NumberWin(int a) { this->NumberWin = a; }
	void set_NumberLose(int a) { this->NumberLose = a; }
	void set_NumberDraw(int a) { this->NumberDraw = a; }
	void set_WinRate(double a) { this->WinRate = a; }

	//get information
	string get_Name() { return name; }
	int get_NumberWin() { return NumberWin; }
	int get_NumberLose() { return NumberLose; }
	int get_NumberDraw() { return NumberDraw; }
	double get_WinRate() { return WinRate; }

	void Diplay_Player() {
		cout << "Ten:" << get_Acount() << endl;
		cout << "So tran thang:" << get_NumberWin() << endl;
		cout << "So tran thua:" << get_NumberLose() << endl;
		cout << "So tran hoa:" << get_NumberDraw() << endl;
		cout << "Ty le thang:" << get_WinRate() * 100 << "%" << endl;
	}
	string get_Acount() {
		string temp;
		for (int i = 0; i < name.size(); i++) {
			if (name[i] != '%') {
				temp += name[i];
			}
			else break;
		}
		return temp;
	}
};