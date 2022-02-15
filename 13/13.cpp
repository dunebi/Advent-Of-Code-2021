#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

typedef struct Point{
    int x, y;
    bool operator<(const Point& rhs) const {
        if(y != rhs.y) {
            return y < rhs.y;
        }
        return x < rhs.x;
    }
}Point;



void part1() {
    int maxX = 0, maxY = 0;
    std::map<Point, int> m;
    std::queue<Point> q;
    std::ifstream file("13_input.txt");
    std::string temp;
    std::string divC = ",";

    while(std::getline(file, temp)) { // 좌표
        if(temp == "") break;
        int pos = temp.find(divC);

        Point p = {
            std::stoi(temp.substr(0, pos)),
            std::stoi(temp.substr(pos + 1))
        };
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
        m.insert(std::make_pair(p, 1));
    }

    while(std::getline(file, temp)) { // 접는위치
        int xpos = temp.find("x=");
        int ypos = temp.find("y=");
        if(xpos != std::string::npos) { // x=? 을 기준으로 접을때
            Point p = {
                std::stoi(temp.substr(xpos + 2)),
                -1
            };
            q.push(p);
        } else { // y=? 을 기준으로 접을때
            Point p = {
                -1,
                std::stoi(temp.substr(ypos + 2))
            };
            q.push(p);
        }
    }

    while(!q.empty()) {
        Point p = q.front();

        Point temp;
        if(p.y == -1) { // x = ?을 기준으로 접을 때
            for(auto it = m.begin(); it != m.end(); it++) {
                if(it->first.x <= p.x || it->first.y > maxY) continue; // 범위에 해당되지 않음

                temp.y = it->first.y;
                int gap = std::abs(it->first.x - p.x);
                temp.x = p.x - gap;
                m[temp]++;

                maxX = p.x - 1;
            }
        } else { // y = ?을 기준으로 접을 때
            for(auto it = m.begin(); it != m.end(); it++) {
                if(it->first.y <= p.y || it->first.x > maxX) continue;

                temp.x = it->first.x;
                int gap = std::abs(it->first.y - p.y);
                temp.y = p.y - gap;
                m[temp]++;

                maxY = p.y - 1;
            }
        }
        q.pop();
    }

    int cnt = 0;
    for(int i = 0; i <= maxX; i++) {
        for(int j = 0; j <= maxY; j++) {
            Point p = {i, j};
            if(m[p] != 0) {
                cnt++;
            }
        }
    }

    std::cout << cnt << '\n';

    // 접을 것들 큐로 출력함
    // int qSize = q.size();
    // for (int i = 0; i < qSize; i++) {
    //     std::cout << q.front().x << ' ' << q.front().y << '\n';
    //     q.pop();
    // }

}

void part2() {
        int maxX = 0, maxY = 0;
    std::map<Point, int> m;
    std::queue<Point> q;
    std::ifstream file("13_input.txt");
    std::string temp;
    std::string divC = ",";

    while(std::getline(file, temp)) { // 좌표
        if(temp == "") break;
        int pos = temp.find(divC);

        Point p = {
            std::stoi(temp.substr(0, pos)),
            std::stoi(temp.substr(pos + 1))
        };
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
        m.insert(std::make_pair(p, 1));
    }

    while(std::getline(file, temp)) { // 접는위치
        int xpos = temp.find("x=");
        int ypos = temp.find("y=");
        if(xpos != std::string::npos) { // x=? 을 기준으로 접을때
            Point p = {
                std::stoi(temp.substr(xpos + 2)),
                -1
            };
            q.push(p);
        } else { // y=? 을 기준으로 접을때
            Point p = {
                -1,
                std::stoi(temp.substr(ypos + 2))
            };
            q.push(p);
        }
    }

    while(!q.empty()) {
        Point p = q.front();

        Point temp;
        if(p.y == -1) { // x = ?을 기준으로 접을 때
            for(auto it = m.begin(); it != m.end(); it++) {
                if(it->first.x <= p.x || it->first.y > maxY) continue; // 범위에 해당되지 않음

                temp.y = it->first.y;
                int gap = std::abs(it->first.x - p.x);
                temp.x = p.x - gap;
                m[temp]++;

                maxX = p.x - 1;
            }
        } else { // y = ?을 기준으로 접을 때
            for(auto it = m.begin(); it != m.end(); it++) {
                if(it->first.y <= p.y || it->first.x > maxX) continue;

                temp.x = it->first.x;
                int gap = std::abs(it->first.y - p.y);
                temp.y = p.y - gap;
                m[temp]++;

                maxY = p.y - 1;
            }
        }
        q.pop();
    }

    for(int i = 0; i <= maxY; i++) {
        for(int j = 0; j <= maxX; j++) {
            Point p = {j, i};
            if(m[p] != 0) {
                std::cout << '#' << ' ';
            } else std::cout << '.' << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    //part1();
    part2();


    return 0;
}