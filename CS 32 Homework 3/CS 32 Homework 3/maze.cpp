#include <string>

using namespace std;

const char WALL = 'X';
const char OPEN = '.';
const char SEEN = '+';

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
	if (sr < 0 || sr > nRows || sc < 0 || sc > nCols ||
		er < 0 || er > nRows || ec < 0 || ec > nCols ||
		maze[sr][sc] != OPEN || maze[er][ec] != OPEN){
		return false;
	}
	if (sr == er && sc == ec){
		return true;
	}
	maze[sr][sc] = SEEN;
	if (maze[sr - 1][sc] == OPEN){
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)){
			return true;
		}
	}
	if (maze[sr][sc + 1] == OPEN){
		if (pathExists(maze, nRows, nCols, sr , sc + 1, er, ec)){
			return true;
		}
	}
	if (maze[sr + 1][sc] == OPEN){
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)){
			return true;
		}
	}
	if (maze[sr][sc - 1] == OPEN){
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)){
			return true;
		}
	}
	return false;
}