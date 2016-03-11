/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>

using namespace std;

int main() {
	int width, st, inst_size;
	string inst, board;
	cin >> width >> st;
	cin >> inst;
	board = "$" + inst;
	cin >> inst_size >> inst;
	cout << board[st];
	for(auto &c: inst) {
		if(c == 'R') {
			st++;
		} else {
			st--;  
		}
		cout << board[st];
	} cout << '\n';
	return 0;
}
