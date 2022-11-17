#pragma once
#include"Server.cpp"
#include"DataProcess.cpp"
#include"Player.cpp"
class Controller {
public:
	void Run() {
		shared_ptr<Server> p(new Server);
		p->Conect_MutilClientp6();
		p->CloseServer();
	}
};