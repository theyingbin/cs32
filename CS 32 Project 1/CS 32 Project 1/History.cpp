#include "History.h"
#include <iostream>
#include "globals.h"
#include <cstdlib>

using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < nCols; j++){
			m_ary[i][j] = '.';
		}
	}
}
bool History::record(int r, int c){
	if (r < 1 || r > m_rows ||
		c < 1 || c > m_cols    ){
		return false;
	}
	if (m_ary[r-1][c-1] == 'Z'){
		return true;
	}
	else if (m_ary[r-1][c-1] == '.'){
		m_ary[r-1][c-1] = 'A';
	}
	else{
		m_ary[r-1][c-1]++;
	}
	return true;
}
void History::display() const 
{
	clearScreen();
	for (int i = 0; i < m_rows; i++){
		for (int j = 0; j < m_cols; j++){
			cout << m_ary[i][j];
		}
		cout << endl;
	}
	cout << endl;
}