#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

enum cmd { FORWARD, UP, DOWN };
map<string, int> m;

int main() {
    ifstream readFile;
    int horizontal = 0, depth = 0, aim = 0;

    m["forward"] = cmd::FORWARD;
    m["up"] = cmd::UP;
    m["down"] = cmd::DOWN;

    string command, temp;
    int cost, pos;

    readFile.open("2_input.txt");
    if(readFile.is_open()) {
        while(!readFile.eof()) {
            getline(readFile, temp);
            pos = temp.find(' ');
            command = temp.substr(0, pos);
            temp.erase(0, pos + 1);
            cost = stoi(temp);

            switch(m[command]) {
                case cmd::FORWARD:
                    horizontal += cost;
                    cost = aim * cost;
                    depth += cost;
                    break;
                case cmd::UP:
                    aim -= cost;
                    break;
                case cmd::DOWN:
                    aim += cost;
                    break;
                default:
                    cout << "error input" << '\n';
                    break;
            }
            
        }
    }

    cout << horizontal << '\n';
    cout << depth << '\n';
    cout << horizontal * depth << '\n';

    return 0;
}