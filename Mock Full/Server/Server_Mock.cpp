#include"Controller.cpp"
int main() {
	shared_ptr<Controller> C(new Controller);
	//while (1) {
		C->Run();
	//}
	return 0;
}