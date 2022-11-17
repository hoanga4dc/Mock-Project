#pragma once
#ifdef _WIN32

#else
#include <unistd.h>
#endif
#include"client.cpp"
#include <Windows.h>
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
	void Register() {
		DataProcess DP;
		shared_ptr<Player> p1(new Player);

		p1->set_Name(u->Register_Acount());
		p1->set_NumberWin(0);
		p1->set_NumberLose(0);
		p1->set_NumberDraw(0);
		p1->set_WinRate(0);
		DP.Inser_DataPlayer(p1);
		cout << "Dang ky thanh cong! ^_^\n";
	}
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
		cout << v.size() << endl;
		for (int i = 0; i < v.size(); i++) {
			cout << i << "." << v[i]->get_Acount() << endl;
		}
		cout << "Choose one of list!";
		int k = 0;
		cin >> k;
		v[k]->Diplay_Player();
		cout << "nguoi choi co ty le thang gan tuong duong:\n";
		for (int i = 0; i < v.size(); i++) {
			if (i != k) {
				if ((v[i]->get_WinRate()==v[k]->get_WinRate())||((v[i]->get_WinRate() < (v[k]->get_WinRate() * 1.1)) && ((v[i]->get_WinRate() > (v[k]->get_WinRate() * 0.9))))) {
					
					v[i]->Diplay_Player();
					cout << "_____________________\n";
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
	/*void Login() {
		WSADATA	wsaData;
		SOCKET clientSocket;
		SOCKADDR_IN clientAddr;
		int clientAddrSize = sizeof(clientAddr);
		int port = 5150;
		const int bufferLength = 1024;
		char messageToServer[bufferLength];
		char messageFromServer[bufferLength];
		int b = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (b != 0)
		{
			cout << "Client: WSAStartup failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
		}
		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (clientSocket == INVALID_SOCKET)
		{
			cout << "Client: Error at socket(): " << WSAGetLastError() << endl;
			WSACleanup();
		}

		clientAddr.sin_family = AF_INET;
		clientAddr.sin_port = htons(port);
		clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		int connect_status = connect(clientSocket, (SOCKADDR*)&clientAddr, clientAddrSize);
		if (connect_status == SOCKET_ERROR) {
			closesocket(clientSocket);
			clientSocket = INVALID_SOCKET;
		}
		int d = 0;
		while (d == 0) {
			string s = "hello world";
			send(clientSocket, s.c_str(), bufferLength, 0);
			Sleep(1000);
		}
	
	}*/
	void Login(){
		cout << "dang request to Server!\n";
		string temp = "Imf";
		shared_ptr<Client> C1(new Client);
		C1->Init_Client();
		C1->SendData(temp);
		string s;
		s = C1->RecvData();
		if (s == "okela") {
			cout << "nhap ten dang nhap:";
			string s1;
			getline(cin, s1);
			C1->SendData(s1);
			shared_ptr<Player> p(new Player);
			s1=C1->RecvData();
			cout << s1 << endl;
			s1 = C1->RecvData();
			cout << s1 << endl;
			s1 = C1->RecvData();
			cout << s1 << endl;
			s1 = C1->RecvData();
			cout << s1 << endl;
			s1 = C1->RecvData();
			cout << s1 << endl;

		}
		
	}
	void testP5() {
		DataProcess DP;
		shared_ptr<Client> C1(new Client);
		C1->Init_Client();
		//->SendData("Imf");
		cout << C1->RecvData() << endl;
		
		string s, s1, s2;
				cout << "nhap ten dang nhap:";
				getline(cin, s1);
				cout << "nhap mat khau:";
				getline(cin, s2);
				C1->SendData(s1 + "%" + s2);
				string temp = C1->RecvData();
					if (temp == "No imf") {
						cout << "Tai khoan khong ton tai hoac mat khau sai!\n";
					}
					else { DP.DisplayConvertPlayer(temp); }
			/*getline(cin, s);
			C1->SendData(s);*/
	}
	void testP6() {
		shared_ptr<Client> C1(new Client);
		C1->Init_Client();
		string s = C1->RecvData();
		string s1, s2;
		cout << s << endl;
		int ValidLogin = 0;
		while (ValidLogin == 0) {
			cout << "Insert Acount:";
			getline(cin, s1);
			cout << "Insert Password:";
			getline(cin, s2);

			C1->SendData("$" + s1 + "%" + s2);
			string temp = C1->RecvData();
			if (temp == "No imf") {
				cout << "Tai khoan khong ton tai hoac mat khau sai!\n";
			}
			else {
				ValidLogin++;
			}
		}
		cout << "Looking for match...\n";
		string Chess = C1->RecvData();
		cout << "Successful pairing\nMaYou are "<< Chess << endl;
		if (Chess == "O") {
			int x=0, y=0;
			DataProcess DP;
			int a[10][10];
			string step;
			int d = 0;
			while (d==0) {
				cin >> x >> y;
				step = Chess + to_string(x)+" "+to_string(y);
				DP.ProcessStep(step, a);
				system("cls");
				u->Display_Map(a);
				if (Check.Check_Win(a, x - 1, y - 1)) {
					cout << "YOU WIN!";
					d++;
					C1->SendData("@"+step);
					break;

					
				}
				C1->SendData(step);
			
				step= C1->RecvData();
				if (step[0] != '@') {
					DP.ProcessStep(step, a);
					system("cls");
					u->Display_Map(a);
				}
				if (step[0] == '@') {
					string temp;
					for (int i = 1; i < step.size(); i++) {
						temp += step[i];
					}
					DP.ProcessStep(temp, a);
					system("cls");
					u->Display_Map(a);
					cout << "YOU LOSE!";
					d++;
					break;
				}
			}
		}
		if (Chess == "X") {
			int x=0, y=0;
			int a[10][10];
			DataProcess DP;
			string step;
			int d = 0;
			while (d==0) {
				step = C1->RecvData();
				if (step[0] != '@') {
					DP.ProcessStep(step, a);
					system("cls");
					u->Display_Map(a);
				}
				if (step[0] == '@') {
					string temp;
					for (int i = 1; i < step.size(); i++) {
						temp += step[i];
					}
					DP.ProcessStep(temp, a);
					system("cls");
					u->Display_Map(a);
					cout << "YOU LOSE!";
					d++;
					break;
				}
				cin >> x >> y;
				step = Chess + to_string(x) +" " + to_string(y);
				DP.ProcessStep(step, a);
				system("cls");
				u->Display_Map(a);
				if (Check.Check_Win(a, x - 1, y - 1)) {
					cout << "YOU WIN!";
					d++;
					C1->SendData("@"+step);
					break;
					
				}
				C1->SendData(step);
			}
		}

	}
	

};