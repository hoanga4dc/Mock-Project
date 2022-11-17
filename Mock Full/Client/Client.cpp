#pragma once
#include<iostream>
#include <string>
#include <winsock2.h>
#include<winsock.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
class Client {
private:
	WSADATA	wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	int port = 5150;
	const static int bufferLength = 1024;
	char messageToServer[bufferLength];
	char messageFromServer[bufferLength];
public:
	void Init_Client() {
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

	}
	void SendData(string s) {
		send(clientSocket, s.c_str(), bufferLength, 0);
	}
	string RecvData() {
		string s;
		int b = recv(clientSocket, messageFromServer, bufferLength, 0);
		if (b > 0) {
			s = messageFromServer;
		}
		return s;
	}
	void Closesocket() {
		closesocket(clientSocket);
		WSACleanup();
	}
};