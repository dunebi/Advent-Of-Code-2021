#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void part1() {
    ifstream file("10_input.txt");
    string temp;
    map<char, char> pair;
    map<char, int> score;
    int ans = 0;

    pair['['] = ']'; score[']'] = 57;
    pair['{'] = '}'; score['}'] = 1197;
    pair['('] = ')'; score[')'] = 3;
    pair['<'] = '>'; score['>'] = 25137;
    
    if(!file.is_open()) {
        cout << "Error open input txt file" << '\n';
        exit(1);
    }

    while(getline(file, temp)) {
        stack<char> s;

        for(int i = 0; i < temp.size(); i++) {
            char c = temp.at(i);

            if(c == ']' || c == '}' || c == ')' || c == '>') {
                char comp = pair[s.top()];
                if(c == comp) s.pop();
                else { //error detect
                    ans += score[c];
                    break;
                }

            } else {
                s.push(c);
            }
        }

    }

    cout << ans << '\n';
}

void part2() {
    ifstream file("10_input.txt");
    string temp;
    map<char, char> pair;
    map<char, int> score;
    map<ll, int> cnt;
    
    int ans = 0;

    pair['['] = ']'; score[']'] = 2;
    pair['{'] = '}'; score['}'] = 3;
    pair['('] = ')'; score[')'] = 1;
    pair['<'] = '>'; score['>'] = 4;

    if(!file.is_open()) {
        cout << "Error open input txt file" << '\n';
        exit(1);
    }

    while(getline(file, temp)) {
        ll total = 0;
        stack<char> s;

        for(int i = 0; i < temp.size(); i++) {
            char c = temp.at(i);

            if(c == ']' || c == '}' || c == ')' || c == '>') {
                s.pop();
            } else {
                s.push(c);
            }
        }

        int size = s.size();
        for(int i = 0; i < size; i++) {
            total = total * 5 + (ll)score[pair[s.top()]];
            s.pop();
        }
        cnt[total]++;
        
    }
    
    cout << cnt.size() << '\n';
    int i = 1;
    for(auto it = cnt.begin(); it != cnt.end(); it++) {
        cout << i << ' ' << it->first << ' ' << it->second << '\n';
        i++;
    }

}

int main() {
    //part1();
    part2();
    
    return 0;
}