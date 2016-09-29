#include <queue>
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
	queue<Coord> queueStack;
	queueStack.push(Coord(sr, sc));
	maze[sr][sc] = '+';
	while (!queueStack.empty()){
		Coord temp = queueStack.front();
		queueStack.pop();
		cout << temp.r() << ", " << temp.c() << endl;
		if (temp.r() == er && temp.r() == ec){
			return true;
		}
		if (maze[temp.r() - 1][temp.c()] == '.'){
			queueStack.push(Coord(temp.r() - 1, temp.c()));
			maze[temp.r() - 1][temp.c()] = '+';
		}
		if (maze[temp.r()][temp.c() + 1] == '.'){
			queueStack.push(Coord(temp.r(), temp.c() + 1));
			maze[temp.r()][temp.c() + 1] = '+';
		}
		if (maze[temp.r() + 1][temp.c()] == '.'){
			queueStack.push(Coord(temp.r() + 1, temp.c()));
			maze[temp.r() + 1][temp.c()] = '+';
		}
		if (maze[temp.r()][temp.c() - 1] == '.'){
			queueStack.push(Coord(temp.r(), temp.c() - 1));
			maze[temp.r()][temp.c() - 1] = '+';
		}
	}
	return false;
}

int main(){
	string maze2[10] = {
		"XXXXXXXXXX'",
		"X.X..X...X'",
		"XXXX.X.XXX'",
		"X....X.X.X'",
		"XX.X.X...X'",
		"XXX..X.X.X'",
		"X...X...XX'",
		"X.XX..X.XX'",
		"X....X...X'",
		"XXXXXXXXXX'",
	};
	cout << pathExists(maze2, 10, 0, 8, 6, 1, 1);
}