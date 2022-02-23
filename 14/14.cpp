#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

typedef long long ll;


std::unordered_map<std::string, char> rule;
void part1() {
    std::ifstream file("14_input.txt");
    std::string start, temp;
    std::queue<char> q;

    std::getline(file, start);
    int size = start.size();
    for(int i = 0; i < size; i++) {
        q.push(start[i]);
    }
    std::getline(file, temp); // \n


    while(std::getline(file, temp)) {
        rule[temp.substr(0, 2)] = temp.at(6);
    }

    std::string now("XX");
    now[0] = q.front();

    int cnt = 0;
    int step = 0;
    while(step != 20) {
        q.pop();
        cnt++;
        if(cnt == size) {
            size = size * 2 - 1;
            cnt = 0;
            q.push(now[0]);
            now[0] = q.front();
            step++;
            continue;
        }
        now[1] = q.front();
        q.push(now[0]);
        q.push(rule[now]);
                
        now[0] = now[1];
    }


    std::map<char, int> result;
    while(!q.empty()) {
        result[q.front()]++;
        q.pop();
    }

    int ans_max = 0, ans_min = INT32_MAX;
    for(auto it = result.begin(); it != result.end(); it++) {
        ans_max = std::max(ans_max, it->second);
        ans_min = std::min(ans_min, it->second);
    }
    std::cout << ans_max - ans_min << '\n';
}

void process(std::unordered_map<std::string, ll>& cnt) {
    std::queue<std::pair<std::string, ll>> q;
    for(auto it = cnt.begin(); it != cnt.end(); it++) {
        std::string front, back;
        std::string now = it->first;
        char insert = rule[now];

        front.push_back(now[0]);
        front.push_back(insert);
        back.push_back(insert);
        back.push_back(now[1]);

        q.push(std::make_pair(front, it->second));
        q.push(std::make_pair(back, it->second));
    }

    cnt.clear();

    while(!q.empty()) {
        auto data = q.front();
        q.pop();
        if(cnt.find(data.first) != cnt.end()) {
            cnt[data.first] += data.second;
        } else {
            cnt.insert(data);
        }
    }
}

void part2() {
    std::unordered_map<std::string, ll> cnt;
    std::unordered_map<char, ll> result;

    std::ifstream file("14_input.txt");
    std::string init, temp;

    std::getline(file, init);
    int size = init.size();
    char start = init[0], end = init[size - 1];

    for(int i = 0; i < size - 1; i++) {
        temp = init.substr(i, 2);
        cnt[temp] = 1;
    }
    std::getline(file, init);

    // insert rule
    while(std::getline(file, temp)) {
        rule[temp.substr(0, 2)] = temp.at(6);
    }

    for(int i = 0; i < 40; i++) {
        process(cnt);
    }

    result[start]++;
    result[end]++;
    for(auto it = cnt.begin(); it != cnt.end(); it++) {
        result[it->first[0]] += it->second;
        result[it->first[1]] += it->second;
    }

    ll max = 0, min = INT64_MAX;
    for(auto it = result.begin(); it != result.end(); it++) {
        max = std::max(max, it->second);
        min = std::min(min, it->second);
    }
    std::cout << (max - min) / 2 << '\n';
}

int main() {
    //part1();
    part2();

    return 0;
}