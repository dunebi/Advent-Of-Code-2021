#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 987654321

void part1() {
    std::ifstream file("15_input.txt");
    std::string temp;
    std::vector<std::string> board;

    while(std::getline(file, temp)) {
        board.push_back(temp);
    }

    int row = board.size(), col = board[0].size();
    int dp[row + 1][col + 1];

    for(int i = 0; i <= row; i++) dp[i][0] = MAX;
    for(int i = 0; i <= col; i++) dp[0][i] = MAX;

    for(int i = 1; i <= row; i++) {
        for(int j = 1; j <= col; j++) {
            if(i == 1 && j == 1) {
                dp[i][j] = 0;
                continue;
            }
            int risk = board[i - 1][j - 1] - '0';
            dp[i][j] = std::min(dp[i - 1][j] + risk, dp[i][j - 1] + risk);
        }
    }

    std::cout << dp[row][col] << '\n';
}

int getRisk(int i, int j, int row, int col, std::vector<std::string> board) {
    int addOn = ((i - 1) / row) + ((j - 1) / col);
    int risk = board[(i - 1) % row][(j - 1) % col] - '0';
    risk += addOn;
    if(risk > 9) risk = (risk + 1) % 10;

    return risk;
}

void part2() {
    std::ifstream file("15_input.txt");
    std::string temp;
    std::vector<std::string> board;

    while(std::getline(file, temp)) {
        board.push_back(temp);
    }

    int row = board.size(), col = board[0].size(); // 실제: row*5, col*5
    int cost[row * 5 + 1][col  * 5 + 1];
    
    //init cost
    for(int i = 0; i <= row * 5; i++) {
        for(int j = 0; j <= col * 5; j++) {
            cost[i][j] = MAX;
        }
    }

    cost[1][1] = 0;

    std::priority_queue<std::pair<int, std::pair<int, int>>> pq; // (risk합계, (row, col))
    pq.push(std::make_pair(0, std::make_pair(1, 1)));

    while(!pq.empty()) {
        auto point = pq.top();
        pq.pop();

        int now_cost = -point.first;
        int i = point.second.first;
        int j = point.second.second;
        if(now_cost > cost[i][j]) continue;

        // (i, j) -> (i, j + 1)
        if((j + 1) <= col * 5 && cost[i][j + 1] > cost[i][j] + getRisk(i, j + 1, row, col, board)) {
            cost[i][j + 1] = cost[i][j] + getRisk(i, j + 1, row, col, board);
            pq.push(std::make_pair(-cost[i][j + 1], std::make_pair(i, j + 1)));
        }
        
        // (i, j) -> (i, j - 1)
        if((j - 1) > 0 && cost[i][j - 1] > cost[i][j] + getRisk(i, j - 1, row, col, board)) {
            cost[i][j - 1] = cost[i][j] + getRisk(i, j - 1, row, col, board);
            pq.push(std::make_pair(-cost[i][j - 1], std::make_pair(i, j - 1)));
        }

        // (i, j) -> (i + 1, j)
        if((i + 1) <= row * 5 && cost[i + 1][j] > cost[i][j] + getRisk(i + 1, j, row, col, board)) {
            cost[i + 1][j] = cost[i][j] + getRisk(i + 1, j, row, col, board);
            pq.push(std::make_pair(-cost[i + 1][j], std::make_pair(i + 1, j)));
        }

        // (i, j) -> (i - 1, j)
        if((i - 1) > 0 && cost[i - 1][j] > cost[i][j] + getRisk(i - 1, j, row, col, board)) {
            cost[i - 1][j] = cost[i][j] + getRisk(i - 1, j, row, col, board);
            pq.push(std::make_pair(-cost[i - 1][j], std::make_pair(i - 1, j)));
        }
    }

    std::cout << cost[row * 5][col * 5] << '\n';
}

int main() {
    part2();

    return 0;
}