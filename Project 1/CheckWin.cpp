#pragma once
class CheckWin {
public:
	CheckWin(){}
	bool Check_Horizon(int a[10][10], int x, int y) {
		int d = 0;
		for (int i = 0; i < 10; i++) {
			if (a[x][i] == a[x][y]) {
				d++;
				if (d == 4) { return true; break; }
			}
			else d = 0;
		}
		return false;
	}

	bool Check_Vertical(int a[10][10], int x, int y) {
		int d = 0;
		for (int i = 0; i < 10; i++) {
			if (a[i][y] == a[x][y]) {
				d++;
				if (d == 4) { return true; break; }
			}
			else d = 0;
		}
		return false;
	}
	bool Check_DiagonalLeft(int a[10][10], int x, int y) {
		int d = 0;
		if (x >= y) {
			for (int i = (x - y); i < 10; i++) {
				if (a[i][i - (x - y)] == a[x][y]) {
					d++;
					if (d == 4) { return true; break; }
				}
				else d = 0;
			}
		}
		if (x < y) {
			for (int j = (y - x); j < 10; j++) {
				if (a[j][j - (y - x)] == a[x][y]) {
					d++;
					if (d == 4) { return true; break; }
				}
				else d = 0;
			}
		}
		return false;

	}
	bool Check_DiagonalRight(int a[10][10], int x, int y) {
		int d = 0;
		if (y<=9-x) {
			for (int i = (9-x); i >=0; i--) {
				if (a[i][(x+y)-i] == a[x][y]) {
					d++;
					if (d == 4) { return true; break; }
				}
				else d = 0;
			}
		}
		if (y>9-x) {
			for (int j = y-(9 - x); j < 10; j++) {
				if (a[9+y-(9-x)-j][j] == a[x][y]) {
					d++;
					if (d == 4) { return true; break; }
				}
				else d = 0;
			}
		}
		return false;

	}

	bool Check_Win(int a[10][10], int x, int y) {
		if ((Check_Horizon(a, x, y)) || (Check_Vertical(a, x, y)) || (Check_DiagonalLeft(a, x, y)) || (Check_DiagonalRight(a, x, y))) {
			return true;
		}
		else return false;
	}
};