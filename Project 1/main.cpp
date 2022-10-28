#include "UI.cpp"
#include"Controller.cpp"
int main() {
	shared_ptr<Controller> Q(new Controller);
	Q->Run();
	return 0;
}