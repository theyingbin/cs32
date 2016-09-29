#include <stack>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
	stack<Coord> cordStack;
	cordStack.push(Coord(sr, sc));
	maze[sr][sc] = '+';
	while (!cordStack.empty()){
		Coord temp = cordStack.top();
		cordStack.pop();
		if (temp.r() == er && temp.r() == ec){
			return true;
		}
		if (maze[temp.r() - 1][temp.c()] == '.'){
			cordStack.push(Coord(temp.r() - 1, temp.c()));
			maze[temp.r() - 1][temp.c()] = '+';
		}
		if (maze[temp.r()][temp.c() + 1] == '.'){
			cordStack.push(Coord(temp.r(), temp.c() + 1));
			maze[temp.r()][temp.c() + 1] = '+';
		}
		if (maze[temp.r() + 1][temp.c()] == '.'){
			cordStack.push(Coord(temp.r() + 1, temp.c()));
			maze[temp.r() + 1][temp.c()] = '+';
		}
		if (maze[temp.r()][temp.c() - 1] == '.'){
			cordStack.push(Coord(temp.r(), temp.c() - 1));
			maze[temp.r()][temp.c() - 1] = '+';
		}
	}
	return false;
}
