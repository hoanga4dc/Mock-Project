#include "UI.cpp"
#include"Controller.cpp"
#include"Menu.cpp"
int main() {
	shared_ptr<Menu> M(new Menu);
	M->Run();
	return 0;
}
//#include"Controller.cpp"
//	int main() {
//		shared_ptr<Controller> p(new Controller);
//		while (true) {
//			cout << "5. Login \n";
//			cout << "6. Find Match\n";
//			int k = 0;
//			cin >> k;
//			cin.ignore();
//			switch (k) {
//			case 5: {system("cls"); p->testP5(); break; }
//			case 6: {system("cls"); p->testP6(); break; }
//			}
//			
//		}
//		return 0;
//	}