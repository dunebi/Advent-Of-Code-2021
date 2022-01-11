#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef struct {
    int sum = 0;
    int rowSum[5] = {0, };
    int colSum[5] = {0, };
    map<int, pair<int, int>> board; // board[number] = (row, col)
}BingoBoard;

vector<int> v;
vector<BingoBoard> boardvec;

int main() {
    ifstream readFile;
    string temp;
    readFile.open("4_input.txt");

    if(readFile.is_open()) {
        getline(readFile, temp); // Bingo Number
        istringstream numbers(temp);
        while(getline(numbers, temp, ',')) {
            v.push_back(stoi(temp));
        }

        int i = 0, j = 0;
        BingoBoard tempBoard;
        while(!readFile.eof()) {
            getline(readFile, temp);
            if(temp == "") continue;

            istringstream numbers(temp);
            while(getline(numbers, temp, ' ')) {
                if (temp == "") continue;
                int num = stoi(temp);
                tempBoard.sum += num;
                tempBoard.board[num].first = i;
                tempBoard.board[num].second = j;
                j++;
            }

            i++; j = 0; // i : row, k : col
            if(i == 5) {
                boardvec.push_back(tempBoard);
                tempBoard = {};
                i = 0; j = 0;
            }
        }
    }

    // Start Bingo
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < boardvec.size(); j++) {
            int num = v[i];
            if (boardvec[j].board.find(num) == boardvec[j].board.end()) continue; // num not in bingo board

            int rownum = boardvec[j].board[num].first;
            int colnum = boardvec[j].board[num].second;
            boardvec[j].rowSum[rownum]++;
            boardvec[j].colSum[colnum]++;
            boardvec[j].sum -= num;

            if(boardvec[j].rowSum[rownum] == 5 || boardvec[j].colSum[colnum] == 5) {
                if(boardvec.size() == 1) { // last
                    cout << "sum: " << boardvec[j].sum << '\n';
                    cout << "now called: " << num << '\n';
                    cout << "mult: " << boardvec[j].sum * num << '\n';
                    exit(0);
                }
                boardvec.erase(boardvec.begin() + j);
                j--;
                /* part1
                cout << "board: " << j << '\n';
                cout << "sum: " << boardvec[j].sum << '\n';
                cout << "now called: " << num << '\n';
                cout << "mult: " << boardvec[j].sum * num << '\n';
                exit(0);
                */
            }
        }
    }

    return 0;
}