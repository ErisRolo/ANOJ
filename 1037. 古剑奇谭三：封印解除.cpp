#include <bits/stdc++.h>
using namespace std;

int h[4]; //0ио 1ср 2об 3вС

int main() {
    fill(h, h + 4, 0);
    string s;
    for(int i = 0; i < 4; i++) {
        cin >> s;
        if(s == "IN")
            h[i] = 1;
        if(s == "OUT")
            h[i] = -1;
    }
    if(h[0] == 1 && h[1] == 1 && h[2] == 1 && h[3] == 1) {
        printf("YES");
        return 0;
    }
    int k;
    bool flag;
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        flag = false;
        cin >> s;
        if(s == "UP") {
            h[0] = -h[0], h[1] = -h[1], h[3] = -h[3];
        }
        if(s == "LEFT") {
            h[0] = -h[0], h[2] = -h[2], h[3] = -h[3];
        }
        if(s == "DOWN") {
            h[1] = -h[1], h[2] = -h[2], h[3] = -h[3];
        }
        if(s == "RIGHT") {
            h[0] = -h[0], h[1] = -h[1], h[2] = -h[2];
        }
        if(h[0] == 1)
            cout << "IN ";
        else
            cout << "OUT ";
        if(h[1] == 1)
            cout << "IN ";
        else
            cout << "OUT ";
        if(h[2] == 1)
            cout << "IN ";
        else
            cout << "OUT ";
        if(h[3] == 1)
            cout << "IN" << endl;
        else
            cout << "OUT" << endl;
        if(h[0] == 1 && h[1] == 1 && h[2] == 1 && h[3] == 1) {
            flag = true;
            break;
        }
    }
    if(flag)
        printf("YES");
    else
        printf("NO");
    return 0;
}
