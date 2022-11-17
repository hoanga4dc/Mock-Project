#pragma once
#include<iostream>
#include"Player.cpp"
#include<fstream>
#include<memory>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
class DataProcess {
public:
	DataProcess() {}
	vector<shared_ptr<Player>> get_ListPlayer() {
		vector<shared_ptr<Player>> v;
		ifstream ifs("D:/Code C++/MOCK PROJECT/ConsoleApplication1/ConsoleApplication1/Player.txt");
		while (!ifs.eof()) {
			shared_ptr<Player> p(new Player);
			char temp[255];
			int x = 0;
			double y = 0;

			ifs.getline(temp, 255); string s = temp;
			p->set_Name(s);

			ifs.getline(temp, 255);
			x = atoi(temp);
			/*stringstream s1n(s);
			s1n >> x;*/
			p->set_NumberWin(x);

			ifs.getline(temp, 255); s = temp;
			stringstream s2n(s);
			s2n >> x;
			p->set_NumberLose(x);

			ifs.getline(temp, 255); s = temp;
			stringstream s3n(s);
			s3n >> x;
			p->set_NumberDraw(x);

			ifs.getline(temp, 255); s = temp;
			stringstream s4n(s);
			s4n >> y;
			p->set_WinRate(y);
			if ((p->get_Acount() != "") || (p->get_NumberWin() != 0) || (p->get_NumberLose() != 0) || (p->get_NumberDraw() != 0)) { v.push_back(p); }
		}
		ifs.close();
		return v;
	}
	void Inser_DataPlayer(shared_ptr<Player> p) {

		vector<shared_ptr<Player>> v = get_ListPlayer();
		//v.push_back(p);
		if (v.size() == 0) { v.push_back(p); }
		if (v.size() > 0) {
			int d = 0;
			for (int i = 0; i < v.size(); i++) {
				if (v[i]->get_Name() == p->get_Name()) {
					d++;
					v[i]->set_NumberWin(v[i]->get_NumberWin() + p->get_NumberWin());
					v[i]->set_NumberLose(v[i]->get_NumberLose() + p->get_NumberLose());
					v[i]->set_NumberDraw(v[i]->get_NumberDraw() + p->get_NumberDraw());
					v[i]->set_WinRate(double(v[i]->get_NumberWin()) / double((v[i]->get_NumberWin() + v[i]->get_NumberLose() + v[i]->get_NumberDraw())));
				}
			}
			if (d == 0) { v.push_back(p); }
		}

		ofstream ofs("D:/Code C++/MOCK PROJECT/ConsoleApplication1/ConsoleApplication1/Player.txt", ostream::out);
		for (int i = 0; i < v.size(); i++) {

			ofs << v[i]->get_Name() << endl;
			ofs << v[i]->get_NumberWin() << endl;
			ofs << v[i]->get_NumberLose() << endl;
			ofs << v[i]->get_NumberDraw() << endl;
			ofs << v[i]->get_WinRate() << endl;


		}
		ofs.close();
	}

	//void Insert_MatchReplay(shared_ptr<Match_Replay> p) {
	//	ofstream ofs("D:/Code C++/MOCK PROJECT/ConsoleApplication1/ConsoleApplication1/Replays.txt", ostream::app);
	//	if (ofs.fail()) { cout << "failtowite!"; }
	//	ofs << p->get_Player1() << endl;
	//	ofs << p->get_Player2() << endl;
	//	ofs << p->get_TimerMatch() << endl;
	//	for (int i = 0; i < (p->get_Step().size()); i++) {
	//		ofs << p->get_Step()[i] << " ";
	//	}
	//	ofs << "$" << endl;
	//	ofs.close();
	//}
	vector<int> get_ListStep(string s) {
		vector<int> v;
		int d = 0;
		string temp = "";
		while (d < s.size()) {
			if (s[d] != ' ') {
				temp += s[d];
			}
			if ((s[d] == ' ') || (s[d] == '$')) {
				int x = 0;
				stringstream s2n(temp);
				s2n >> x;
				v.push_back(x);
				temp = "";
			}
			d++;

		}
		return v;
	}
	/*vector<shared_ptr<Match_Replay>> get_ListMatchReplays() {
		vector<shared_ptr<Match_Replay>> v;
		ifstream ifs("D:/Code C++/MOCK PROJECT/ConsoleApplication1/ConsoleApplication1/Replays.txt");
		while (!ifs.eof()) {
			shared_ptr<Match_Replay> p(new Match_Replay);
			char temp[500];
			ifs.getline(temp, 500);
			string s = temp;
			p->set_Player1(s);

			ifs.getline(temp, 500);
			s = temp;
			p->set_Player2(s);

			ifs.getline(temp, 500); s = temp;
			p->set_TimeMatch(s);

			ifs.getline(temp, 500); s = temp;
			p->set_Step(get_ListStep(s));
			if ((p->get_Player1() != "") && (p->get_TimerMatch() != "")) { v.push_back(p); }
		}
		ifs.close();
		return v;
	}*/
	/*bool Check_ExistPlayer(shared_ptr<Player> p) {
		vector<shared_ptr<Player>> v;
		v = get_ListPlayer();
		for (int i = 0; i < v.size(); i++) {
			if (v[i]->get_Name() == p->get_Name()) {
				return false;
			}
		}
		return true;
	}*/
	bool Check_ExistAcount(string s) {
		vector<shared_ptr<Player>> v;
		v = get_ListPlayer();
		for (int i = 0; i < v.size(); i++) {
			if (v[i]->get_Name() == s) {
				return true;
			}
		}
		return false;
	}

};