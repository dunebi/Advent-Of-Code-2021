#include <iostream>
#include <fstream>

using namespace std;

int main() {
    FILE* pFile = fopen("8_input.txt", "r");
    char c;
    bool isOutput = false;
    int cnt = 0, ans = 0;

    while(true) {
        c = fgetc(pFile);
        if (c == EOF) break;

        if(c == '|') {
            isOutput = true;
            cnt = 0;
        } else if (c == '\n')  {
            if(cnt == 2 || cnt == 4 || cnt == 3 || cnt == 7) ans += isOutput;
            isOutput = false;
            cnt = 0;
        } else if (c == ' ') {
            if(cnt == 2 || cnt == 4 || cnt == 3 || cnt == 7) ans += isOutput;
            cnt = 0;
        } else cnt++;
    }
    fclose(pFile);
    cout << ans << '\n';

    return 0;
}