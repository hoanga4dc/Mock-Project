#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<dos.h>
#include"UI.cpp"
#include"CheckWin.cpp"
#include<memory>
#include"Player.cpp"
#include"DataProcess.cpp"
#include"Match_Replay.cpp"
class Controller {
private:
	shared_ptr<UI> u;
	CheckWin Check;
public:
	void RunMatch() {
		/*DataProcess DP1;
		
		vector<shared_ptr<Player>> v1=DP1.get_ListPlayer();
		cout << v1.size() << endl;
		for (int i = 0; i < v1.size(); i++) { v1[i]->Diplay_Player(); }*/
		string player1 = u->Input_NamePlayer1();
		string player2 = u->Input_NamePlayer2();
		int x = 0;
		int y = 0;
		vector<int> temp;
		int a[10][10];
		string TimeMatch = u->Input_TimeMatch();
		u->Display_Map(a);
		int d1 = 0;
		
		while (d1==0) {
			int d = 0;
			u->Input_Xxy(a, x, y, player1);
			temp.push_back(x);
			temp.push_back(y);
			d++;
			system("cls"); 
			u->Display_Map(a);
			if (Check.Check_Win(a, x-1, y-1)) {
				
				DataProcess DP;
				shared_ptr<Player> p1(new Player);
				p1->set_Name(player1);
				p1->set_NumberWin(1);
				p1->set_NumberLose(0);
				p1->set_NumberDraw(0);
				p1->set_WinRate(1);
				DP.Inser_DataPlayer(p1);

				shared_ptr<Player> p2(new Player);
				p2->set_Name(player2);
				p2->set_NumberWin(0);
				p2->set_NumberLose(1);
				p2->set_NumberDraw(0);
				p2->set_WinRate(0);
				DP.Inser_DataPlayer(p2);

				u->Notification_Win(player1);
				d1++;
				break;
			}
			u->Input_Oxy(a, x, y, player2); d++;
			temp.push_back(x);
			temp.push_back(y);
			system("cls");
			u->Display_Map(a);
			if (Check.Check_Win(a, x-1, y-1)) {
				DataProcess DP2;
				shared_ptr<Player> p1(new Player);
				p1->set_Name(player2);
				p1->set_NumberWin(1);
				p1->set_NumberLose(0);
				p1->set_NumberDraw(0);
				p1->set_WinRate(1);
				DP2.Inser_DataPlayer(p1);

				shared_ptr<Player> p2(new Player);
				p2->set_Name(player1);
				p2->set_NumberWin(0);
				p2->set_NumberLose(1);
				p2->set_NumberDraw(0);
				p2->set_WinRate(0);
				DP2.Inser_DataPlayer(p2);


				u->Notification_Win(player2);
				d1++;
				break;
			}
			if (d == 100) {
				DataProcess DP2;
				shared_ptr<Player> p1(new Player);
				p1->set_Name(player2);
				p1->set_NumberWin(0);
				p1->set_NumberLose(0);
				p1->set_NumberDraw(1);
				p1->set_WinRate(0);
				DP2.Inser_DataPlayer(p1);

				shared_ptr<Player> p2(new Player);
				p2->set_Name(player1);
				p2->set_NumberWin(0);
				p2->set_NumberLose(0);
				p2->set_NumberDraw(1);
				p2->set_WinRate(0);
				DP2.Inser_DataPlayer(p2);
				u->Notification_Draw();
				d1++;
				break;
			}
		}
		shared_ptr<Match_Replay> M(new Match_Replay);
		M->set_Player1(player1);
		M->set_Player2(player2);
		M->set_TimeMatch(TimeMatch);
		M->set_Step(temp);
		/*cout << M->get_Player1() << endl;
		cout << M->get_Player2() << endl;*/
		DataProcess D;
		D.Insert_MatchReplay(M);
	}
	void DisplayPlayers() {
		cout << "Danh sach cac nguoi choi:\n";
		vector<shared_ptr<Player>> v;
		shared_ptr<DataProcess> DP(new DataProcess);
		v = DP->get_ListPlayer();
		for (int i = 0; i < v.size(); i++) {
			cout << i << "." << v[i]->get_Name() << endl;
		}
		cout << "Choose one of list!";
		int k = 0;
		cin >> k;
		v[k]->Diplay_Player();
		for (int i = 0; i < v.size(); i++) {
			if (i != k) {
				if ((v[i]->get_WinRate()==v[k]->get_WinRate())||((v[i]->get_WinRate() < (v[k]->get_WinRate() * 1.1)) && ((v[i]->get_WinRate() > (v[k]->get_WinRate() * 0.9))))) {
					cout << "nguoi choi co ty le thang gan tuong duong:\n";
					v[i]->Diplay_Player();
				}
			}
		}
	}
	void Display_Relays() {
		DataProcess DP;
		vector<shared_ptr<Match_Replay>> v=DP.get_ListMatchReplays();
		for (int i = 0; i < v.size(); i++) {
			cout << i << ".\n";
			v[i]->Display();
			cout << "-----------------\n";
		}
		cout << "choose one match to view^^";
		int k = 0;
		cin >> k;
		cin.ignore();
		vector<int> step;
		step = v[k]->get_Step();
		/*cout << step.size();
		for (int i = 0; i < step.size(); i++) { cout << step[i] << " "; }*/
		int k2 = 1;
		int d = 0;
		int a[10][10];
		while (d < step.size()-2) {
			if (k2==1)
			{
				a[step[d] - 1][step[d + 1] - 1] = 1;
				k2 = 2;
			}

			else if(k2 == 2) { 
				a[step[d] - 1][step[d + 1] - 1] = 2; 
				k2 = 1; }
			system("cls");
			if (k2 == 2) { cout << v[k]->get_Player1() << " turn\n"; }
			if (k2 == 1) { cout << v[k]->get_Player2() << " turn\n"; }
			u->Display_Map(a);
			Sleep(600);
			d += 2;
		}
		if (k2 == 2) { cout << v[k]->get_Player1() << " Win\n"; }
		if (k2 == 1) { cout << v[k]->get_Player2() << " Win\n"; }

	}
	

};