#include <iostream>
#include <fstream>
#include <cmath>
#include <deque>
#include <numeric>

#define MAX 9
typedef long long ll;

using namespace std;
deque<ll> dq;

ll solve(int maxDay) {
    for(int i = 0; i < maxDay; i++) {
        ll zeroCnt = dq[0];

        dq.pop_front();
        dq.push_back(zeroCnt);
        dq[6] += zeroCnt;
    }

    return accumulate(dq.begin(), dq.end(), (ll)0);
}

int main() {
    FILE* pFile = fopen("6_input.txt", "r");
    int day;
    cin >> day;
    ll cnt[MAX] = {0, };
    char c = '\0';

    while(c != EOF) {
        if(isdigit(c)) {
            cnt[c - '0']++;
        }
        c = fgetc(pFile);
    }

    for(int i = 0; i < MAX; i++) {
        dq.push_back((ll)cnt[i]);
    }
    
    cout << solve(day) << '\n';

    return 0;
}