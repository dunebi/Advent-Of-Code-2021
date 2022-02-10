#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

class graph {
private:
    std::map<std::string, std::set<std::string>> cave; // graph
    std::map<std::string, int> visit_cnt;
    bool smallCave2 = true;
public:
    graph();

    void addEdge(std::string n1, std::string n2);
    int getPath(std::string now);
    int getPath2(std::string now);

    void print();
};

graph::graph() {
    cave.clear();
}

void graph::addEdge(std::string n1, std::string n2) {
    cave[n1].insert(n2);
    cave[n2].insert(n1);
}

int graph::getPath(std::string now) {
    if(now == "end") {
        return 1;
    }
    int cnt = 0;
    visit_cnt[now]++;

    for(auto it = cave[now].begin(); it != cave[now].end(); it++) {
        std::string next = *it;
        if(next == "start") continue;

        if(islower(next[0]) && visit_cnt[next] == 1) continue;

        cnt += getPath(next);
    }


    visit_cnt[now]--;
    return cnt;
}

int graph::getPath2(std::string now) {
    if(now == "end") {
        return 1;
    }
    int cnt = 0;
    visit_cnt[now]++;
    //smallCave2 = (visit_cnt[now] != 2);

    for(auto it = cave[now].begin(); it != cave[now].end(); it++) {
        std::string next = *it;
        if(next == "start") continue;

        if(islower(next[0]) && visit_cnt[next] == 1 && smallCave2 == true) {
            smallCave2 = false;
            cnt += getPath2(next);
            smallCave2 = true;
            continue;
        } else if(islower(next[0]) && visit_cnt[next] >= 1 && smallCave2 == false) {
            continue;
        } else {
            cnt += getPath2(next);
        }
    }

    visit_cnt[now]--;
    return cnt;
}

void graph::print() {
    for(auto it = cave.begin(); it != cave.end(); it++) {
        std::cout << it->first << ": ";
        for(auto jt = it->second.begin(); jt != it->second.end(); jt++) {
            std::cout << *jt << ' ';
        }
        std::cout << '\n';
    }
}

void part1() {
    graph* g = new graph();

    std::ifstream file("12_input.txt");
    std::string temp;
    std::string divC = "-";

    while(std::getline(file, temp)) {
        int pos = temp.find(divC);
        
        g->addEdge(temp.substr(0, pos), temp.substr(pos + 1));
    }
    g->print();
    std::cout << g->getPath("start") << '\n';

    delete g;
}

void part2() {
    graph* g = new graph();

    std::ifstream file("12_input.txt");
    std::string temp;
    std::string divC = "-";

    while(std::getline(file, temp)) {
        std::cout << temp << '\n';
        int pos = temp.find(divC);
        
        g->addEdge(temp.substr(0, pos), temp.substr(pos + 1));
    }
    //g->print();
    std::cout << g->getPath2("start") << '\n';

    delete g;
}

int main() {
    //part1();
    part2();

    return 0;
}

// int isupper(int c) -> 대문자 판별. 대문자가 아닐 시 0이 아닌 정수를 return 