#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <cmath>
using namespace std;

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

typedef struct Point {
    int x, y;
}Point;

map<pair<int, int>, int> cnt;

void Solve(Point p1, Point p2) {
    int low, high;
    
    if(p1.x == p2.x) {
        low = MIN(p1.y, p2.y);
        high = MAX(p1.y, p2.y);

        for(int i = low; i <= high; i++) {
            cnt[make_pair(p1.x, i)]++;
        }
    } 
    else {
        low = MIN(p1.x, p2.x);
        high = MAX(p1.x, p2.x);

        for(int i = low; i <= high; i++) {
            cnt[make_pair(i, p1.y)]++;
        }
    }
}

void diagonal(Point p1, Point p2) { // p1->p2
    int xdir = 0, ydir = 0;
    if (p1.x < p2.x) xdir = 1;
    if (p1.y < p2.y) ydir = 1;

    int i = p1.x, j = p1.y;
    while(i != p2.x) {
        cnt[make_pair(i, j)]++;

        if(xdir == 1) i++;
        else i--;

        if(ydir == 1) j++;
        else j--;
    }
    cnt[make_pair(i, j)]++;
}

int main() {
    string temp;
    ifstream readFile;
    readFile.open("5_input.txt");

    regex re("(\\d+),(\\d+) -> (\\d+),(\\d+)");
    smatch match;

    if(readFile.is_open()) {
        Point p1, p2;
        while(!readFile.eof()) {
            getline(readFile, temp);
            if(regex_match(temp, match, re)) {
                p1.x = stoi(match[1].str()); p1.y = stoi(match[2].str());
                p2.x = stoi(match[3].str()); p2.y = stoi(match[4].str());

                //cout << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << '\n';

                if(abs(p1.x - p2.x) == abs(p1.y - p2.y)) diagonal(p1, p2);
                if(p1.x != p2.x && p1.y != p2.y) continue;
                Solve(p1, p2);
            }
        }
    }

    int ans = 0;
    for(auto it = cnt.begin(); it != cnt.end(); it++) {
        if (it->second > 1) ans++;
    }
    cout << ans << '\n';

    return 0;
}