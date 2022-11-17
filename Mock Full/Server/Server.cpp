#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include <string>
#include <winsock2.h>
#include<thread>
#include"DataProcess.cpp"

using namespace std;
class Server {
private:
	int port = 5150;
	const static int BUFFER_LENGHT = 1024;
	SOCKET serverSocket, clientSocketAccepted;
	SOCKADDR_IN ServerAddr, clientAddr;
	string msgFromClientOut;
	char msgFromClient[BUFFER_LENGHT];
	int iresult;
	WSADATA wsaData;
	vector<SOCKET>v;
	fd_set master;
	vector<SOCKET> MatchQueue;
	vector<shared_ptr<Player>> PlayerQueue;
	DataProcess Data;
public:
	Server() {}
	void Init_Serer() {
		iresult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iresult != 0) {
			cout << "WSAFATA error!";
		}
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (serverSocket == INVALID_SOCKET) {
			cout << "create socket error!";
			WSACleanup();
		}
		else { cout << "create socket is oke!"; }

		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_port = htons(port);
		ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		int ServerAddrSize = sizeof(ServerAddr);

		iresult = bind(serverSocket, (LPSOCKADDR)&ServerAddr, ServerAddrSize);
		if (iresult == SOCKET_ERROR) {
			cout << "bind() failed! Error";
			closesocket(serverSocket);
			WSACleanup();
		}
		else { cout << "blind() complete!\n"; }
	}
	//----------------------------------------------------------------
	string RecvDataFormClient(SOCKET s) {
		int b=recv(s, msgFromClient, BUFFER_LENGHT, 0);
		if (b <= 0) {
			closesocket(clientSocketAccepted);
			WSACleanup();
		}
		string s1 = msgFromClient;
		return s1;

	}
	void SendDataToClient(string s,SOCKET k) {
		send(k, s.c_str(), BUFFER_LENGHT, 0);
	}
	//---------------------------------------------------------------------
	void RequestImf() {
		while (1) {
			for (int i = 0; i < v.size(); i++) {
				string s;
				s=RecvDataFormClient(v[i]);
				if (s[0]=='#') {
					string st;
					for (int j = 1; j < s.size(); j++) {
						st = st + s[j];
					}
					DataProcess DP;
					vector<shared_ptr<Player>> v1;
					v1 = DP.get_ListPlayer();

					for (int j = 0; j < v1.size(); j++) {
						if (v1[j]->get_Name() == st) {
							st = st + "okela";
							SendDataToClient(st,v[i]);
						}
					}
				}
				else { break; }

				/*if (s[0] = '@') {
					string st;
					for (int j = 1; j < s.size(); j++) {
						st = st + s[j];
					}
					cout << st << endl;
					DataProcess DP;
					vector<shared_ptr<Player>> p;
					p = DP.get_ListPlayer();
					for (int i = 0; i < p.size(); i++) {
						if (p[i]->get_Name() == st) {
							string temp = (p[i]->get_Name()) + "@" + ((to_string(p[i]->get_NumberWin()))) + "@" + (to_string(p[i]->get_NumberLose())) + "@" + (to_string(p[i]->get_NumberDraw())) + "@" + (to_string(p[i]->get_WinRate()));
							SendDataToClient(temp, v[i]);
						}
					}
				}*/

			}
			
		}
	}
	void RunMatch_Online(SOCKET a,SOCKET b,string Player1,string Player2) {
		string s1 = "O";
		string s2 = "X";
		send(a, s1.c_str(), s1.size() + 1, 0);
		send(b, s2.c_str(), s2.size() + 1, 0);
		int d = 0;
		int NumberStep = 0;
		while (d == 0&&NumberStep<50) {
			NumberStep++;
			string temp1 = RecvDataFormClient(a);
			if (temp1[0] == '@') {
				d++; 
				SendDataToClient(temp1, b);
				shared_ptr<Player> p1(new Player);
				shared_ptr<Player> p2(new Player);
				p1->set_Name(Player1);
				p1->set_NumberWin(1);
				p1->set_NumberLose(0);
				p1->set_NumberDraw(0);
				p1->set_WinRate(1);
				Data.Inser_DataPlayer(p1);
				p2->set_Name(Player2);
				p2->set_NumberWin(0);
				p2->set_NumberLose(1);
				p2->set_NumberDraw(0);
				p2->set_WinRate(0);
				Data.Inser_DataPlayer(p2);
				break;
			}
			else { SendDataToClient(temp1, b); }
			string temp2 = RecvDataFormClient(b);
			if (temp2[0]=='@') {
				d++; 
				SendDataToClient(temp2, a);
				shared_ptr<Player> p1(new Player);
				shared_ptr<Player> p2(new Player);
				p1->set_Name(Player1);
				p1->set_NumberWin(0);
				p1->set_NumberLose(1);
				p1->set_NumberDraw(0);
				p1->set_WinRate(0);
				Data.Inser_DataPlayer(p1);
				p2->set_Name(Player2);
				p2->set_NumberWin(1);
				p2->set_NumberLose(0);
				p2->set_NumberDraw(0);
				p2->set_WinRate(1);
				Data.Inser_DataPlayer(p2);
				break; 
			}
			else { SendDataToClient(temp2, a); }		
		}
	}
	void StartMatchOnline() {
		int k = 0;
		while (k == 0) {
			/*if (PlayerQueue.size() == 2) {


					if (PlayerQueue[0]->get_WinRate() == PlayerQueue[1]->get_WinRate() || (((PlayerQueue[0]->get_WinRate()) < PlayerQueue[1]->get_WinRate() * 1.1) && ((PlayerQueue[0]->get_WinRate()) > PlayerQueue[1]->get_WinRate() * 0.9))) {
						RunMatch_Online(MatchQueue[0], MatchQueue[1]);
						MatchQueue.erase(MatchQueue.begin());
						MatchQueue.erase(MatchQueue.begin());
						PlayerQueue.erase(PlayerQueue.begin());
						PlayerQueue.erase(PlayerQueue.begin());

					}

			}*/int max = PlayerQueue.size();
			if (max > 1) {
				if (PlayerQueue.size() == max) {
					//int d = 0;
					//while (d == 0) {
						/*if (PlayerQueue.size() == 2) {

							if (PlayerQueue[0]->get_WinRate() == PlayerQueue[1]->get_WinRate() || (((PlayerQueue[0]->get_WinRate()) < PlayerQueue[1]->get_WinRate() * 1.1) && ((PlayerQueue[0]->get_WinRate()) > PlayerQueue[1]->get_WinRate() * 0.9))) {
								RunMatch_Online(MatchQueue[0], MatchQueue[1]);
									MatchQueue.erase(MatchQueue.begin());
									MatchQueue.erase(MatchQueue.begin());
									PlayerQueue.erase(PlayerQueue.begin());
									PlayerQueue.erase(PlayerQueue.begin());
							}
						}*/
					int x = 0, y = 0;
					for (int i = 0; i < max; i++) {
						for (int j = 0; j < max; j++) {
							if (PlayerQueue[i]->get_WinRate() == PlayerQueue[j]->get_WinRate() || (((PlayerQueue[i]->get_WinRate()) < PlayerQueue[j]->get_WinRate() * 1.1) && ((PlayerQueue[i]->get_WinRate()) > PlayerQueue[j]->get_WinRate() * 0.9)))
							{
								if (i != j) {
									//d++;
									x = i;
									y = j;
								}
							}
						}

					}
					if (x != y) {
						cout << x << " " << y;
						RunMatch_Online(MatchQueue[x], MatchQueue[y],PlayerQueue[x]->get_Name(),PlayerQueue[y]->get_Name());
						if (x < y) {
							MatchQueue.erase(MatchQueue.begin() + x);
							PlayerQueue.erase(PlayerQueue.begin() + x);
							MatchQueue.erase(MatchQueue.begin() + y - 1);
							PlayerQueue.erase(PlayerQueue.begin() + y - 1);
						}
						else {
							MatchQueue.erase(MatchQueue.begin() + y);
							PlayerQueue.erase(PlayerQueue.begin() + y);
							MatchQueue.erase(MatchQueue.begin() + x - 1);
							PlayerQueue.erase(PlayerQueue.begin() + x - 1);
						}
					}
					else { 
						//continue;
						cout << "";
					}
					//if (x != 0 && y != 0 && x != y) {
					//	RunMatch_Online(MatchQueue[x], MatchQueue[y]);
					//	//RunMatch_Online(MatchQueue[0], MatchQueue[1]);
					//	///*closesocket(MatchQueue[0]);
					//	//closesocket(MatchQueue[1]);*/
					//	MatchQueue.erase(MatchQueue.begin() + x);
					//	MatchQueue.erase(MatchQueue.begin() + y - 1);
					//}
				//}
				}
			}
		}
		
	}
	void Login() {
		while (1) {
			DataProcess DP;
			
			fd_set copy = master;
			int soketCount = select(0, &copy, nullptr, nullptr, nullptr);
			for (int i = 0; i < soketCount; i++) {
				SOCKET sock = copy.fd_array[i];
				if (sock == serverSocket) {
					//accept a new connection
					SOCKET client = accept(serverSocket, nullptr, nullptr);
					v.push_back(client);
					//if (v.size() > 3) { d++; }
					//Add the new connection to the list of connect
					FD_SET(client, &master);
					//send a welcome message to the connected client
					string s = "welcome to server\n";
					send(client, s.c_str(), s.size() + 1, 0);

				}
				else {

					int byteIn = recv(sock, msgFromClient, BUFFER_LENGHT, 0);
					if (byteIn <= 0) {
						//drop the client
						closesocket(sock);
						FD_CLR(sock, &master);
					}
					else {
						vector<shared_ptr<Player>> listPlayer;
						listPlayer = DP.get_ListPlayer();
						string temp = msgFromClient;
						if (temp[0] == '$') {
							string acount;
							for (int i = 1; i < temp.size(); i++) {
								acount += temp[i];
							}
							int d = 0;
							for (int j = 0; j < listPlayer.size();j++) {
								if (listPlayer[j]->get_Name() == acount) {
									listPlayer[j]->Diplay_Player();
									PlayerQueue.push_back(listPlayer[j]);
									MatchQueue.push_back(sock);
									d++;
									string temp = "Ok";
									send(sock, temp.c_str(), temp.size() + 1, 0);

								}
							}
							if (d==0){
								string temp = "No imf";
								send(sock, temp.c_str(), temp.size() + 1, 0);
							}
						}
						else {
							int d = 0;
							for (int i = 0; i < listPlayer.size(); i++) {
								if (listPlayer[i]->get_Name() == temp) {
									cout << "Get Login request form " << listPlayer[i]->get_Acount() << endl;
									string temp2 = (listPlayer[i]->get_Acount()) + "@" + ((to_string(listPlayer[i]->get_NumberWin()))) + "@" + (to_string(listPlayer[i]->get_NumberLose())) + "@" + (to_string(listPlayer[i]->get_NumberDraw())) + "@" + (to_string(listPlayer[i]->get_WinRate()));
									send(sock, temp2.c_str(), temp2.size() + 1, 0);
									d++;
								}
							}
							if (d == 0) {
								string temp = "No imf";
								send(sock, temp.c_str(), temp.size() + 1, 0);
							}
						}
					}

					/*for (int i = 0; i < master.fd_count; i++) {
						SOCKET outsock = master.fd_array[i];
						if (outsock != serverSocket && outsock != sock) {
							send(outsock, msgFromClient, byteIn, 0);
						}
					}*/
				}
			}
		}
	}
	
	void Conect_MutilClientp6() {
		Init_Serer();
		int listen_status = listen(serverSocket, 4);
		FD_ZERO(&master);
		FD_SET(serverSocket, &master);
		thread t1(&Server::Login, this);
		thread t2(&Server::StartMatchOnline, this);
		t1.join();
		t2.join();
	}

		/*for (int i = 0; i < v.size(); i++) {
			listPlayer2[i]->Diplay_Player();
			string temp=(listPlayer2[i]->get_Name()) + "@" + ((to_string(listPlayer2[i]->get_NumberWin())))+"@"+ (to_string(listPlayer2[i]->get_NumberLose())) + "@" + (to_string(listPlayer2[i]->get_NumberDraw()))+"@" + (to_string(listPlayer2[i]->get_WinRate()));
			SendDataToClient(temp, v[i]);
		}*/
	
	//void p6() {
	//	Init_Serer();
	//	thread t1(&Server::Conect_MutilClientp6,this);
	//	thread t2(&Server::RequestImf,this);
	//	t1.join();
	//	t2.join();

	//}
	void CloseServer() {
		closesocket(clientSocketAccepted);
		WSACleanup();
		cout << "Close Server!\n";
	}
};