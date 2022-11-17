#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Match_Replay {
private:
	string Player1;
	string Player2;
	string TimerMatch;
	vector<int> Step;
public:
	Match_Replay() {}
	//set informtion
	void set_Player1(string s) { this->Player1 = s; }
	void set_Player2(string s) { this->Player2 = s; }
	void set_TimeMatch(string s) { this->TimerMatch = s; }
	void set_Step(vector<int>v) { this->Step = v; }

	//get information
	string get_Player1() { return Player1; }
	string get_Player2() { return Player2; }
	string get_TimerMatch() { return TimerMatch; }
	vector<int> get_Step() { return Step; }
	//display
	void Display() {
		cout << "player 1:" << Player1 << endl;
		cout << "player 2:" << Player2 << endl;
		cout << "Time Match:" << TimerMatch << endl;
	}
};